#include "positionsensor.h"

#include "brain/brainin.h"
#include "body/fixation.h"
#include <QDebug>
#include <QVariant>

namespace GeneLabCore {
PositionSensor::PositionSensor(Fixation * rootFix, Fixation *fixation) : Sensor(fixation) {
    this->rootFix = rootFix;

    typeName = "Egocentric position sensor";
    type = positionSensor;

    // FIXME : max size of an entity is 10 in this case !
    // The best would be to pass the entity for computing its biggest member (root to end fix)
    float minDistanceBetweenRootFixAndThisFix = -5.0;
    float maxDistanceBetweenRootFixAndThisFix = 5.0;

    inputX = new BrainIn(minDistanceBetweenRootFixAndThisFix, maxDistanceBetweenRootFixAndThisFix);
    inputY = new BrainIn(minDistanceBetweenRootFixAndThisFix, maxDistanceBetweenRootFixAndThisFix);
    inputZ = new BrainIn(minDistanceBetweenRootFixAndThisFix, maxDistanceBetweenRootFixAndThisFix);

    brainInputs.append(inputX);
    brainInputs.append(inputY);
    brainInputs.append(inputZ);
}

PositionSensor::PositionSensor(QVariant data, Fixation* rootFix, Fixation* fixation) : Sensor(data, fixation) {
    this->rootFix = rootFix;

    inputX = new BrainIn(data.toMap()["inputX"]);
    inputY = new BrainIn(data.toMap()["inputY"]);
    inputZ = new BrainIn(data.toMap()["inputZ"]);

    brainInputs.append(inputX);
    brainInputs.append(inputY);
    brainInputs.append(inputZ);
}

QVariant PositionSensor::serialize() {
    QVariantMap data = Sensor::serialize().toMap();
    data.insert("inputX", inputX->serialize());
    data.insert("inputY", inputY->serialize());
    data.insert("inputZ", inputZ->serialize());

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
