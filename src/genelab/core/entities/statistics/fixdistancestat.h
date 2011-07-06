#ifndef FIXDISTANCESTAT_H
#define FIXDISTANCESTAT_H

#include "genelabcoreclasses.h"
#include "statistic.h"
#include "LinearMath/btVector3.h"

namespace GeneLabCore{

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * Statistics used to know the distance traveled by a fixation (all axes combined).
 *
 * Unit : meters
 *
 * @version 1.0 | July 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class FixDistanceStat : public Statistic
{
public:

    FixDistanceStat(Fixation * fix);
    void update();

protected:

    Fixation *fix;
    btVector3 previousOrigin;
};

}

#endif // FIXDISTANCESTAT_H
