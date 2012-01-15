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

#include "btcylinder.h"

#include "bullet/btworld.h"

#include "bullet/bulletengine.h"
#include "bullet/rigidbodyorigin.h"
#include <QDebug>

namespace GeneCraftCore {

btCylinder::btCylinder(btWorld *world, btScalar radius, btScalar height, const btTransform &transform, const btScalar density) :
        btShape(world), shape(NULL)
{
    init(radius,height,density,transform);
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
    btScalar vol = SIMD_PI*radius*radius*height;
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
