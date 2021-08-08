/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | foam-extend: Open Source CFD
   \\    /   O peration     | Version:     4.1
    \\  /    A nd           | Web:         http://www.foam-extend.org
     \\/     M anipulation  | For copyright notice see file Copyright
-------------------------------------------------------------------------------
License
    This file is part of foam-extend.

    foam-extend is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    foam-extend is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with foam-extend.  If not, see <http://www.gnu.org/licenses/>.

Application
    sonicLiquidFoam

Description
    Transient solver for trans-sonic/supersonic, inviscid flow of a
    compressible liquid.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "pimpleControl.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
#   include "setRootCase.H"
#   include "createTime.H"
#   include "createMesh.H"

    pimpleControl pimple(mesh);

#   include "readThermodynamicProperties.H"
#   include "readTransportProperties.H"
#   include "createFields.H"
// #   include "initContinuityErrs.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nStarting time loop\n" << endl;

    while (runTime.loop())
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;

#       include "compressibleCourantNo.H"

        // --- PIMPLE loop
        while (pimple.loop())
        {
            // Correct density
            rho = psi*p;
            surfaceScalarField rhof =
                fvc::interpolate(rho, "upwindRho");

            // Solve energy equation
            fvScalarMatrix TEqn
            (
                Cp*fvm::ddt(rho, T)
              + Cp*fvm::div(phi, T)
             == fvc::DDt(phi/fvc::interpolate(rho, "upwindRho"), p)
            );
            TEqn.relax();
            TEqn.solve();

            // Correct psi
            psi = 1.0/(R*T);

            // Solve momentum equation
            fvVectorMatrix UEqn
            (
                fvm::ddt(rho, U)
              + fvm::div(phi, U)
            );
            UEqn.relax();
            solve(UEqn == -fvc::grad(p));

            // --- PISO loop
            while (pimple.correct())
            {
                p.storePrevIter();

                volScalarField rAU("rAU", 1.0/UEqn.A());

                surfaceScalarField rhorAUf =
                    rhof*fvc::interpolate(rAU);

                U = rAU*UEqn.H();

                surfaceScalarField phid
                (
                    "phid",
                    fvc::interpolate(psi, "upwindPsi")
                   *(fvc::interpolate(U) & mesh.Sf())
                );

                fvScalarMatrix pEqn
                (
                    fvm::ddt(psi, p)
                  + fvm::div(phid, p)
                  - fvm::laplacian(rhorAUf, p)
                );

                pEqn.solve();

                phi = pEqn.flux();

                p.relax();

                // Correct velocity
                U -= rAU*fvc::grad(p);
                U.correctBoundaryConditions();
            }

// #           include "compressibleContinuityErrs.H"
        }

        runTime.write();
        
#       include "writeFields.H"

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info<< "End\n" << endl;

    return(0);
}


// ************************************************************************* //
