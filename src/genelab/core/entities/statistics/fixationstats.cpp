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

    // first initialization of the previous origin
    previousOrigin = fixation->getRigidBody()->getWorldTransform().getOrigin();
}

void FixationStats::step()
{
    // get new origin
    btVector3 origin = fixation->getRigidBody()->getWorldTransform().getOrigin();

    // UPDATE VALUES
    fixationVelocity->setValue(previousOrigin.distance(origin));
    fixationRelativeDistance->setValue(origin.distance(refOrigin) - previousOrigin.distance(refOrigin));

    // update previous origin
    previousOrigin = origin;
}

void FixationStats::resetOrigin(){
    refOrigin = fixation->getRigidBody()->getWorldTransform().getOrigin();
}

}
