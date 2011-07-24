#ifndef ACCELEROMETERSENSOR_H
#define ACCELEROMETERSENSOR_H

#include "genelabcoreclasses.h"
#include "sensor.h"
#include "LinearMath/btVector3.h"

namespace GeneLabCore {

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * This sensor allows entities to know the acceleration movement of a specific fixation.
 *
 * Unit : meter / step^2
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class AccelerometerSensor : public Sensor
{
public:

    // To create
    AccelerometerSensor(Fixation * fixation);

    // To create from serialization data
    AccelerometerSensor(QVariant data, Fixation * fixation);

    // To create an empty sensor
    static QVariant generateEmpty();

    // To serialize
    virtual QVariant serialize();

    // To update brain inputs values
    void step();

private:


    btScalar tmpMinAcc, tmpMaxAcc;
    BrainIn * inputX, * inputY, * inputZ;
    btVector3 oldPosition, oldSpeed;

};
}

#endif // ACCELEROMETERSENSOR_H
