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

#include "btoshapesfactory.h"

#include "bulletogre/btoworld.h"

#include "bulletogre/bulletogreengine.h"

#include "ogre/shapes/obox.h"
#include "ogre/shapes/osphere.h"
#include "ogre/shapes/ocylinder.h"
#include "ogre/shapes/oPhysBone.h"

#include "base/shapes/physbone.h"
#include "base/shapes/box.h"
#include "base/shapes/sphere.h"
#include "base/shapes/cylinder.h"

#include "bullet/shapes/btphysbone.h"
#include "bullet/shapes/btcylinder.h"
#include "bullet/shapes/btsphere.h"
#include "bullet/shapes/btbox.h"

#include <QDebug>

namespace GeneCraftCore {

btoShapesFactory::btoShapesFactory(BulletOgreEngine *btoEngine) : btShapesFactory()
{
    this->btoEngine = btoEngine;
}

Node<Box*> *btoShapesFactory::createBox(btVector3 size, const btTransform &transform, const btScalar density, QVariant)
{
    return new oBox((btoWorld*)world, size, transform, density);
}

Node<Sphere*> *btoShapesFactory::createSphere(btScalar radius, const btTransform &transform, const btScalar density, QVariant params) {
    btSphere* btImpl   = new btSphere(world, radius, transform, density);
    oSphere* oImpl     = new oSphere((btoWorld*)world, radius, transform, density, params);
    Sphere* compoundImpl = new Sphere(world, radius, transform, density);
    compoundImpl->addComposite(btImpl);
    compoundImpl->addComposite(oImpl);
    compoundImpl->setDelegate(btImpl);
    return compoundImpl;
}

Node<Cylinder*> *btoShapesFactory::createCylinder(btScalar radius, btScalar height, const btTransform &transform, const btScalar density, QVariant)
{
    btCylinder* btImpl       = new btCylinder(world, radius, height, transform, density);
    oCylinder*  oImpl        = new oCylinder((btoWorld*)world, radius, height, transform, density);
    Cylinder*   compoundImpl = new Cylinder(world, radius, height, transform, density);
    compoundImpl->addComposite(btImpl);
    compoundImpl->addComposite(oImpl);
    compoundImpl->setDelegate(btImpl);
    return compoundImpl;
}

Node<PhysBone*> *btoShapesFactory::createBone(btScalar length, btScalar radius, btScalar radiusArticulation, const btTransform &transform, QVariant p) {
    btPhysBone* btImpl       = new btPhysBone(world, length, radius, radiusArticulation, transform);
    oPhysBone*  oImpl        = new oPhysBone((btoWorld*)world, length, radius, radiusArticulation, transform);
    PhysBone*   compoundImpl = new PhysBone(world, length, radius, radiusArticulation, transform);

    compoundImpl->addComposite(btImpl);
    compoundImpl->addComposite(oImpl);
    compoundImpl->setDelegate(btImpl);
    return compoundImpl;
}

}
