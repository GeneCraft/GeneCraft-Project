#include "positionsensor.h"

#include "brainin.h"
#include "fixation.h"
#include <QDebug>
#include <QVariant>

namespace GeneLabCore {
PositionSensor::PositionSensor(Fixation * rootFix, Fixation *fixation) : Sensor(fixation)
{
    this->rootFix = rootFix;

    typeName = "Egocentric position sensor";
    type = position;

    // WARNING : max size of an entity is 200 in this case ! FIXME
    // 200 c'est grand de toute façon :D
    // Je dirais plutot 20 !
    inputX = new BrainIn(-5.0, 5.0);
    inputY = new BrainIn(-5.0, 5.0);
    inputZ = new BrainIn(-5.0, 5.0);

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

void PositionSensor::step()
{
    btTransform inverseRootTransform = rootFix->getRigidBody()->getWorldTransform().inverse();
    btVector3 distance = inverseRootTransform(fixation->getRigidBody()->getWorldTransform().getOrigin());

    inputX->setValue(distance.x());
    inputY->setValue(distance.y());
    inputZ->setValue(distance.z());
}
}
