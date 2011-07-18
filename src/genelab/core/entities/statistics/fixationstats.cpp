#include "fixationstats.h"

#include "statisticsstorage.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btQuaternion.h"
#include "body/bone.h"
#include "body/fixation.h"
#include "body/treeshape.h"

namespace GeneLabCore{

FixationStats::FixationStats(StatisticsStorage * statsStorage, Fixation * fixation, QString fixName) :
    StatisticsProvider(statsStorage), fixation(fixation), nbSteps(0)
{
    fixationVelocity = statsStorage->registerStat(fixName + QString(" absolute velocity"),"m / step");
    connect(fixationVelocity,SIGNAL(reseted()), this, SLOT(resetOrigin()));
    resetOrigin();

    fixationRelativeDistance = statsStorage->registerStat(fixName + QString(" relative velocity"),"m / step");

    fixationAbsoluteYPosition = statsStorage->registerStat(fixName + QString(" absolute Y position"), "m");

    // first initialization of the previous origin
    previousOrigin = fixation->getRigidBody()->getWorldTransform().getOrigin();
    sum = 0.;
}

void FixationStats::step()
{
    // get new origin
    btVector3 origin = fixation->getRigidBody()->getWorldTransform().getOrigin();

    // velocity
    fixationVelocity->setValue(previousOrigin.distance(origin));

    // relative distance
    // 0.001 because of little variantion create noise and cumulate lot of errors in the sum value
    // And because it's impossible to attaint stability without this cheat
    if(qAbs(origin.distance(refOrigin) - sum) < 0.0001)
        fixationRelativeDistance->setValue(0.0);
    else
        fixationRelativeDistance->setValue(origin.distance(refOrigin) - previousOrigin.distance(refOrigin));

    sum = origin.distance(refOrigin);

    // absolute Y position
    fixationAbsoluteYPosition->setValue(origin.y());

    // update previous origin
    previousOrigin = origin;
}

void FixationStats::resetOrigin(){
    refOrigin = previousOrigin =  fixation->getRigidBody()->getWorldTransform().getOrigin();
    sum = 0.0f;
}

}
