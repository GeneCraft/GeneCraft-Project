/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "btsphere.h"

#include <QDebug>

#include "bullet/btworld.h"

#include "bullet/bulletengine.h"
#include "bullet/rigidbodyorigin.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"

#include "BulletCollision/CollisionShapes/btSphereShape.h"
#include "LinearMath/btDefaultMotionState.h"

#include "BulletDynamics/Dynamics/btRigidBody.h"

namespace GeneCraftCore {

btSphere::btSphere(btWorld *world, btScalar radius, const btTransform &transform, const btScalar density)
    : Sphere(world, radius, transform, density), shape(NULL)
{
    init(radius, density, transform);
}

btSphere::~btSphere() {
    world->getBulletWorld()->removeRigidBody(rigidBody);
    delete rigidBody;
    delete shape;
    delete motionState;
    delete origin;
}

void btSphere::init(btScalar radius, btScalar density, const btTransform &transform)
{
    this->density = density;
//    this->size = size;
//    this->initialPosition = position;
//    this->initiaEulerlRotation = EulerRotation;

    // shape
    this->shape = new btSphereShape(radius);

    // rotation with euler method :) (warning order Z-Y-X)
    this->motionState = new btDefaultMotionState(transform);

    // body
    btScalar mass = computeMass();
    btVector3 fallInertia(0,0,0);
    this->shape->calculateLocalInertia(mass,fallInertia);
    this->rigidBody = new btRigidBody(mass,this->motionState,this->shape,fallInertia);

    origin = new RigidBodyOrigin(RigidBodyOrigin::BASIC_SHAPE,(QObject *)this);
    rigidBody->setUserPointer(origin);
}

btScalar btSphere::getMass() const
{
    return btScalar(1.0)/rigidBody->getInvMass();
}

btScalar btSphere::computeMass() const
{
    // volume * density
    return 4/3.*SIMD_PI*shape->getRadius()*shape->getRadius()*shape->getRadius() * density ;
}

void btSphere::setup()
{
    if(world != NULL && rigidBody != NULL)
        world->getBulletWorld()->addRigidBody(rigidBody);
    else
        qDebug() << Q_FUNC_INFO << "btSphere::setup btEngine == NULL || rigidBody == NULL";
}

void btSphere::setRadius(btScalar radius)
{
    if(shape != NULL)
    {
        delete shape;
        shape = new btSphereShape(radius);
        rigidBody->setCollisionShape(shape);

        btScalar mass = computeMass();
        btVector3 intertia;
        this->shape->calculateLocalInertia(mass,intertia);
        this->rigidBody->setMassProps(mass,intertia);
    }
}

}
