if (runTime.outputTime())
{
    volScalarField Mo
    (
        IOobject
        (
            "Mo",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mag(U)/sqrt(Cp*R*T/(Cp-R))
    );

    Mo.write();
}
