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

#ifndef BTBOX_H
#define BTBOX_H

#include "genecraftcoreclasses.h"
#include "btshape.h"
#include "BulletCollision/CollisionShapes/btBoxShape.h"
#include "LinearMath/btDefaultMotionState.h"

namespace GeneCraftCore {

/**
 * @brief A simple physical box
 *
 */
class btBox : public btShape
{
public:
/**
 * @brief Create a simple physical box in the world
 *
 * @param world the world where the box will be
 * @param size the size of the edge of the box
 * @param transform the initial position (see bulletphysics transform)
 * @param density the density of the box
 */
    btBox(btWorld *world, btVector3 size, const btTransform &transform, const btScalar density);
    /**
     * @brief destruct the box and remove it from the world
     *
     */
    ~btBox();
    /**
     * @brief setup the box and add it in the world
     *
     */
    virtual void setup();

private:

    /**
     * @brief initialize the box
     *
     * @param size
     * @param transform
     * @param density
     */
    void init(btVector3 size, const btTransform &transform, const btScalar density);

protected:

    btBoxShape* shape; /**< the bullet physics box shape */
    btDefaultMotionState* motionState; /**< motion state (bullet) */
    RigidBodyOrigin *origin; /**< the link between this object and the bullet rigid origin */
};

}

#endif // BTBOX_H
