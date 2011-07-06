#ifndef FIXAVERAGEVELOCITYSTAT_H
#define FIXAVERAGEVELOCITYSTAT_H

#include "genelabcoreclasses.h"
#include "statistic.h"
#include "LinearMath/btVector3.h"

namespace GeneLabCore{

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * Statistics used to know the average velocity of a fixation (all axes combined).
 *
 * Unit : meters / step
 *
 * @version 1.0 | July 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class FixAverageVelocityStat : public Statistic
{
public:

    FixAverageVelocityStat(Fixation * fix);
    void update();

    // To reset average
    void reset() { Statistic::reset(); totalDistance = 0.0;}

protected:

    float totalDistance;
    Fixation *fix;
    btVector3 previousOrigin;
};

}

#endif // FIXAVERAGEVELOCITYSTAT_H
