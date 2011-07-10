#ifndef GENERICFAMILY_H
#define GENERICFAMILY_H

#include <QVariant>
#include "genelabcoreclasses.h"
#include "LinearMath/btVector3.h"

namespace GeneLabCore {

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
    static Entity *createEntity(QVariant genotype,
                                btShapesFactory *shapesFactory,
                                const btVector3 &initialPosition);

    // To create a virgin entity
    static Entity *createVirginEntity(btShapesFactory *shapesFactory,
                                     btScalar rootFixRadius,
                                     const btVector3 &initialPosition);
};
}
#endif // GENERICFAMILY_H
