#include "fixdistancefromoriginstat.h"

#include "body/fixation.h"

namespace GeneLabCore{

FixDistanceFromOriginStat::FixDistanceFromOriginStat(Fixation *fix) : fix(fix)
{
    // Info
    name = "Fixation distance from origin";
    unit = "m";

    origin = fix->getRigidBody()->getWorldTransform().getOrigin();
    updateEachStep = false;
    updateWhenValueIsRequested = true;
}

void FixDistanceFromOriginStat::update()
{
    // update value by computing distance between previous origin and current origin
    value = origin.distance(fix->getRigidBody()->getWorldTransform().getOrigin());
}

void FixDistanceFromOriginStat::reset() {
    Statistic::reset();
    this->origin = fix->getRigidBody()->getWorldTransform().getOrigin();
}

}
