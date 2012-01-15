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

#ifndef BTCYLINDER_H
#define BTCYLINDER_H

#include "genecraftcoreclasses.h"
#include "btshape.h"
#include "BulletCollision/CollisionShapes/btCylinderShape.h"
#include "LinearMath/btDefaultMotionState.h"

namespace GeneCraftCore {

/**
 * @brief A basic physical cylinder
 *
 */
class btCylinder : public btShape
{
public:
/**
 * @brief Construct a cylinder in a given world
 *
 * @param world the world where the cylinder will be
 * @param radius the radius of the cylinder
 * @param height the height of the cylinder
 * @param transform the initial position of the cylinder (bullet physics)
 * @param density the density of the cylinder
 */
    btCylinder(btWorld *world, btScalar radius, btScalar height, const btTransform &transform, const btScalar density);
    /**
     * @brief destruct and remove the cylinder from the world
     *
     */
    virtual ~btCylinder();
    /**
     * @brief setup the cylinder in the world
     *
     */
    virtual void setup();
    /**
     * @brief change the size (both radius and height) of the cylinder
     *
     * @param radius the new radius of the cylinder
     * @param height the new height of the cylinder
     */
    virtual void setSize(btScalar radius, btScalar height);

private:

    /**
     * @brief
     *
     * @param radius
     * @param height
     * @param density
     * @param transform
     */
    void init(btScalar radius, btScalar height, btScalar density, const btTransform &transform);

protected:

    btScalar radius; /**< TODO */
    btScalar height; /**< TODO */
    btCylinderShape* shape; /**< TODO */
    btDefaultMotionState* motionState; /**< TODO */
};

}

#endif // BTCYLINDER_H
