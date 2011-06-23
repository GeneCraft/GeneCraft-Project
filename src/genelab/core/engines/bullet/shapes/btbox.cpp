#include "btbox.h"

#include "bullet/bulletengine.h"
#include "bullet/rigidbodyorigin.h"
#include "world/btworld.h"

namespace GeneLabCore {

btBox::btBox(btWorld *world, btVector3 size, const btTransform &transform) : btShape(world)
{
    init(size, 5.0, transform);
}

btBox::~btBox() {
    this->world->getBulletWorld()->removeRigidBody(rigidBody);
    delete shape;
    delete motionState;
}

void btBox::init(btVector3 size, btScalar density, const btTransform &transform)
{
//    this->size = size;
//    this->initialPosition = position;
//    this->initiaEulerlRotation = EulerRotation;

    btScalar friction = 0.9;

    // shape
    this->shape = new btBoxShape(btVector3(size.x()/2.0,size.y()/2.0,size.z()/2.0));

    this->motionState = new btDefaultMotionState(transform);

    // body
    btScalar mass = size.x()*size.y()*size.z()*density; // volumic mass = 1500kg/m3
    btVector3 fallInertia(0,0,0);
    this->shape->calculateLocalInertia(mass,fallInertia);
    this->rigidBody = new btRigidBody(mass,this->motionState,this->shape,fallInertia);
    this->rigidBody->setFriction(friction);

    RigidBodyOrigin *origin = new RigidBodyOrigin(RigidBodyOrigin::BASIC_SHAPE,(QObject *)this);
    rigidBody->setUserPointer(origin);
}

void btBox::setup()
{
    if(world != NULL && rigidBody != NULL)
        world->getBulletWorld()->addRigidBody(rigidBody);
    else
        qDebug("btSphere::setup btEngine == NULL || rigidBody == NULL");
}

}
