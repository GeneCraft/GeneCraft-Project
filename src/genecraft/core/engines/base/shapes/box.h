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

#ifndef BOX_H
#define BOX_H

#include "genecraftcoreclasses.h"
#include "base/node.h"

#include <QList>

namespace GeneCraftCore {

/**
 * @brief A simple physical box
 *
 */
class Box : public Node<Box*>
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
    Box(btWorld *world, btVector3 size, const btTransform &transform, const btScalar density);

    /**
     * @brief destruct the box and remove it from the world
     *
     */
    ~Box();

    /**
     * @brief setup the box and add it in the world
     *
     */
    virtual void setup();

    /**
      * @brief to resize a box
      */
    virtual void resize(btVector3 size);

    /**
      * @brief return the actual size
      */
    virtual btVector3 getSize();

protected:

    btVector3 size;
    btScalar density;
};

}

#endif // BOX_H
