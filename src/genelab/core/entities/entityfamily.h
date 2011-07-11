#ifndef ENTITYFAMILY_H
#define ENTITYFAMILY_H

#include <QObject>
#include "genelabcoreclasses.h"
#include "LinearMath/btVector3.h"

namespace GeneLabCore {

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * A Family allows to create specific entities with particular shape.
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class EntityFamily : public QObject
{

public:
    explicit EntityFamily(QObject *parent = 0);

    virtual Entity* createEntity(btShapesFactory *shapesFactory, const btVector3 &position) = 0;

    virtual QVariant serialize() = 0;

};
}
#endif // ENTITYFAMILY_H
