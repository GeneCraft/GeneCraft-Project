/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

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


    fixationDistance = statsStorage->registerStat(fixName + QString("Distance"),"m / step");

    fixationYPosition = statsStorage->registerStat(fixName + QString("YPosition"), "m / step");
    fixationXPosition = statsStorage->registerStat(fixName + QString("XPosition"), "m / step");
    fixationZPosition = statsStorage->registerStat(fixName + QString("ZPosition"), "m / step");


    connect(fixationAbsoluteVelocity,SIGNAL(reseted()), this, SLOT(resetOrigin()), Qt::DirectConnection);
    connect(fixationRelativeVelocity,SIGNAL(reseted()), this, SLOT(resetOrigin()), Qt::DirectConnection);
    connect(fixationAbsoluteYPosition,SIGNAL(reseted()), this, SLOT(resetOrigin()), Qt::DirectConnection);
    connect(fixationAbsoluteXPosition,SIGNAL(reseted()), this, SLOT(resetOrigin()), Qt::DirectConnection);
    connect(fixationAbsoluteZPosition,SIGNAL(reseted()), this, SLOT(resetOrigin()), Qt::DirectConnection);
    connect(fixationDistance,SIGNAL(reseted()), this, SLOT(resetOrigin()), Qt::DirectConnection);
    connect(fixationYPosition,SIGNAL(reseted()), this, SLOT(resetOrigin()), Qt::DirectConnection);
    connect(fixationXPosition,SIGNAL(reseted()), this, SLOT(resetOrigin()), Qt::DirectConnection);
    connect(fixationZPosition,SIGNAL(reseted()), this, SLOT(resetOrigin()), Qt::DirectConnection);


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

    fixationDistance->setValue(origin.distance(refDistance));
    fixationXPosition->setValue(origin.x() - refPosX.x());
    fixationYPosition->setValue(origin.y() - refPosY.y());
    fixationZPosition->setValue(origin.z() - refPosZ.z());
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

    if(fixationDistance->getSum() == 0) {
        refDistance = this->fixation->getRigidBody()->getWorldTransform().getOrigin();
    }

    if(fixationXPosition->getSum() == 0) {
        refPosX = this->fixation->getRigidBody()->getWorldTransform().getOrigin();
    }

    if(fixationYPosition->getSum() == 0) {
        refPosY = this->fixation->getRigidBody()->getWorldTransform().getOrigin();
    }

    if(fixationZPosition->getSum() == 0) {
        refPosZ = this->fixation->getRigidBody()->getWorldTransform().getOrigin();
    }
}

}
