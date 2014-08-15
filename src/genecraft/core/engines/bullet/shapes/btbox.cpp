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

#include "btbox.h"

#include <QDebug>
#include "bullet/bulletengine.h"
#include "bullet/rigidbodyorigin.h"
#include "bullet/btworld.h"

namespace GeneCraftCore {

btBox::btBox(btWorld *world, btVector3 size, const btTransform &transform, const btScalar density) : btShape(world)
{
    init(size, transform, density);
}

btBox::~btBox() {
    this->world->getBulletWorld()->removeRigidBody(rigidBody);
    delete rigidBody;
    delete shape;
    delete motionState;
    delete origin;
}

void btBox::init(btVector3 size, const btTransform &transform, const btScalar density)
{
//    this->size = size;
//    this->initialPosition = position;
//    this->initiaEulerlRotation = EulerRotation;

    btScalar friction = 0.9;

    qDebug() << transform.getOrigin().x();
    qDebug() << transform.getOrigin().y();
    qDebug() << transform.getOrigin().z();

    // shape
    this->shape = new btBoxShape(btVector3(size.x()/2.0,size.y()/2.0,size.z()/2.0));
    this->motionState = new btDefaultMotionState(transform);

    // body
    btScalar mass = size.x()*size.y()*size.z()*density; // volumic mass = 1500kg/m3
    btVector3 fallInertia(0,0,0);
    this->shape->calculateLocalInertia(mass,fallInertia);
    this->rigidBody = new btRigidBody(mass,this->motionState,this->shape,fallInertia);
    this->rigidBody->setFriction(friction);

    origin = new RigidBodyOrigin(RigidBodyOrigin::BASIC_SHAPE,(QObject *)this);
    rigidBody->setUserPointer(origin);
}

void btBox::setup()
{
    if(world != NULL && rigidBody != NULL)
        world->getBulletWorld()->addRigidBody(rigidBody);
    else
        qDebug() << Q_FUNC_INFO << "btEngine == NULL || rigidBody == NULL";
}

}
