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

#ifndef BTOSHAPESFACTORY_H
#define BTOSHAPESFACTORY_H

#include "genecraftcoreclasses.h"
#include "btshapesfactory.h"
#include "bulletogre/btoworld.h"

namespace GeneCraftCore {

class btoShapesFactory : public btShapesFactory
{
public:
    btoShapesFactory(BulletOgreEngine *btoEngine);

    virtual void setWorld(btoWorld* world) { this->world = world; }

    virtual btBox *createBox(btVector3 size, const btTransform &transform, const btScalar density, QVariant params = QVariant());
    virtual btSphere *createSphere(btScalar radius, const btTransform &transform, const btScalar density, QVariant params = QVariant());
    virtual btCylinder *createCylinder(btScalar radius, btScalar height, const btTransform &transform, const btScalar density, QVariant params = QVariant());
    virtual btBone *createBone(btScalar length, btScalar radius, btScalar radiusArticulation, const btTransform &transform, QVariant params = QVariant());
protected:
    BulletOgreEngine *btoEngine;
};

}

#endif // BTOSHAPESFACTORY_H
