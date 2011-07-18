#include "btcylinder.h"

#include "world/btworld.h"

#include "bullet/bulletengine.h"
#include "bullet/rigidbodyorigin.h"
#include <QDebug>

#define PI 3.14159265

namespace GeneLabCore {

btCylinder::btCylinder(btWorld *world, btScalar radius, btScalar height, const btTransform &transform) :
        btShape(world), shape(NULL)
{
    init(radius,height,5.0,transform);
}

btCylinder::~btCylinder() {
    this->world->getBulletWorld()->removeRigidBody(rigidBody);
    delete rigidBody;
    delete shape;
    delete motionState;
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
    if(world != NULL && rigidBody != NULL)
        world->getBulletWorld()->addRigidBody(rigidBody);
    else
         qDebug() << Q_FUNC_INFO << ", btEngine == NULL || rigidBody == NULL";
}

void btCylinder::setSize(btScalar radius, btScalar height)
{
    if(shape != NULL)
        shape->setLocalScaling(btVector3(radius,height/2.0,radius));
    else
        qDebug() << Q_FUNC_INFO << ", shape == NULL";
}

}
