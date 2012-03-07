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

#ifndef SPHERE_H
#define SPHERE_H

#include "genecraftcoreclasses.h"
#include "base/node.h"

#include <QList>

namespace GeneCraftCore {

/**
 * @brief a basic physical sphere, mainly used at the primary fixation of an
 entity
 *
 */
class Sphere : public Node<Sphere*>
{
public:
    /**
     * @brief construct a sphere in a given world
     *
     * @param btWorld the world where the sphere will be
     * @param radius the radius of the sphere
     * @param transform the initial transformation of the sphere
     * @param density the density of the sphere
     */
    Sphere(btWorld *btWorld, btScalar radius, const btTransform &transform, const btScalar density);

    /**
     * @brief destruct and remove the sphere from the world
     *
     */
    virtual ~Sphere();

    /**
     * @brief setup the sphere in the world
     *
     */
    virtual void setup();

    /**
     * @brief change the size of the sphere
     *
     * @param radius the new radius of the sphere
     */

    virtual void setRadius(btScalar radius);


    /**
     * @brief return the size of the sphere
     *
     * @return radius the radius of the sphere
     */

    virtual btScalar getRadius();

    virtual void setFriction(btScalar);
    virtual btScalar getFriction();


private:


protected:
    btScalar radius;
    btScalar density; /**< the density of the sphere */
    btScalar friction;

};

}

#endif // SPHERE_H
