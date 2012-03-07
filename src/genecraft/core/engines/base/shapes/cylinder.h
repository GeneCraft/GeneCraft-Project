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

#ifndef CYLINDER_H
#define CYLINDER_H

#include "genecraftcoreclasses.h"
#include "base/node.h"
#include <QList>

namespace GeneCraftCore {

/**
 * @brief A basic physical cylinder
 *
 */
class Cylinder : public Node<Cylinder*>
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
    Cylinder(btWorld *world, btScalar radius, btScalar height, const btTransform &transform, const btScalar density);

    /**
     * @brief destruct and remove the cylinder from the world
     *
     */
    virtual ~Cylinder();

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


    /**
     * @brief return the radius of the cylinder
     *
     * @return the radius of the cylinder
     */
    virtual btScalar getRadius();

    /**
     * @brief return the height of the cylinder
     *
     * @return height the height of the cylinder
     */
    virtual btScalar getHeight();

private:


protected:

    btScalar radius; /**< TODO */
    btScalar height; /**< TODO */
};

}

#endif // CYLINDER_H
