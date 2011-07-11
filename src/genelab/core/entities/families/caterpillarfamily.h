#ifndef CATERPILLARFAMILY_H
#define CATERPILLARFAMILY_H

#include "genelabcoreclasses.h"
#include "entityfamily.h"
#include "entity.h"

namespace GeneLabCore {

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * Snake Family
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class CaterpillarFamily : public EntityFamily
{


public:

    // To create a random snake family
    explicit CaterpillarFamily(QObject *parent = 0);

    // To create the family from serialization data
    CaterpillarFamily(QVariant data, QObject *parent = 0);

    // To create an entity of this family
    Entity* createEntity(btShapesFactory* factory, const btVector3 &position);

    // To serialize family
    QVariant serialize();
    void load(QVariant data);

private:
    int length;
    btScalar pieceLength;
    btScalar pieceRadius;
    btScalar fixRadius;
    btScalar legLength;
    btScalar legRadius;
    btScalar antennaPieces;
    btScalar antennaLength;
    btScalar antennaRadius;
};
}

#endif // CATERPILLARFAMILY_H
