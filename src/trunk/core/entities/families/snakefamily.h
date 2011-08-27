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
