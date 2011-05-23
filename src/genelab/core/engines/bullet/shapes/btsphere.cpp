#include "btsphere.h"
#include "bulletengine.h"
#include "rigidbodyorigin.h"
#include "OgreBulletDynamicsWorld.h" // TODO TRY TO DELETE !!!
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"

#define PI 3.14159265

btSphere::btSphere(BulletEngine *btEngine, btScalar radius, btVector3 position, btVector3 rotation)
{
    this->btEngine = btEngine;

    init(radius,position,2500.0,rotation);
}

void btSphere::init(btScalar radius, btVector3 position, btScalar density, btVector3 EulerRotation)
{
//    this->size = size;
//    this->initialPosition = position;
//    this->initiaEulerlRotation = EulerRotation;

    btScalar friction = 0.9;

    // shape
    this->shape = new btSphereShape(radius);

    // rotation with euler method :) (warning order Z-Y-X)
    btTransform tFinal; tFinal.setIdentity();
    tFinal.getBasis().setEulerZYX(EulerRotation.x(),EulerRotation.y(),EulerRotation.z());
    tFinal.setOrigin(position); // set position
    this->motionState = new btDefaultMotionState(tFinal);

    // body
    btScalar vol = 4*PI*radius*radius;
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
