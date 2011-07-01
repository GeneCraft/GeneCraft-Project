#ifndef FIXDISTANCESTAT_H
#define FIXDISTANCESTAT_H

#include "genelabcoreclasses.h"
#include "statistic.h"
#include "LinearMath/btVector3.h"

namespace GeneLabCore{

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
