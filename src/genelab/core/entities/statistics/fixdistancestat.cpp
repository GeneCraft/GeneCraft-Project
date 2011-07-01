#include "fixdistancestat.h"

#include "body/fixation.h"

namespace GeneLabCore{

FixDistanceStat::FixDistanceStat(Fixation *fix) : fix(fix)
{
    previousOrigin = fix->getRigidBody()->getWorldTransform().getOrigin();
}

void FixDistanceStat::update()
{
    // get new origin
    btVector3 origin = fix->getRigidBody()->getWorldTransform().getOrigin();

    // update value by computing distance between previous origin and new origin
    value += previousOrigin.distance(origin);

    // update previous origin
    previousOrigin = origin;
}

}
