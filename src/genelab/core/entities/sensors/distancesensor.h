#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H

#include "genelabcoreclasses.h"
#include "sensor.h"
#include "LinearMath/btQuaternion.h"

namespace GeneLabCore {

class DistanceSensor : public Sensor
{
public:

    // To create
    DistanceSensor(Fixation * fixation, btQuaternion orientation);

    // To create from serialization data
    DistanceSensor(QVariant data, Fixation* fixation);

    // To serialize
    virtual QVariant serialize();

    // To update brain inputs values
    void step();

private:

    BrainIn *distanceInput;
    btQuaternion orientation;

};
}

#endif // DISTANCESENSOR_H
