#include "smellsensor.h"

#include <QDebug>

#include "bullet/rigidbodyorigin.h"
#include "body/fixation.h"

#include "BulletCollision/CollisionShapes/btSphereShape.h"
#include "btBulletDynamicsCommon.h"

#include "engines/bullet/bulletengine.h"
#include "factories/btshapesfactory.h"
#include "factories/btfactory.h"
#include "world/btworld.h"

namespace GeneLabCore {

SmellSensor::SmellSensor(Fixation *fixation, QString typeName, SensorType type, RigidBodyOrigin::RigidBodyType smellType, btScalar smellRadius) : Sensor(fixation)
{
    this->typeName      = typeName;
    this->type          = type;
    this->smellType     = smellType;
    this->smellRadius   = smellRadius;

    intensityInput = new BrainIn(0, smellRadius);

    brainInputs.append(intensityInput);

    // TODO create the rigid to do contact test...
    btMotionState *motion = new btDefaultMotionState();
    btCollisionShape *shape = new btSphereShape(smellRadius);
    smellSphere = new btRigidBody(0,motion,shape);

    callback = new ContactSensorCallback(smellSphere, this);
}

// To create from serialization data
SmellSensor::SmellSensor(QVariant data, Fixation * fixation) : Sensor(data, fixation)
{
    intensityInput = new BrainIn(data.toMap()["intensityInput"]);
    brainInputs.append(intensityInput);
}

// To serialize
QVariant SmellSensor::serialize()
{
    QVariantMap data = Sensor::serialize().toMap();
    data.insert("intensityInput", intensityInput->serialize());
    return data;
}

void SmellSensor::step() {

    //qDebug() << "STEP START";

    nearestBodySmelled = NULL;
    distanceOfNearestBodySmelled = smellRadius;

    btVector3 origin = fixation->getRigidBody()->getWorldTransform().getOrigin();
    smellSphere->getWorldTransform().setOrigin(origin);

    /* ContactTest
    Bullet 2.76 onwards let you perform an instant query on the world (btCollisionWorld or btDiscreteDynamicsWorld)
    using the contactTest query. The contactTest query will peform a collision test against all overlapping objects in
    the world, and produces the results using a callback. The query object doesn't need to be part of the world.
    In order for an efficient query on large worlds, it is important that the broadphase aabbTest is accelerated,
    for example using the btDbvtBroadphase or btAxisSweep3 broadphase.
    http://www.bulletphysics.org/mediawiki-1.5.8/index.php?title=Collision_Callbacks_and_Triggers
    */

    // USAGE:
    fixation->getShapesFactory()->getWorld()->getBulletWorld()->contactTest(smellSphere,*callback); // will call contactCallBack...


    // IF WE KNOW SMELLED OBJECTS WE CAN ALSO USE CONTACT PAIR TEST
    /*contactPairTest
    Bullet 2.76 onwards provides the contactPairTest to perform collision detection between two specific collision objects only.
    Contact results are passed on using the provided callback. They don't need to be inserted in the world.
    See btCollisionWorld::contactPairTest in Bullet/src/BulletCollision/CollisionDispatch/btCollisionWorld.h for implementation details.
    http://www.bulletphysics.org/mediawiki-1.5.8/index.php?title=Collision_Callbacks_and_Triggers
    */

    //if(nearestBodySmelled) {
        intensityInput->setValue(smellRadius - distanceOfNearestBodySmelled);
        //qDebug() << "Smell intensity :" << smellRadius - distanceOfNearestBodySmelled;
    //}

    //qDebug() << "STEP END";
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
    btScalar distance = fixation->getRigidBody()->getWorldTransform().getOrigin().distance(body->getWorldTransform().getOrigin());
    // qDebug() << "Object smelled at " << distance << " meters";

    // keep only the nearest object
    if(distance < distanceOfNearestBodySmelled) {
        nearestBodySmelled = body;
        distanceOfNearestBodySmelled = distance;
    }
}

}
