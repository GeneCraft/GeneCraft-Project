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

#ifndef BTSHAPE_H
#define BTSHAPE_H

#include "genecraftcoreclasses.h"
#include "base/node.h"

class btRigidBody;

namespace GeneCraftCore {

/**
 * @brief A basic physical shape an abstract class meant to be implemented in
 various shape type.
 *
 */
class btShape : public Node
{
public:
    /**
     * @brief construct the shape in a given world
     *
     * @param world
     */
    explicit btShape(btWorld* world);

    /**
     * @brief destruct and remove the shape from the world
     *
     */
    ~btShape();

    /**
     * @brief return the bulletphysic rigid body relatif to the shape
     *
     * @return btRigidBody *
     */
    btRigidBody * getRigidBody() { return rigidBody; }

protected:

    btWorld *world; /**< the world where the shape live */
    btRigidBody *rigidBody; /**< the rigidbody of the shape */

};

}

#endif // BTSHAPE_H
