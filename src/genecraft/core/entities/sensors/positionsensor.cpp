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

#include "positionsensor.h"

#include "brain/brainin.h"
#include "body/fixation.h"
#include <QDebug>
#include <QVariant>
#include "tools.h"

// FIXME : max size of an entity is 10 in this case !
// The best would be to pass the entity for computing its biggest member (root to end fix)
#define minDistanceBetweenRootFixAndThisFix -5.0
#define maxDistanceBetweenRootFixAndThisFix 5.0

namespace GeneCraftCore {
PositionSensor::PositionSensor(Fixation * rootFix, Fixation *fixation) : Sensor(fixation) {
    this->rootFix = rootFix;

    typeName = "Egocentric position sensor";
    type = positionSensor;

    inputX = new BrainIn(minDistanceBetweenRootFixAndThisFix, maxDistanceBetweenRootFixAndThisFix);
    inputY = new BrainIn(minDistanceBetweenRootFixAndThisFix, maxDistanceBetweenRootFixAndThisFix);
    inputZ = new BrainIn(minDistanceBetweenRootFixAndThisFix, maxDistanceBetweenRootFixAndThisFix);

    brainInputs.append(inputX);
    brainInputs.append(inputY);
    brainInputs.append(inputZ);
}

PositionSensor::PositionSensor(QJsonObject data, Fixation* rootFix, Fixation* fixation) : Sensor(data, fixation) {
    this->rootFix = rootFix;

    inputX = new BrainIn(data["inputX"].toObject());
    inputY = new BrainIn(data["inputY"].toObject());
    inputZ = new BrainIn(data["inputZ"].toObject());

    brainInputs.append(inputX);
    brainInputs.append(inputY);
    brainInputs.append(inputZ);
}

QJsonObject PositionSensor::serialize() {
    QJsonObject data = Sensor::serialize();
    data.insert("inputX", inputX->serialize());
    data.insert("inputY", inputY->serialize());
    data.insert("inputZ", inputZ->serialize());

    return data;
}

QJsonObject PositionSensor::generateEmpty()
{
    QJsonObject data = Sensor::generateEmpty("Egocentric position sensor", positionSensor);

    BrainIn inputX(minDistanceBetweenRootFixAndThisFix,maxDistanceBetweenRootFixAndThisFix);
    BrainIn inputY(minDistanceBetweenRootFixAndThisFix,maxDistanceBetweenRootFixAndThisFix);
    BrainIn inputZ(minDistanceBetweenRootFixAndThisFix,maxDistanceBetweenRootFixAndThisFix);

    inputX.connectRandomly();
    inputY.connectRandomly();
    inputZ.connectRandomly();

    data.insert("inputX", inputX.serialize());
    data.insert("inputY", inputY.serialize());
    data.insert("inputZ", inputZ.serialize());

    return data;
}

void PositionSensor::step() {
    btTransform inverseRootTransform = rootFix->getRigidBody()->getWorldTransform().inverse();
    btVector3 distance = inverseRootTransform(fixation->getRigidBody()->getWorldTransform().getOrigin());

    inputX->setValue(distance.x());
    inputY->setValue(distance.y());
    inputZ->setValue(distance.z());
}
}
