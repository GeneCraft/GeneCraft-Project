/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "bonelimitsmutation.h"

#include "tools.h"
#include <cmath>
#include <QDebug>

namespace GeneCraftCore {

BoneLimitsMutation::BoneLimitsMutation()
{
    axisMutation = new FloatMutation();
    axisMutation->probability    = 0.1;
    axisMutation->mean         = 0.0;
    axisMutation->sigma        = 0.5;
    axisMutation->minValue       = -SIMD_PI;
    axisMutation->maxValue       =  SIMD_PI;
}

void BoneLimitsMutation::mutate(QJsonObject &lowerLimits, QJsonObject &upperLimits)
{
    // foreach axis...
    QString allAxis[] = {"x","y","z"};
    for(int i=0;i<3;i++){

        QString axis = allAxis[i];
        btScalar loValue = lowerLimits[axis].toDouble();
        btScalar upValue = upperLimits[axis].toDouble();

        loValue = axisMutation->mutate(loValue);
        upValue = axisMutation->mutate(upValue);

        // Y axis limited between -SIMD_PI/2..SIMD_PI/2
        if(axis == "y") {
            if(loValue < -SIMD_HALF_PI+0.1)
                loValue = -SIMD_HALF_PI+0.1;

            if(upValue > SIMD_HALF_PI-0.1)
                upValue = SIMD_HALF_PI-0.1;
        }

        // 0 must be included between lo and up
        if(loValue > 0)
            loValue = 0;

        if(upValue < 0)
            upValue = 0;

        lowerLimits.remove(axis);
        upperLimits.remove(axis);
        lowerLimits.insert(axis,(double)loValue);
        upperLimits.insert(axis,(double)upValue);
    }
}

}
