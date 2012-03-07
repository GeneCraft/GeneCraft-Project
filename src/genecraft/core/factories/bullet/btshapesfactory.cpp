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

#include "btshapesfactory.h"

#include "bullet/shapes/btbox.h"
#include "bullet/shapes/btsphere.h"
#include "bullet/shapes/btcylinder.h"
#include "bullet/shapes/btPhysBone.h"

namespace GeneCraftCore {

btShapesFactory::btShapesFactory()
{
}

Node<Box*> *btShapesFactory::createBox(btVector3 size, const btTransform &transform, const btScalar density, QVariant)
{
    return new btBox(world, size, transform, density);
}

Node<Sphere*> *btShapesFactory::createSphere(btScalar radius, const btTransform &transform, const btScalar density, QVariant)
{
    return new btSphere(world, radius, transform, density);
}

Node<Cylinder*> *btShapesFactory::createCylinder(btScalar radius, btScalar height, const btTransform &transform, const btScalar density, QVariant)
{
    return new btCylinder(world, radius, height, transform, density);
}

Node<PhysBone*> *btShapesFactory::createBone(btScalar length, btScalar radius, btScalar radiusArticulation, const btTransform &transform, QVariant) {
    return new btPhysBone(world, length, radius, radiusArticulation, transform);
}

}
