#include "btbone.h"
#include "world/btworld.h"
#include "bullet/bulletengine.h"
#include "bullet/rigidbodyorigin.h"
#include <QDebug>

namespace GeneLabCore {

const btScalar btBone::DENSITY = 1010.0; // Average body density

btBone::btBone(btWorld *world, btScalar length, btScalar radius, btScalar radiusArticulation, const btTransform &transform) :
    btShape(world)
{
    this->init(length, radius, radiusArticulation, btBone::DENSITY, transform);
}

btBone::~btBone() {
    this->world->getBulletWorld()->removeRigidBody(rigidBody);
    shape->removeChildShape(cylinderShape);
    shape->removeChildShape(sphereShape);
    delete rigidBody;
    delete shape;
    delete motionState;
    delete cylinderShape;
    delete sphereShape;
}

void btBone::init(btScalar length,
                  btScalar radius,
                  btScalar radiusArticulation,
                  btScalar density,
                  const btTransform &transform) {

    btScalar friction = 0.7;

    // shape
    this->shape = new btCompoundShape(true); 

    // Adding the sphere to the shape !
    sphereShape = new btSphereShape(radiusArticulation);
    btTransform articulationTransform;
    articulationTransform.setIdentity();
    articulationTransform.setOrigin(btVector3(0,length*0.5 + radiusArticulation, 0));
    shape->addChildShape(articulationTransform, sphereShape);

    // adding the cylinder to the shape
    cylinderShape = new btCylinderShape(btVector3(radius,length*0.5,radius));
    btTransform cylinderTransform; cylinderTransform.setIdentity();
    shape->addChildShape(cylinderTransform, cylinderShape);

    // body
    float vol = M_PI*radius*radius*length + 4/3. * M_PI * radiusArticulation * radiusArticulation * radiusArticulation;
    btScalar mass = vol*density;
    btVector3 localInertia(0,0,0);
    shape->calculateLocalInertia(mass,localInertia);

    btTransform principal;
    principal.setIdentity();
    btVector3 inertia(0,0,0);

    // Masse de l'os, masse de la fixation
    float massBone = M_PI*radius*radius*length*density;
    float massSphere =  4/3. * M_PI * radiusArticulation * radiusArticulation * radiusArticulation * density;
    float childMasses[2] = {massSphere,massBone};
    // TODO Use this information to shift object inside the compound
    // Set the shift in the rigid objets
    // And set the shift in all childs fixations
    // And parent constraint of bone
    // ARG, lot of todo to get the center of gravity work properly
    shape->calculatePrincipalAxisTransform(childMasses, principal, inertia);

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
    if(cylinderShape != NULL && sphereShape != NULL) {

        // remove shapes from compound
        shape->removeChildShape(sphereShape);
        shape->removeChildShape(cylinderShape);

        // re-add fixation
        btTransform localFix; localFix.setIdentity();
        localFix.setOrigin(btVector3(0, length*0.5 + sphereShape->getRadius(), 0));
        shape->addChildShape(localFix,sphereShape);

        // adapt bone size + re-add
        delete cylinderShape;
        cylinderShape = new btCylinderShape(btVector3(radius,length*0.5,radius));
        //cylinderShape->setImplicitShapeDimensions(btVector3(radius, length/2, radius));
        btTransform localBone; localBone.setIdentity();
        shape->addChildShape(localBone,cylinderShape);

        // set body mass
        btScalar volBone    = M_PI*getRadius()*getRadius()*getLength();
        btScalar volFix     = 4/3. * M_PI * cylinderShape->getRadius() * cylinderShape->getRadius() * cylinderShape->getRadius();
        btScalar mass = volBone*DENSITY + volFix*DENSITY; // TODO different density between fix and bone
        btVector3 localInertia;
        shape->calculateLocalInertia(mass,localInertia);
        rigidBody->setMassProps(mass,localInertia);
    }
    else
        qDebug() << Q_FUNC_INFO << ", cylinderShape == NULL or sphereShape == NULL";
}

void btBone::setEndFixationRadius(btScalar fixationRadius)
{
    if(cylinderShape != NULL && sphereShape != NULL) {

        // remove shapes from compound
        shape->removeChildShape(sphereShape);
        shape->removeChildShape(cylinderShape);

        // adapt fixation + re-add
        delete sphereShape;
        sphereShape = new btSphereShape(fixationRadius);
        btTransform localFix; localFix.setIdentity();
        localFix.setOrigin(btVector3(0, getLength()*0.5 + fixationRadius, 0));
        shape->addChildShape(localFix,sphereShape);

        // bone
        btTransform localBone; localBone.setIdentity();
        shape->addChildShape(localBone,cylinderShape);

        // set body mass
        btScalar volBone    = M_PI*getRadius()*getRadius()*getLength();
        btScalar volFix     = 4/3. * M_PI * cylinderShape->getRadius() * cylinderShape->getRadius() * cylinderShape->getRadius();
        btScalar mass = volBone*DENSITY + volFix*DENSITY; // TODO different density between fix and bone
        btVector3 localInertia;
        shape->calculateLocalInertia(mass,localInertia);
        rigidBody->setMassProps(mass,localInertia);
    }
    else
        qDebug() << Q_FUNC_INFO << ", cylinderShape == NULL or sphereShape == NULL";
}

}
