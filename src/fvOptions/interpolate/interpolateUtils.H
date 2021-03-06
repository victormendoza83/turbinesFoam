/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2013 OpenFOAM Foundation
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

Class
    Foam::interpolateUtils

Description
This file contains functions useful for interpolating data from input files

SourceFiles
    interpolateUtils.H
    interpolateUtils.C

\*---------------------------------------------------------------------------*/

#ifndef interpolateUtils_H
#define interpolateUtils_H

#include "fvCFD.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

namespace interpolateUtils
{

//- Find index for interpolation
label binarySearch
(
    const List<scalar>& list,
    const scalar value
);
        
//- Find index for interpolation
label linearSearch
(
    const List<scalar>& list,
    const scalar value,
    label startvalue=0
);

//get interpolation fraction
scalar getPart
(
    const scalar xNew,
    const List<scalar>& xList,
    label &xIndex
);

//interpolate from 1d data with known index
scalar interpolate1d
(
    const scalar xNew,
    const List<scalar>& xList,
    const List<scalar>& data,
    label xIndex
);

//interpolate from 1d data with known fraction
scalar interpolate1d
(
    const scalar xPart,
    const List<scalar>& data,
    label xIndex
);

//interpolate from 1d data
scalar interpolate1d
(
    const scalar xNew,
    const List<scalar>& xList,
    const List<scalar>& data
);

//interpolate from 2d data with known indices
scalar interpolate2d
(
    const scalar xNew,
    const scalar yNew,
    const List<scalar>& xList,
    const List<scalar>& yList,
    const List<List<scalar> >& data,
    label xIndex,
    label yIndex
);

//interpolate from 2d data with known fractions
scalar interpolate2d
(
    const scalar xPart,
    const scalar yPart,
    const List<List<scalar> >& data,
    label xIndex,
    label yIndex
);
        
//interpolate from 2d data
scalar interpolate2d
(
    const scalar xNew,
    const scalar yNew,
    const List<scalar>& xList,
    const List<scalar>& yList,
    const List<List<scalar> >& data
);

} //End namespace interpolateUtils


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
