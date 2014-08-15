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

#ifndef SPIDERFAMILY_H
#define SPIDERFAMILY_H

#include "genecraftcoreclasses.h"
#include "LinearMath/btTransform.h"
#include "entityfamily.h"

namespace GeneCraftCore {

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * Spider Family
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class SpiderFamily : public EntityFamily
{


public:

    // To create a random spider family
    SpiderFamily();

    // To create an entity of this family
    virtual Entity* createEntity(btShapesFactory *shapesFactory,
                                 const btVector3 &position);
    // To serialize the family
    virtual QVariant serialize();

protected:

    btShapesFactory *shapesFactory;

    // characteristics of the family
    int nbLegs;
    int nbBoneInLeg;
    btScalar legRadius;
    btScalar legLenght;
    btScalar kneeRadius;
    btScalar headRadius;

private:

    // use to create the spider
    void addLeg(Fixation *fixBody, btScalar yAxis, btScalar zAxis, const btVector3 &lowerLimits, const btVector3 &upperLimits);
};

}

#endif // SPIDERFAMILY_H
