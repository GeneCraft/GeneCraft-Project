#ifndef CONTACTSENSOR_H
#define CONTACTSENSOR_H

#include "genelabcoreclasses.h"
#include "sensor.h"
#include "LinearMath/btVector3.h"
#include <QVariant>

namespace GeneLabCore {

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * This sensor allows entities to know what fixation is in contact with static object.
 *
 * Unit : meter / step^2
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class ContactSensor : public Sensor
{
public:

    // To create
    ContactSensor(Fixation * fixation);

    // To create from serialization data
    ContactSensor(QVariant data, Fixation * fixation);

    // To serialize
    virtual QVariant serialize();

public slots:

    // To update brain inputs values
    void step();

private:

    float tmpMinAcc, tmpMaxAcc;
    BrainIn * inputX, * inputY, * inputZ;
    btVector3 oldPosition, oldSpeed;

};
}

#endif // CONTACTSENSOR_H
