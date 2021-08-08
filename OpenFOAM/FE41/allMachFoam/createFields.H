    // Info<< "Reading thermophysical properties\n" << endl;

    // autoPtr<basicPsiThermo> pThermo
    // (
    //     basicPsiThermo::New(mesh)
    // );
    // basicPsiThermo& thermo = pThermo();

    // volScalarField& p = thermo.p();
    // volScalarField& T = thermo.T();

    // const volScalarField& psi = thermo.psi();
    // psi.oldTime();

    // volScalarField psis("psi", thermo.psi()/thermo.Cp()*thermo.Cv());
    // psis.oldTime();

    Info<< "Reading field p\n" << endl;
    volScalarField p
    (
        IOobject
        (
            "p",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    Info<< "Reading field U\n" << endl;
    volVectorField U
    (
        IOobject
        (
            "U",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    Info<< "Reading field ht\n" << endl;
    volScalarField T
    (
        IOobject
        (
            "T",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    volScalarField psi
    (
        IOobject
        (
            "psi",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        1.0/(R*T)
    );
    psi.oldTime();

    volScalarField rho
    (
        IOobject
        (
            "rho",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        psi*p
    );
    rho.oldTime();

#   include "compressibleCreatePhi.H"

    mesh.schemesDict().setFluxRequired(p.name());
