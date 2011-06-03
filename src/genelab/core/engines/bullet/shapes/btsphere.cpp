#include "btsphere.h"

#include <QDebug>
#include "bulletengine.h"
#include "rigidbodyorigin.h"
#include "OgreBulletDynamicsWorld.h" // TODO TRY TO DELETE !!!
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"

#define PI 3.14159265

namespace GeneLabCore {

btSphere::btSphere(BulletEngine *btEngine, btScalar radius, const btTransform &transform)
{
    this->btEngine = btEngine;

    init(radius, 2, transform);
}

void btSphere::init(btScalar radius, btScalar density, const btTransform &transform)
{
//    this->size = size;
//    this->initialPosition = position;
//    this->initiaEulerlRotation = EulerRotation;

    btScalar friction = 1;

    // shape
    this->shape = new btSphereShape(radius);

    // rotation with euler method :) (warning order Z-Y-X)
    this->motionState = new btDefaultMotionState(transform);

    // body
    btScalar vol = 4/3.*M_PI*radius*radius*radius;
    btScalar mass = vol*density;
    btVector3 fallInertia(0,0,0);
    this->shape->calculateLocalInertia(mass,fallInertia);
    this->rigidBody = new btRigidBody(mass,this->motionState,this->shape,fallInertia);
    this->rigidBody->setFriction(friction);

    RigidBodyOrigin *origin = new RigidBodyOrigin(RigidBodyOrigin::BASIC_SHAPE,(QObject *)this);
    rigidBody->setUserPointer(origin);
}

void btSphere::setup()
{
    if(btEngine != NULL && rigidBody != NULL)
        btEngine->getBulletDynamicsWorld()->addRigidBody(rigidBody);
    else
        qDebug("btSphere::setup btEngine == NULL || rigidBody == NULL");
}

}
