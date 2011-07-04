#ifndef ANTFAMILY_H
#define ANTFAMILY_H

#include "genelabcoreclasses.h"
#include "LinearMath/btTransform.h"
#include "entityfamily.h"

namespace GeneLabCore {

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * Ant Family
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class AntFamily : public EntityFamily
{
    Q_OBJECT

public:

    // To create a random ant family
    AntFamily();

    // To create an entity of this family
    virtual Entity* createEntity(btShapesFactory *shapesFactory,
                                 const btVector3 &position);

    // To serialize the family
    virtual QVariant serialize();

protected:

    btShapesFactory *shapesFactory;

    // characteristics of the family
    int nbBonesInLeg;
    btScalar legRadius;
    btScalar legLenght;
    btScalar kneeRadius;
    btScalar headRadius;
    btScalar trunkRadius;
    btScalar metasomaRadius;

private:

    // use to create the spider
    void addLeg(Fixation *fixBody, btScalar yAxis, btScalar zAxis, const btVector3 &lowerLimits, const btVector3 &upperLimits);
};
}

#endif // ANTFAMILY_H
