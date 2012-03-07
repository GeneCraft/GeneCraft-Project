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

#ifndef BTSPHERE_H
#define BTSPHERE_H

#include "genecraftcoreclasses.h"
#include "base/shapes/sphere.h"

class btSphereShape;
class btDefaultMotionState;

namespace GeneCraftCore {

/**
 * @brief a basic physical sphere, mainly used at the primary fixation of an
 entity
 *
 */
class btSphere : public Sphere
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
    btSphere(btWorld *btWorld, btScalar radius, const btTransform &transform, const btScalar density);

    /**
     * @brief destruct and remove the sphere from the world
     *
     */
    virtual ~btSphere();

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
     * @brief return the mass of the sphere
     *
     */
    btScalar getMass() const;

private:

    /**
     * @brief protected init function
     *
     * @param radius
     * @param density
     * @param transform
     */
    void init(btScalar radius, btScalar density, const btTransform &transform);
    /**
     * @brief compute the mass of the sphere
     *
     */
    btScalar computeMass() const;

protected:
    btRigidBody* rigidBody;
    btSphereShape* shape; /**< physical spherical bullet shape */
    btDefaultMotionState* motionState; /**< motion state (bullet) */
    RigidBodyOrigin* origin; /**< the link between the object to the rigid body */
};

}

#endif // BTSPHERE_H
