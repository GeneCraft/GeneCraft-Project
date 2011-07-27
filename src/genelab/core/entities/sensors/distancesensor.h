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
