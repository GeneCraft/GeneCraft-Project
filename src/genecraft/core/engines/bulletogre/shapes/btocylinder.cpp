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

#include "btocylinder.h"

#include "bulletogre/btoworld.h"

#include "bulletogre/bulletogreengine.h"
#include "ogre/ogreengine.h"

#include "Ogre.h"

namespace GeneCraftCore {

using namespace Ogre;

int btoCylinder::mNumEntitiesInstanced = 0;

btoCylinder::btoCylinder(btoWorld *world, BulletOgreEngine *btoEngine, btScalar radius, btScalar height, const btTransform &transform, const btScalar density)
    : btCylinder(world, radius, height, transform, density)
{
    this->btoEngine = btoEngine;

    // New entity
    btoCylinder::mNumEntitiesInstanced++;

    // Create Ogre Entity
    entity = btoEngine->getOgreEngine()->getOgreSceneManager()->createEntity(
            "CylinderEntity_" + StringConverter::toString(btoCylinder::mNumEntitiesInstanced),
            "Barrel.mesh");

    // Material
    entity->setMaterialName("GeneCraft/RockWall");
    entity->setCastShadows(true);

    // Attach
    node = btoEngine->getOgreEngine()->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode();

    // Scale
    AxisAlignedBox boundingB = entity->getBoundingBox(); // we need the bounding box of the box to be able to set the size of the Bullet-box
    Vector3 sizeBB = boundingB.getSize();
    sizeBB /= 2.0f;     // only the half needed
    sizeBB *= 0.95f;    // Bullet margin is a bit bigger so we need a smaller size (Bullet 2.76 Physics SDK Manual page 18)
    Vector3 ogreSize(radius*2,height,radius*2);
    Vector3 scale = ogreSize  / boundingB.getSize();
    node->scale(scale);	// the cube is too big for us
    sizeBB *= scale;	// don't forget to scale down the Bullet-box too
}

void btoCylinder::setup()
{
    btCylinder::setup();

    node->attachObject(entity);
    btoEngine->addBody(rigidBody,entity,node);
}

void btoCylinder::setSize(btScalar radius, btScalar height)
{
    btoCylinder::setSize(radius,height);

    // Scale
    AxisAlignedBox boundingB = entity->getBoundingBox(); // we need the bounding box of the box to be able to set the size of the Bullet-box
    Vector3 sizeBB = boundingB.getSize();
    sizeBB /= 2.0f;     // only the half needed
    sizeBB *= 0.95f;    // Bullet margin is a bit bigger so we need a smaller size (Bullet 2.76 Physics SDK Manual page 18)
    Vector3 ogreSize(radius*2,height,radius*2);
    Vector3 scale = ogreSize  / boundingB.getSize();
    node->scale(scale);	// the cube is too big for us
}

}
