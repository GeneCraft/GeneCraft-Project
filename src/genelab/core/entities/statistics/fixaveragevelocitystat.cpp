#include "fixaveragevelocitystat.h"

#include "body/fixation.h"

namespace GeneLabCore{

FixAverageVelocityStat::FixAverageVelocityStat(Fixation *fix) : fix(fix)
{
    nbSteps = 0;
    totalDistance = .0f;
    previousOrigin = fix->getRigidBody()->getWorldTransform().getOrigin();
}

void FixAverageVelocityStat::update()
{
    nbSteps++;

    // get new origin
    btVector3 origin = fix->getRigidBody()->getWorldTransform().getOrigin();

    // update value by computing distance between previous origin and new origin
    totalDistance += previousOrigin.distance(origin);

    // update previous origin
    previousOrigin = origin;

    // compute average velocity
    value = totalDistance / nbSteps;
}

}