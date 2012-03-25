/*
Copyright 2012 Zéni David

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

#ifndef REALSPIDERFAMILY_H
#define REALSPIDERFAMILY_H

#include "genecraftcoreclasses.h"
#include "LinearMath/btTransform.h"
#include "entityfamily.h"

namespace GeneCraftCore {

class RealSpiderFamily : public EntityFamily
{
public:
    RealSpiderFamily();
    ~RealSpiderFamily();

    // To create an entity of this family
    virtual Entity* createEntity(btShapesFactory *shapesFactory,
                                 const btVector3 &position);
    // To serialize the family
    virtual QVariant serialize(Entity *entity);

protected:

    btShapesFactory *shapesFactory;

    // characteristics of the family
    btScalar sizeMultiplier;
    int nbLegs;
    int nbBoneInLeg;

    btScalar** legSegmentLength;
    btScalar** legSegmentRadius;

    btScalar legRadius;
    btScalar legLenght;
    btScalar kneeRadius;
    btScalar headRadius;
    btScalar** anglesY;
    btScalar* anglesZ;
    btVector3* lowerLimits;
    btVector3* upperLimits;

private:

    // use to create the spider
    void addLeg(int rightSide, int legId, Fixation *fixBody, btScalar yAxis);
};

}

#endif // REALSPIDERFAMILY_H
