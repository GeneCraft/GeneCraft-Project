#include "distancesensor.h"

#include <QVariantMap>
#include "body/fixation.h"
#include "factories/btshapesfactory.h"
#include "world/btworld.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"

#define MAX_DISTANCE 100.0f

namespace GeneLabCore {

DistanceSensor::DistanceSensor(Fixation *fixation, btQuaternion orientation) : Sensor(fixation) {

    typeName = "Distance sensor";
    type = distanceSensor;

    this->orientation = orientation;

    distanceInput = new BrainIn(0, MAX_DISTANCE);

    brainInputs.append(distanceInput);
}

DistanceSensor::DistanceSensor(QVariant data, Fixation* fixation) : Sensor(data, fixation) {

    distanceInput = new BrainIn(data.toMap()["distanceInput"]);
    brainInputs.append(distanceInput);

    QVariantMap orientationMap = data.toMap()["orientation"].toMap();
    orientation = btQuaternion(orientationMap["x"].toFloat(),orientationMap["y"].toFloat(),orientationMap["z"].toFloat(),orientationMap["w"].toFloat());
}

QVariant DistanceSensor::serialize() {

    QVariantMap data = Sensor::serialize().toMap();
    data.insert("distanceInput", distanceInput->serialize());

    QVariantMap orientationMap;
    orientationMap.insert("x",(double)orientation.x());
    orientationMap.insert("y",(double)orientation.y());
    orientationMap.insert("z",(double)orientation.z());
    orientationMap.insert("w",(double)orientation.w());
    data.insert("orientation",orientationMap);

    return data;
}

void DistanceSensor::step() {

    // under mouse pointer
    btVector3 rayFrom = fixation->getRigidBody()->getWorldTransform().getOrigin();

    // TODO HELP CYP !
    btVector3 rayTo = btVector3(0,0,0);

    // find the closest rigidBody with raycast
    btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom,rayTo);
    fixation->getShapesFactory()->getWorld()->getBulletWorld()->rayTest(rayFrom,rayTo,rayCallback);
    if(rayCallback.hasHit())
    {
        btRigidBody* body = btRigidBody::upcast(rayCallback.m_collisionObject);

        if(body) {

            //if(!(body->isStaticObject() || body->isKinematicObject()))
            {

                btScalar distance = rayFrom.distance(body->getWorldTransform().getOrigin());
                distanceInput->setValue(distance);
                return;
            }
        }
    }

    distanceInput->setValue(0);
}

}
