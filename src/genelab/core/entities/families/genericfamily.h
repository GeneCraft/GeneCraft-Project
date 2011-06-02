#ifndef GENERICFAMILY_H
#define GENERICFAMILY_H

#include <QVariant>
#include "genelabcoreclasses.h"
#include "LinearMath/btVector3.h"

namespace GeneLabCore {
class GenericFamily
{
public:

    GenericFamily();

    static Entity *createEntity(QVariant genotype,
                                btShapesFactory *shapesFactory,
                                const btVector3 &initialPosition);

    static Entity *createViginEntity(btShapesFactory *shapesFactory,
                                     btScalar rootFixRadius,
                                     const btVector3 &initialPosition);
};
}
#endif // GENERICFAMILY_H
