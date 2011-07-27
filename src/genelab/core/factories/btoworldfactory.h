#ifndef BTOWORLDFACTORY_H
#define BTOWORLDFACTORY_H

#include <QVariant>
#include "genecraftcoreclasses.h"

namespace GeneCraftCore {

    class btoWorldFactory
    {
    public:

        static btoWorld* createWorld(btoFactory* factory,
                                     btoShapesFactory* shapesFactory,
                                     QVariant worldData);
    };

}

#endif // BTOWORLDFACTORY_H
