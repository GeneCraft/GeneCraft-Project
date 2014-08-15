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

#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H

#include "genecraftcoreclasses.h"
#include "sensor.h"
#include "LinearMath/btQuaternion.h"

namespace GeneCraftCore {

class DistanceSensor : public Sensor
{
public:

    // To create
    DistanceSensor(Fixation * fixation, btScalar yAxis, btScalar zAxis);

    // To create from serialization data
    DistanceSensor(QVariant data, Fixation* fixation);

    // To create empty sensor serialization data
    static QVariant generateEmpty();

    // To serialize
    virtual QVariant serialize();

    // To update brain inputs values
    void step();

private:

    BrainIn *distanceInput;
    btScalar yAxis;
    btScalar zAxis;
};
}

#endif // DISTANCESENSOR_H
