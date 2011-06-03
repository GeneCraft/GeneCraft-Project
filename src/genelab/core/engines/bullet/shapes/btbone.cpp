#include "btbone.h"
#include "bulletengine.h"
#include "rigidbodyorigin.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include <QDebug>
namespace GeneLabCore {
btBone::btBone(BulletEngine *btEngine, btScalar length, btScalar radius, btScalar radiusArticulation, const btTransform &transform) :
    btShape()
{
    this->btEngine = btEngine;
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
    btSphereShape* sphere = new btSphereShape(radiusArticulation);
    btTransform articulationTransform;
    articulationTransform.setIdentity();
    articulationTransform.setOrigin(btVector3(0,length/2.+ radiusArticulation, 0));
    shape->addChildShape(articulationTransform, sphere);

    // adding the cylinder to the shape
    btCylinderShape* cylinder = new btCylinderShape(btVector3(radius,length/2.0,radius));
    btTransform cylinderTransform;
    cylinderTransform.setIdentity();
    shape->addChildShape(cylinderTransform, cylinder);

    // body
    float vol = M_PI*radius*radius*length + 4/3. * M_PI * radiusArticulation * radiusArticulation * radiusArticulation;
    btScalar mass = vol*density;
    btVector3 localInertia(0,0,0);
    shape->calculateLocalInertia(mass,localInertia);

    // motion state
    motionState = new btDefaultMotionState(transform);

    this->rigidBody = new btRigidBody(mass,motionState,shape,localInertia);
    this->rigidBody->setFriction(friction);
    //qDebug() << "bien !" << this->rigidBody;
}


void btBone::setup()
{

    if(btEngine != NULL && rigidBody != NULL)
        btEngine->getBulletDynamicsWorld()->addRigidBody(rigidBody);

}

}
