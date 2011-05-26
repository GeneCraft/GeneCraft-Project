#include "btcylinder.h"

#include "bulletengine.h"
#include "rigidbodyorigin.h"

#define PI 3.14159265

namespace GeneLabCore {

btCylinder::btCylinder(BulletEngine *btEngine, btScalar radius, btScalar height, const btTransform &transform)
{
    this->btEngine = btEngine;
    init(radius,height,5.0,transform);
}

void btCylinder::init(btScalar radius, btScalar height, btScalar density, const btTransform &transform)
{
    this->radius = radius;
    this->height = height;

    //this->initialPosition = position;
    //this->initialEulerlRotation = EulerRotation;

    // shape
    shape = new btCylinderShape(btVector3(radius,height/2.0,radius));

    // body
    float vol = PI*radius*radius*height;
    btScalar mass = vol*density;
    btVector3 localInertia(0,0,0);
    shape->calculateLocalInertia(mass,localInertia);

    // motion state
    motionState = new btDefaultMotionState(transform);

    this->rigidBody = new btRigidBody(mass,motionState,shape,localInertia);
    this->rigidBody->setFriction(0.7);
}

void btCylinder::setup()
{
    if(btEngine != NULL && rigidBody != NULL)
        btEngine->getBulletDynamicsWorld()->addRigidBody(rigidBody);
    else
        qDebug("btSphere::setup btEngine == NULL || rigidBody == NULL");
}

}
