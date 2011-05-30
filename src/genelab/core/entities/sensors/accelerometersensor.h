#ifndef ACCELEROMETERSENSOR_H
#define ACCELEROMETERSENSOR_H

#include "genelabcoreclasses.h"
#include "sensor.h"
#include "LinearMath/btVector3.h"

namespace GeneLabCore {

/**
 * (c) GeneLab 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * This sensor allows entities to know the acceleration movement of a specific fixation.
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo & Cyprien Huissoud
 */
class AccelerometerSensor : public Sensor
{
public:

    AccelerometerSensor(long stepTime, Fixation * fixation);

public slots:

    void step();

private:

    long stepTime;
    BrainIn * inputX, * inputY, * inputZ;
    btVector3 oldPosition, oldSpeed;

};
}



#endif // ACCELEROMETERSENSOR_H
