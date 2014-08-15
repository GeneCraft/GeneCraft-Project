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
#include "bulletogre/shapes/btobox.h"
#include "bulletogre/shapes/btosphere.h"
#include "bulletogre/shapes/btocylinder.h"
#include "bulletogre/shapes/btobone.h"

#include <QDebug>

namespace GeneCraftCore {

btoShapesFactory::btoShapesFactory(BulletOgreEngine *btoEngine) : btShapesFactory()
{
    this->btoEngine = btoEngine;
}

btBox *btoShapesFactory::createBox(btVector3 size, const btTransform &transform, const btScalar density, QVariant)
{
    return new btoBox((btoWorld*)world, btoEngine, size, transform, density);
}

btSphere *btoShapesFactory::createSphere(btScalar radius, const btTransform &transform, const btScalar density, QVariant params)
{
    return new btoSphere((btoWorld*)world, btoEngine, radius, transform, density, params);
}

btCylinder *btoShapesFactory::createCylinder(btScalar radius, btScalar height, const btTransform &transform, const btScalar density, QVariant)
{
    return new btoCylinder((btoWorld*)world, btoEngine, radius, height, transform, density);
}

btBone* btoShapesFactory::createBone(btScalar length, btScalar radius, btScalar radiusArticulation, const btTransform &transform, QVariant) {
    return new btoBone((btoWorld*)world, btoEngine, length, radius, radiusArticulation, transform);
}

}
