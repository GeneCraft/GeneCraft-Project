#include "btsphere.h"

#include <QDebug>

#include "world/btworld.h"

#include "bullet/bulletengine.h"
#include "bullet/rigidbodyorigin.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"

#define PI 3.14159265

namespace GeneLabCore {

btSphere::btSphere(btWorld *world, btScalar radius, const btTransform &transform) : btShape(world), shape(NULL)
{
    init(radius, 5, transform);
}

btSphere::~btSphere() {
    world->getBulletWorld()->removeRigidBody(rigidBody);
    delete shape;
    delete motionState;
}

void btSphere::init(btScalar radius, btScalar density, const btTransform &transform)
{
//    this->size = size;
//    this->initialPosition = position;
//    this->initiaEulerlRotation = EulerRotation;

    btScalar friction = 0.3;

    // shape
    this->shape = new btSphereShape(radius);

    // rotation with euler method :) (warning order Z-Y-X)
    this->motionState = new btDefaultMotionState(transform);

    // body
    btScalar mass = computeMass();
    btVector3 fallInertia(0,0,0);
    this->shape->calculateLocalInertia(mass,fallInertia);
    this->rigidBody = new btRigidBody(mass,this->motionState,this->shape,fallInertia);
    this->rigidBody->setFriction(friction);

    RigidBodyOrigin *origin = new RigidBodyOrigin(RigidBodyOrigin::BASIC_SHAPE,(QObject *)this);
    rigidBody->setUserPointer(origin);
}

btScalar btSphere::getMass() const
{
    return btScalar(1.0)/rigidBody->getInvMass();
}

btScalar btSphere::computeMass() const
{
    // volume * density
    // TODO MOVE 5 into density !!
    return 4/3.*M_PI*shape->getRadius()*shape->getRadius()*shape->getRadius() * 5 ;
}

void btSphere::setup()
{
    if(world != NULL && rigidBody != NULL)
        world->getBulletWorld()->addRigidBody(rigidBody);
    else
        qDebug("btSphere::setup btEngine == NULL || rigidBody == NULL");
}

void btSphere::setRadius(btScalar radius)
{
    if(shape != NULL)
    {
        delete shape;
        shape = new btSphereShape(radius);
        rigidBody->setCollisionShape(shape);

        btScalar mass = computeMass();
        btVector3 intertia(0,0,0);
        this->shape->calculateLocalInertia(mass,intertia);
        this->rigidBody->setMassProps(mass,intertia);
    }
}

}
