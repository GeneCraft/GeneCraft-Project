#ifndef GYROSCOPICSENSOR_H
#define GYROSCOPICSENSOR_H

#include "genelabcoreclasses.h"
#include "sensor.h"

namespace GeneLabCore {

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

    // To update brain inputs values
    void step();

private:
    BrainIn * inputYaw, * inputPitch, * inputRoll;
};
}

#endif // GYROSCOPICSENSOR_H
