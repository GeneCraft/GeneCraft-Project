#ifndef GYROSCOPICSENSOR_H
#define GYROSCOPICSENSOR_H

#include "genelabcoreclasses.h"
#include "sensor.h"

namespace GeneLabCore {

/**
 * (c) GeneLab 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * This sensor allows entities to know the angular position of a specific fixation.
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo & Cyprien Huissoud
 */
class GyroscopicSensor : public Sensor
{
public:
    GyroscopicSensor(Fixation * fixation);
    GyroscopicSensor(QVariant data, Fixation* fixation);

    virtual QVariant serialize();

public slots:
    void step();

private:
    BrainIn * inputYaw, * inputPitch, * inputRoll;
};
}

#endif // GYROSCOPICSENSOR_H
