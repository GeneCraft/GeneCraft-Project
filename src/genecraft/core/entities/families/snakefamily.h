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

#ifndef SNAKEBUILDER_H
#define SNAKEBUILDER_H

#include "genecraftcoreclasses.h"
#include "entityfamily.h"
#include "entity.h"

namespace GeneCraftCore {

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * Snake Family
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class SnakeFamily : public EntityFamily
{


public:

    // To create a random snake family
    explicit SnakeFamily(QObject *parent = 0);

    // To create the family from serialization data
    SnakeFamily(QVariant data, QObject *parent = 0);

    // To create an entity of this family
    Entity* createEntity(btShapesFactory* factory, const btVector3 &positionSensor);

    // To serialize family
    QVariant serialize();
    void load(QVariant data);

private:
    int length;
    btScalar pieceLength;
    btScalar pieceRadius;
    btScalar fixRadius;

};
}
#endif // SNAKEBUILDER_H
