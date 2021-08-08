{
    // Solve continuity equation
    solve(fvm::ddt(rho) + fvc::div(phi));

    dimensionedScalar totalMass = fvc::domainIntegrate(rho);
    
    sumLocalContErr =
        (fvc::domainIntegrate(mag(rho - psi*p))/totalMass).value();

    globalContErr =
        (fvc::domainIntegrate(rho - psi*p)/totalMass).value();

    cumulativeContErr += globalContErr;

    Info<< "time step continuity errors : sum local = " << sumLocalContErr
        << ", global = " << globalContErr
        << ", cumulative = " << cumulativeContErr
        << endl;

    
}
