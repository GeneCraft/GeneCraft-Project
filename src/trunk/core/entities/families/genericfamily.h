#ifndef GENERICFAMILY_H
#define GENERICFAMILY_H

#include <QVariant>
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
    static Entity *createEntity(QVariant genotype,
                                btShapesFactory *shapesFactory,
                                const btVector3 &initialPosition);

    // To create a virgin entity
    static Entity *createVirginEntity(btShapesFactory *shapesFactory,
                                     btScalar rootFixRadius,
                                     const btVector3 &initialPosition);


    static Fixation* createRootFromGenotype(btShapesFactory *shapesFactory, QVariant genotype, btTransform initTransform);
    static void buildFixFromGenotype(btShapesFactory *shapesFactory, Fixation *fix, Fixation* root, QVariant fixGenotype);


};
}
#endif // GENERICFAMILY_H
