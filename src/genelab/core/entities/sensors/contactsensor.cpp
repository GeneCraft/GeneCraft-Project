#include "contactsensor.h"

#include "body/fixation.h"
#include "world/btworld.h"
#include "factories/btshapesfactory.h"

namespace GeneLabCore {

// To create
ContactSensor::ContactSensor(Fixation * fixation) : Sensor(fixation)
{
    typeName = "Contact sensor";
    type = contact;

    collided = new BrainIn(0,1);
    world = fixation->getShapesFactory()->getWorld();

    brainInputs.append(collided);
}

// To create from serialization data
ContactSensor::ContactSensor(QVariant data, Fixation * fixation) : Sensor(fixation) {
}

// To serialize
QVariant ContactSensor::serialize()
{
    return collided->serialize();
}

//
//void ContactSensor::collideStaticObject(const btCollisionObject *object, btVector3 contactPoint){
//    collided->setValue(100.0);
//}

// To update brain inputs values
void ContactSensor::step() {

//    // Method : contactTest
//    btRigidBody* tgtBody = fixation->getRigidBody();
//    ContactSensorCallback callback(tgtBody, this);
//    world->getBulletWorld()->contactTest(tgtBody,callback);

    bool collide = false;

    // Method : Contact Information
    //Assume world->stepSimulation or world->performDiscreteCollisionDetection has been called
    int numManifolds = world->getBulletWorld()->getDispatcher()->getNumManifolds();

    for (int i=0;i<numManifolds;i++)
    {
            btPersistentManifold* contactManifold =  world->getBulletWorld()->getDispatcher()->getManifoldByIndexInternal(i);
            btCollisionObject* obA = static_cast<btCollisionObject*>(contactManifold->getBody0());
            btCollisionObject* obB = static_cast<btCollisionObject*>(contactManifold->getBody1());

            btCollisionObject* object;

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

    qDebug() << Q_FUNC_INFO << (int) collide;

    //collided->setValue((int)collide);
}

}
