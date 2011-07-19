#ifndef CREATUREFACTORY_H
#define CREATUREFACTORY_H

#include "entity.h"
#include "LinearMath/btVector3.h"

namespace GeneLabCore {

    class CreatureFactory
    {

    public:

        static Entity* createEntity(QVariant data,
                             btShapesFactory* shapesFactory,
                             btVector3 positionSensor);
    };
}

#endif // CREATUREFACTORY_H
