/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author(s)
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of turbinesFoam, which is based on OpenFOAM.

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

Class
    Foam::fv::LeishmanBeddoesSGC

Description
    Leishman-Beddoes dynamic stall model modified by Sheng et al. (2008).

SourceFiles
    LeishmanBeddoesSGC.C

\*---------------------------------------------------------------------------*/

#ifndef LeishmanBeddoesShengDyachuk_H
#define LeishmanBeddoesShengDyachuk_H

#include "LeishmanBeddoesSGC.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace fv
{

/*---------------------------------------------------------------------------*\
                         Class LeishmanBeddoesSGC Declaration
\*---------------------------------------------------------------------------*/

class LeishmanBeddoesShengDyachuk
:
    public LeishmanBeddoesSGC
{

protected:

    // Protected data
    
        //- Correction to CC to make results reduce 
        //  to static values for low angles of attack
        bool CTCorrection_;

        //- Correct angle of attack due to attached flow effects
        bool alphaAttachedCorrection_;

        //- Cross flow turbine mode, adapts model to differences
        //  between upwind and downwind regions
        bool crossFlowTurbine_;

        //- previous value of deltaS
        scalar deltaSPrev_;

        //- Approximately static value for CT
        scalar CTStatic_;
        
        
    // Protected member functions
        
        //- Calculate unsteady quantities
        virtual void calcUnsteady();
        
        //- Calculate separated flow quantities
        virtual void calcSeparated();
    
        //- Update previous time step values
        virtual void update();

        //- Correct lift and drag coefficients
        virtual void correct
        (
            scalar magU,
            scalar alphaDeg,
            scalar& cl,
            scalar& cd,
            scalar& cm
        );


public:

    //- Runtime type information
    TypeName("LeishmanBeddoesShengDyachuk");


    // Constructors

        //- Construct from components
        LeishmanBeddoesShengDyachuk
        (
            const dictionary& dict, 
            const word& modelName,
            const Time& time,
            profileData& profileData
        );


    // Selectors

        //- Select null constructed
        static autoPtr<LeishmanBeddoesShengDyachuk> New
        (
            const dictionary& dict,
            const word& modelName,
            const Time& time,
            profileData& profileData
        );


    //- Destructor
    ~LeishmanBeddoesShengDyachuk();


    // Member Functions

        // Access

        // Check

        // Edit

        // Write
        
        // Evaluation

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace fv
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
