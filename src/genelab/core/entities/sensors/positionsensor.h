#ifndef POSITIONSENSOR_H
#define POSITIONSENSOR_H

#include "genelabcoreclasses.h"
#include "sensor.h"

namespace GeneLabCore {

/**
 * (c) GeneLab 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * This sensor allows entities to know a distance between two fixations. Normally the
 * first fixation is the root fixation of the entity.
 *
 * We don't use global position because basiquely an entity can't know its position
 * into the world and using this value can make different behavious between two same entities in
 * a different position in the world.
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo & Cyprien Huissoud
 */
class PositionSensor : public Sensor
{
public:

    PositionSensor(Fixation * rootFix, Fixation * fixation);

public slots:

    void step();

private:

    Fixation * rootFix;
    BrainIn * inputX, * inputY, * inputZ ;

};
}

#endif // POSITIONSENSOR_H
