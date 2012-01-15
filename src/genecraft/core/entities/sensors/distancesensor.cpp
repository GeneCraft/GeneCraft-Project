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

#include "distancesensor.h"

#include <QVariantMap>
#include "body/fixation.h"
#include "btshapesfactory.h"
#include "bullet/btworld.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"

#define MAX_DISTANCE 4.0f

namespace GeneCraftCore {

DistanceSensor::DistanceSensor(Fixation *fixation, btScalar yAxis, btScalar zAxis) : Sensor(fixation) {

    typeName = "Distance sensor";
    type = distanceSensor;

    this->yAxis = yAxis;
    this->zAxis = zAxis;

    distanceInput = new BrainIn(0, MAX_DISTANCE);

    brainInputs.append(distanceInput);
}

DistanceSensor::DistanceSensor(QVariant data, Fixation* fixation) : Sensor(data, fixation) {

    distanceInput = new BrainIn(data.toMap()["distanceInput"]);
    brainInputs.append(distanceInput);

    QVariantMap orientationMap = data.toMap()["orientation"].toMap();

    yAxis = orientationMap["y"].toFloat();
    zAxis = orientationMap["z"].toFloat();
}

QVariant DistanceSensor::serialize() {

    QVariantMap data = Sensor::serialize().toMap();
    data.insert("distanceInput", distanceInput->serialize());

    QVariantMap orientationMap;
    orientationMap.insert("y",(double)yAxis);
    orientationMap.insert("z",(double)zAxis);
    data.insert("orientation",orientationMap);

    return data;
}

void DistanceSensor::step() {

    // compute orientation of raycast
    btVector3 rayFrom = fixation->getRigidBody()->getWorldTransform().getOrigin();
    btQuaternion local1;
    local1.setRotation(btVector3(0, 1, 0), yAxis);
    btQuaternion local2;
    local2.setRotation(btVector3(0, 0, 1), zAxis);
    local1 *= local2;

    btTransform fixTransform = fixation->getRigidBody()->getWorldTransform();
    fixTransform.setRotation(fixTransform * local1);
    btVector3 rayTo = btVector3(0,MAX_DISTANCE,0);
    btVector3 realRayTo = fixTransform(rayTo);

    // find the closest rigidBody with raycast
    btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom,realRayTo);
    fixation->getShapesFactory()->getWorld()->getBulletWorld()->rayTest(rayFrom,realRayTo,rayCallback);
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

QVariant DistanceSensor::generateEmpty()
{
    QVariantMap data = Sensor::generateEmpty("Distance sensor", distanceSensor).toMap();

    BrainIn distanceInput(0,MAX_DISTANCE);
    distanceInput.connectRandomly();
    data.insert("distanceInput", distanceInput.serialize());

    return data;
}

}
