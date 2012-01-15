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

#ifndef RIGIDBODYORIGIN_H
#define RIGIDBODYORIGIN_H

#include <QObject>

namespace GeneCraftCore {

/**
 * @brief Create a link between a rigidbody and a QObject*
 is used to get the qt object back from a collision callback for example
 *
 */
class RigidBodyOrigin : public QObject
{

public:

    /**
     * @brief the type of the shape, to be able to cast the QObject to a more
     usefull type, new kind of shape should be added here accordingly
     *
     */
    enum RigidBodyType
    {
        BONE = 0, // A physical bone
        FIXATION, // A physical fixation (sphere)
        BASIC_SHAPE // Another type of shape
    };

/**
 * @brief create an information about the rigidbodyorigin
 *
 * @param typeOrigin the initial type
 * @param object the pointer to the linked object
 */
    RigidBodyOrigin(RigidBodyType typeOrigin, QObject * object);


    /**
     * @brief return to object type
     *
     * @return RigidBodyType
     */
    inline RigidBodyType getType()
    {
        return typeOrigin;
    }

    /**
     * @brief return the object pointer
     *
     * @return QObject *
     */
    QObject * getObject()
    {
        return object;
    }

protected:

    RigidBodyType typeOrigin; /**< the type of the object */
    QObject *object; /**< the pointer to the object */

};

}

#endif // RIGIDBODYORIGIN_H
