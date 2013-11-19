/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2013 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "functionObjectTemplate.H"
#include "Time.H"
#include "fvCFD.H"
#include "unitConversion.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(errorFunctionObject, 0);


// * * * * * * * * * * * * * * * Local Functions * * * * * * * * * * * * * * //

//{{{ begin localCode

//}}} end localCode


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

const objectRegistry& errorFunctionObject::obr() const
{
    return obr_;
}


const fvMesh& errorFunctionObject::mesh() const
{
    return refCast<const fvMesh>(obr_);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

errorFunctionObject::errorFunctionObject
(
    const word& name,
    const objectRegistry& obr,
    const dictionary& dict,
    const bool
)
:
    name_(name),
    obr_(obr)
{
    read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

errorFunctionObject::~errorFunctionObject()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void errorFunctionObject::read(const dictionary& dict)
{
    if (false)
    {
        Info<<"read error sha1: e92448da6ae10bc777e0869670f72a48fd0673f1\n";
    }

//{{{ begin code
    
//}}} end code
}


void errorFunctionObject::execute()
{
    if (false)
    {
        Info<<"execute error sha1: e92448da6ae10bc777e0869670f72a48fd0673f1\n";
    }

//{{{ begin code
    
//}}} end code
}


void errorFunctionObject::end()
{
    if (false)
    {
        Info<<"end error sha1: e92448da6ae10bc777e0869670f72a48fd0673f1\n";
    }

//{{{ begin code
    
//}}} end code
}


void errorFunctionObject::timeSet()
{
    if (false)
    {
        Info<<"timeSet error sha1: e92448da6ae10bc777e0869670f72a48fd0673f1\n";
    }

//{{{ begin codeTime
    
//}}} end code
}


void errorFunctionObject::write()
{
    if (false)
    {
        Info<<"write error sha1: e92448da6ae10bc777e0869670f72a48fd0673f1\n";
    }

//{{{ begin code
    #line 58 "D:/Projects/Test/ToolOpenFoamExample8/system/controlDict::functions::difference"
// Lookup U
            Info<< "Looking up field U\n" << endl;
            const volVectorField& U = mesh().lookupObject<volVectorField>("U");

            Info<< "Reading inlet velocity  uInfX\n" << endl;

            scalar ULeft = 0.0;
            label leftI = mesh().boundaryMesh().findPatchID("left");
            const fvPatchVectorField& fvp = U.boundaryField()[leftI];
            if (fvp.size())
            {
                ULeft = fvp[0].x();
            }
            reduce(ULeft, maxOp<scalar>());

            dimensionedScalar uInfX
            (
                "uInfx",
                dimensionSet(0, 1, -1, 0, 0),
                ULeft
            );

            Info << "U at inlet = " << uInfX.value() << " m/s" << endl;


            scalar magCylinder = 0.0;
            label cylI = mesh().boundaryMesh().findPatchID("cylinder");
            const fvPatchVectorField& cylFvp = mesh().C().boundaryField()[cylI];
            if (cylFvp.size())
            {
                magCylinder = mag(cylFvp[0]);
            }
            reduce(magCylinder, maxOp<scalar>());

            dimensionedScalar radius
            (
                "radius",
                dimensionSet(0, 1, 0, 0, 0),
                magCylinder
            );

            Info << "Cylinder radius = " << radius.value() << " m" << endl;

            volVectorField UA
            (
                IOobject
                (
                    "UA",
                    mesh().time().timeName(),
                    U.mesh(),
                    IOobject::NO_READ,
                    IOobject::AUTO_WRITE
                ),
                U
            );

            Info<< "\nEvaluating analytical solution" << endl;

            const volVectorField& centres = UA.mesh().C();
            volScalarField magCentres(mag(centres));
            volScalarField theta(acos((centres & vector(1,0,0))/magCentres));

            volVectorField cs2theta
            (
                cos(2*theta)*vector(1,0,0)
              + sin(2*theta)*vector(0,1,0)
            );

            UA = uInfX*(dimensionedVector(vector(1,0,0))
              - pow((radius/magCentres),2)*cs2theta);

            // Force writing of UA (since time has not changed)
            UA.write();

            volScalarField error("error", mag(U-UA)/mag(UA));

            Info<<"Writing relative error in U to " << error.objectPath()
                << endl;

            error.write();
//}}} end code
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam


// ************************************************************************* //

