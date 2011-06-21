#include "btbone.h"
#include "world/btworld.h"
#include "bullet/bulletengine.h"
#include "bullet/rigidbodyorigin.h"
#include <QDebug>

namespace GeneLabCore {
btBone::btBone(btWorld *world, btScalar length, btScalar radius, btScalar radiusArticulation, const btTransform &transform) :
    btShape(world)
{
    this->init(length, radius, radiusArticulation, 5.0, transform);
}

void btBone::init(btScalar length,
                  btScalar radius,
                  btScalar radiusArticulation,
                  btScalar density,
                  const btTransform &transform) {
    btScalar friction = 1;

    // shape
    this->shape = new btCompoundShape(true);

    // Adding the sphere to the shape !
    sphereShape = new btSphereShape(radiusArticulation);
    btTransform articulationTransform;
    articulationTransform.setIdentity();
    articulationTransform.setOrigin(btVector3(0,length/2.+ radiusArticulation, 0));
    shape->addChildShape(articulationTransform, sphereShape);

    // adding the cylinder to the shape
    cylinderShape = new btCylinderShape(btVector3(radius,length/2.0,radius));
    btTransform cylinderTransform; cylinderTransform.setIdentity();
    shape->addChildShape(cylinderTransform, cylinderShape);

    // body
    float vol = M_PI*radius*radius*length + 4/3. * M_PI * radiusArticulation * radiusArticulation * radiusArticulation;
    btScalar mass = vol*density;
    btVector3 localInertia(0,0,0);
    shape->calculateLocalInertia(mass,localInertia);

    // motion state
    motionState = new btDefaultMotionState(transform);

    this->rigidBody = new btRigidBody(mass,motionState,shape,localInertia);
    this->rigidBody->setFriction(friction);
}


void btBone::setup()
{
    if(world != NULL && rigidBody != NULL)
        world->getBulletWorld()->addRigidBody(rigidBody);
}

void btBone::setSize(btScalar radius, btScalar length)
{
    if(cylinderShape != NULL) {


        //shape->recalculateLocalAabb();
        shape->removeChildShape(cylinderShape);

        cylinderShape->setLocalScaling(btVector3(radius*4,length,radius*4));
        btTransform cylinderTransform; cylinderTransform.setIdentity();
        shape->addChildShape(cylinderTransform,cylinderShape);

        // body
        //btVector3 localInertia(0,0,0);
        //shape->calculateLocalInertia(1.0,localInertia); // TODO mass
    }
    else
        qDebug() << Q_FUNC_INFO << ", shape == NULL";
}

}
