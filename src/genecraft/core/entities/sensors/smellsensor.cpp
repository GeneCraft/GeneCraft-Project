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

#include "smellsensor.h"

#include <QDebug>

#include "bullet/rigidbodyorigin.h"
#include "body/fixation.h"

#include "BulletCollision/CollisionShapes/btSphereShape.h"
#include "btBulletDynamicsCommon.h"

#include "engines/bullet/bulletengine.h"
#include "btshapesfactory.h"
#include "btfactory.h"
#include "bullet/btworld.h"

namespace GeneCraftCore {

SmellSensor::SmellSensor(Fixation *fixation, QString typeName, SensorType type,
                         RigidBodyOrigin::RigidBodyType smellType, btScalar smellRadius) :
    Sensor(fixation)
{
    this->typeName      = typeName;
    this->type          = type;
    this->smellType     = smellType;
    this->radiusOfSmell   = smellRadius;

    intensityInput = new BrainIn(0, smellRadius);
    brainInputs.append(intensityInput);

    createRigidBody(smellRadius);
}

// To create from serialization data
SmellSensor::SmellSensor(QVariant data, RigidBodyOrigin::RigidBodyType smellType, Fixation * fixation) : Sensor(data, fixation)
{
    QVariantMap map = data.toMap();

    this->smellType =  smellType;

    intensityInput = new BrainIn(map["intensityInput"]);
    // the max value equals radius of smell !
    radiusOfSmell = map["radiusOfSmell"].toFloat();
    //intensityInput->setMax(radiusOfSmell);
    brainInputs.append(intensityInput);


    createRigidBody(radiusOfSmell);
}
SmellSensor::~SmellSensor() {
    fixation->getShapesFactory()->getWorld()->getBulletWorld()->removeRigidBody(smellSphere);
    delete callback;
    delete smellSphere;
    delete shape;
    delete motion;
}

void SmellSensor::createRigidBody(btScalar radiusOfSmell) {
    // create the rigid to do contact test...
    motion = new btDefaultMotionState();
    shape = new btSphereShape(radiusOfSmell);
    smellSphere = new btRigidBody(0,motion,shape);

    callback = new ContactSensorCallback(smellSphere, this);
}

// To serialize
QVariant SmellSensor::serialize()
{
    QVariantMap data = Sensor::serialize().toMap();
    data.insert("intensityInput", intensityInput->serialize());
    data.insert("radiusOfSmell", (double) radiusOfSmell);

    return data;
}

void SmellSensor::step() {

    //qDebug() << "STEP START";
    // TODO: fix use physobject
/*
    nearestBodySmelled = NULL;
    distanceOfNearestBodySmelled = radiusOfSmell;

    btVector3 origin = fixation->getRigidBody()->getWorldTransform().getOrigin();
    smellSphere->getWorldTransform().setOrigin(origin);


    // USAGE:
    fixation->getShapesFactory()->getWorld()->getBulletWorld()->contactTest(smellSphere,*callback); // will call contactCallBack...


    // IF WE KNOW SMELLED OBJECTS WE CAN ALSO USE CONTACT PAIR TEST

    //if(nearestBodySmelled) {
        intensityInput->setValue(radiusOfSmell - distanceOfNearestBodySmelled);
        //qDebug() << "Smell intensity :" << smellRadius - distanceOfNearestBodySmelled;
    //}

    //qDebug() << "STEP END";
    */
}

void SmellSensor::contactCallBack(const btCollisionObject *body) {

    const btRigidBody* rigidBody = btRigidBody::upcast(body);
    if(rigidBody->getUserPointer()) {
        RigidBodyOrigin* origin = static_cast<RigidBodyOrigin*>(rigidBody->getUserPointer());
        if(origin && origin->getObject())
            if(origin->getType() == smellType)
                objectSmelled(rigidBody);
    }
}

void SmellSensor::objectSmelled(const btRigidBody *body) {

    // distance between sensor and object smelled
    // TODO: fix use physobject
    btScalar distance = 1;//fixation->getRigidBody()->getWorldTransform().getOrigin().distance(body->getWorldTransform().getOrigin());
    // qDebug() << "Object smelled at " << distance << " meters";

    // keep only the nearest object
    if(distance < distanceOfNearestBodySmelled) {
        nearestBodySmelled = body;
        distanceOfNearestBodySmelled = distance;
    }
}

QVariant SmellSensor::generateEmpty(QString typeName, SensorType type, btScalar radiusOfSmell)
{
    QVariantMap data = Sensor::generateEmpty(typeName, type).toMap();

    BrainIn intensity(0, radiusOfSmell);
    intensity.connectRandomly();
    data.insert("intensityInput", intensity.serialize());
    data.insert("radiusOfSmell", (double) radiusOfSmell);

    return data;
}

}
