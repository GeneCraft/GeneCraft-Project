#ifndef FIXAVERAGEVELOCITYSTAT_H
#define FIXAVERAGEVELOCITYSTAT_H

#include "genelabcoreclasses.h"
#include "statistic.h"
#include "LinearMath/btVector3.h"

namespace GeneLabCore{

class FixAverageVelocityStat : public Statistic
{
public:

    FixAverageVelocityStat(Fixation * fix);
    void update();

protected:

    float totalDistance;
    int nbSteps;
    Fixation *fix;
    btVector3 previousOrigin;
};

}

#endif // FIXAVERAGEVELOCITYSTAT_H
