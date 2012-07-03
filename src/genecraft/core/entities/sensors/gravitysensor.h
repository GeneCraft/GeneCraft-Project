#ifndef GRAVITYSENSOR_H
#define GRAVITYSENSOR_H

#include "genecraftcoreclasses.h"
#include "sensor.h"
#include "LinearMath/btVector3.h"
#include <QVariant>
#include "btBulletCollisionCommon.h"

namespace GeneCraftCore {

class GravitySensor : public Sensor
{
public:

    // To create
    GravitySensor(Fixation* fixation);

    // To create from serialization data
    GravitySensor(QVariant data, Fixation * fixation);

    // To serialize
    virtual QVariant serialize();

    // To create empty sensor serialization data
    static QVariant generateEmpty();

    // To update brain inputs values
    void step();
private:
    BrainIn * axeX, * axeY, * axeZ;
};

}

#endif // GRAVITYSENSOR_H
