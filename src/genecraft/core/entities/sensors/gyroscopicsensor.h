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

#ifndef GYROSCOPICSENSOR_H
#define GYROSCOPICSENSOR_H

#include "genecraftcoreclasses.h"
#include "sensor.h"

namespace GeneCraftCore {

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * This sensor allows entities to know the angular position of a specific fixation.
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class GyroscopicSensor : public Sensor
{
public:

    // To create
    GyroscopicSensor(Fixation * fixation);

    // To create from serialization data
    GyroscopicSensor(QVariant data, Fixation* fixation);

    // To serialize
    virtual QVariant serialize();

    // To create an empty sensor
    static QVariant generateEmpty();

    // To update brain inputs values
    void step();

private:
    BrainIn * inputYaw, * inputPitch, * inputRoll;
};
}

#endif // GYROSCOPICSENSOR_H
