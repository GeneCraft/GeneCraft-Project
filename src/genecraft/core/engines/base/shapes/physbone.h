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

#ifndef PHYSBONE_H
#define PHYSBONE_H

#include "genecraftcoreclasses.h"
#include "base/node.h"
#include <QList>

namespace GeneCraftCore {
/**
 * @brief The physical bone representing a bone in an abstract and composite way
 *
 */
class PhysBone : public Node<PhysBone*>
{
public:
    /**
     * @brief Construct a bone in a given world, and set informations about the
     way it's attached to the parent fixation
     *
     * @param world a world where the bone will be located
     * @param length the length of the bone
     * @param radius the radius of the bone
     * @param radiusArticulation the radius of the sphere at the end of the bone
     * @param transform the way the bone is attached to the parent
     */
    PhysBone(btWorld *world, btScalar length, btScalar radius, btScalar radiusArticulation, const btTransform &transform);

        /**
     * @brief simple bone destructor
     *
     */
    virtual ~PhysBone();

    /**
     * @brief setup the bone into the world, attach the bone to the parent and
     if necessary create the motor effector for it's joint.
     *
     */
    virtual void setup();

    /**
     * @brief return the length of the bone
     *
     * @return btScalar the length of the bone
     */
    btScalar getLength();

    /**
     * @brief return the radius of the bone
     *
     * @return btScalar the radius of the bone
     */
    btScalar getRadius();

    /**
     * @brief return the radius of the sphere at the end of the bone
     *
     * @return btScalar the radius of the fixation
     */
    btScalar getArticulationRadius();

    /**
     * @brief change the bone size (both length and radius)
     *
     * @param radius the new radius of the bone
     * @param length the new length of the bone
     */
    virtual void setSize(btScalar radius, btScalar length);

    /**
     * @brief change the ending sphere radius
     *
     * @param radius the new radius of the fixation
     */
    virtual void setEndFixationRadius(btScalar radius);

    virtual btScalar getMass() const;

    //!TODO: Improve
    static const btScalar DENSITY; /**< the density of all bone */


protected:
    btScalar length;
    btScalar radius;
    btScalar radiusArticulation;
};
}



#endif // PHYSBONE_H
