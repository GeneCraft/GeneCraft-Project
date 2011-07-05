#ifndef FIXDISTANCEFROMORIGINSTAT_H
#define FIXDISTANCEFROMORIGINSTAT_H

#include "genelabcoreclasses.h"
#include "statistic.h"
#include "LinearMath/btVector3.h"

namespace GeneLabCore{

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * FixDistanceFromOriginStat is used to know the distance traveled by a fixation (from origin to current position).
 * Notice that you can set or reset the origin.
 *
 * Unit : meters
 *
 * @version 1.0 | July 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class FixDistanceFromOriginStat : public Statistic
{
public:

    // To create the statistic
    FixDistanceFromOriginStat(Fixation * fix);

    // To update the statistic value
    void update();

    // To set the origin
    void setOrigin(btVector3 origin) { this->origin = origin; }

    // To reset origin to current origin
    void reset();

protected:

    Fixation *fix;
    btVector3 origin;
};

}

#endif // FIXDISTANCEFROMORIGINSTAT_H
