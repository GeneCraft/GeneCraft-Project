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

#include "contactsensor.h"

#include "body/fixation.h"
#include "bullet/btworld.h"
#include "btshapesfactory.h"
#include "tools.h"

namespace GeneCraftCore {

// To create
ContactSensor::ContactSensor(Fixation * fixation) : Sensor(fixation)
{
    typeName = "Contact sensor";
    type = contactSensor;

    collided = new BrainIn(0,1);
    //world = fixation->getShapesFactory()->getWorld();

    brainInputs.append(collided);
}

// To create from serialization data
ContactSensor::ContactSensor(QVariant data, Fixation * fixation) : Sensor(data, fixation) {

    collided = new BrainIn(data.toMap()["collisionInput"]);

    brainInputs.append(collided);
}

// To serialize
QVariant ContactSensor::serialize()
{
    QVariantMap data = Sensor::serialize().toMap();
    data.insert("collisionInput", collided->serialize());
    return data;
}

QVariant ContactSensor::generateEmpty()
{
    QVariantMap data = Sensor::generateEmpty("Contact sensor", contactSensor).toMap();

    BrainIn collided(0,1);

    collided.connectRandomly();

    data.insert("collisionInput", collided.serialize());

    return data;
}

//
//void ContactSensor::collideStaticObject(const btCollisionObject *object, btVector3 contactPoint){
//    collided->setValue(100.0);
//}

// To update brain inputs values
void ContactSensor::step() {

    // Method : contactTest
//    btRigidBody* tgtBody = fixation->getRigidBody();
//    ContactSensorCallback callback(tgtBody, this);
//    world->getBulletWorld()->contactTest(tgtBody,callback);


    // Method : Contact Information
    bool collide = false;

    //Assume world->stepSimulation or world->performDiscreteCollisionDetection has been called
    int numManifolds = fixation->getShapesFactory()->getWorld()->getBulletWorld()->getDispatcher()->getNumManifolds();

    for (int i=0;i<numManifolds;i++)
    {
            btPersistentManifold* contactManifold =  fixation->getShapesFactory()->getWorld()->getBulletWorld()->getDispatcher()->getManifoldByIndexInternal(i);
            btCollisionObject* obA = static_cast<btCollisionObject*>(contactManifold->getBody0());
            btCollisionObject* obB = static_cast<btCollisionObject*>(contactManifold->getBody1());

            // contact ?
            if(contactManifold->getNumContacts() > 0)
            {
                btCollisionObject* object;

                // get object in contact
                if(obA == (btCollisionObject *) fixation->getRigidBody())
                    object = obB;
                else if(obB == (btCollisionObject *) fixation->getRigidBody())
                    object = obA;
                else
                    continue;

                if(object->isStaticObject()){
                    collide = true;
                    break;
                }
            }

//            // more info
//            int numContacts = contactManifold->getNumContacts();
//            for (int j=0;j<numContacts;j++)
//            {
//                    btManifoldPoint& pt = contactManifold->getContactPoint(j);
//                    if (pt.getDistance()<0.f)
//                    {
//                            const btVector3& ptA = pt.getPositionWorldOnA();
//                            const btVector3& ptB = pt.getPositionWorldOnB();
//                            const btVector3& normalOnB = pt.m_normalWorldOnB;
//                    }
//            }
    }

    collided->setValue((int)collide);
}

}
