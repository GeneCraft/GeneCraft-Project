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

#ifndef GENERICFAMILY_H
#define GENERICFAMILY_H

#include <QJsonObject>
#include "genecraftcoreclasses.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btTransform.h"

namespace GeneCraftCore {

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * This family is a family that contains entities with a generic shape (non-predefined shape).
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class GenericFamily
{
public:

    GenericFamily();

    // To create an entity with its genome
    static Entity *createEntity(QJsonObject genotype,
                                btShapesFactory *shapesFactory,
                                const btVector3 &initialPosition);

    // To create a virgin entity
    static Entity *createVirginEntity(btShapesFactory *shapesFactory,
                                     btScalar rootFixRadius,
                                     const btVector3 &initialPosition);


    static Fixation* createRootFromGenotype(btShapesFactory *shapesFactory, QJsonObject genotype, btTransform initTransform);
    static void buildFixFromGenotype(btShapesFactory *shapesFactory, Fixation *fix, Fixation* root, QJsonObject fixGenotype);


};
}
#endif // GENERICFAMILY_H
