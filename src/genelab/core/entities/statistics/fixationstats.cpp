#include "fixationstats.h"

#include "statisticsstorage.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btQuaternion.h"
#include "body/bone.h"
#include "body/fixation.h"
#include "body/treeshape.h"

#define EPSILON 0.01

namespace GeneCraftCore{

FixationStats::FixationStats(StatisticsStorage * statsStorage, Fixation * fixation, QString fixName) :
    StatisticsProvider(statsStorage), fixation(fixation), nbSteps(0)
{
    fixationAbsoluteVelocity = statsStorage->registerStat(fixName + QString("AbsVelocity"),"m / step");

    fixationRelativeVelocity = statsStorage->registerStat(fixName + QString("RelVelocity"),"m / step");

    fixationAbsoluteYPosition = statsStorage->registerStat(fixName + QString("YRelVelocity"), "m / step");
    fixationAbsoluteXPosition = statsStorage->registerStat(fixName + QString("XRelVelocity"), "m / step");
    fixationAbsoluteZPosition = statsStorage->registerStat(fixName + QString("ZRelVelocity"), "m / step");


    connect(fixationAbsoluteVelocity,SIGNAL(reseted()), this, SLOT(resetOrigin()), Qt::DirectConnection);
    connect(fixationRelativeVelocity,SIGNAL(reseted()), this, SLOT(resetOrigin()), Qt::DirectConnection);
    connect(fixationAbsoluteYPosition,SIGNAL(reseted()), this, SLOT(resetOrigin()), Qt::DirectConnection);
    connect(fixationAbsoluteXPosition,SIGNAL(reseted()), this, SLOT(resetOrigin()), Qt::DirectConnection);
    connect(fixationAbsoluteZPosition,SIGNAL(reseted()), this, SLOT(resetOrigin()), Qt::DirectConnection);


    resetOrigin();

}

void FixationStats::step()
{
    // get new origin
    btVector3 origin = fixation->getRigidBody()->getWorldTransform().getOrigin();

    // velocity
    if(qAbs(previousOriginAbs.distance(origin)) > EPSILON) {
        fixationAbsoluteVelocity->setValue(previousOriginAbs.distance(origin));
        previousOriginAbs = origin;
    } else {
        fixationAbsoluteVelocity->setValue(0);
    }

    // relative distance
    // 0.001 because of little variantion create noise and cumulate lot of errors in the sum value
    // And because it's impossible to attaint stability without this cheat
    if(qAbs(origin.distance(refOriginRel) - previousOriginRel.distance(refOriginRel)) > EPSILON) {
        fixationRelativeVelocity->setValue(origin.distance(refOriginRel) - previousOriginRel.distance(refOriginRel));
        previousOriginRel = origin;
    }
    else
        fixationRelativeVelocity->setValue(0.0);

    // absolute Y position
    if(qAbs(origin.y() - previousOriginY.y()) > EPSILON) {
        fixationAbsoluteYPosition->setValue(origin.y() - previousOriginY.y());
        previousOriginY = origin;
    }
    else
        fixationAbsoluteYPosition->setValue(0.0);

    if(qAbs(origin.x() - previousOriginX.x()) > EPSILON) {
        fixationAbsoluteXPosition->setValue(origin.x() - previousOriginX.x());
        previousOriginX = origin;
    }
    else
        fixationAbsoluteXPosition->setValue(0.0);

    if(qAbs(origin.z() - previousOriginZ.z()) > EPSILON) {
        fixationAbsoluteZPosition->setValue(origin.z() - previousOriginZ.z());
        previousOriginZ = origin;
    }
    else
        fixationAbsoluteZPosition->setValue(0.0);

}

void FixationStats::resetOrigin(){

    if(fixationAbsoluteVelocity->getSum() == 0) {
        previousOriginAbs = this->fixation->getRigidBody()->getWorldTransform().getOrigin();
    }

    if(fixationRelativeVelocity->getSum() == 0) {
        refOriginRel = previousOriginRel = this->fixation->getRigidBody()->getWorldTransform().getOrigin();
    }

    if(fixationAbsoluteYPosition->getSum() == 0) {
        refOriginY = previousOriginY = this->fixation->getRigidBody()->getWorldTransform().getOrigin();
    }

    if(fixationAbsoluteXPosition->getSum() == 0) {
        refOriginX = previousOriginX = this->fixation->getRigidBody()->getWorldTransform().getOrigin();
    }

    if(fixationAbsoluteZPosition->getSum() == 0) {
        refOriginZ = previousOriginZ = this->fixation->getRigidBody()->getWorldTransform().getOrigin();
    }
}

}
