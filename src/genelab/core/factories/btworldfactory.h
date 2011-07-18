#ifndef WORLDFACTORY_H
#define WORLDFACTORY_H

#include "world/btworld.h"

namespace GeneLabCore {

    class btWorldFactory
    {

    public:

        static QVariant createSimpleWorld();
        static btWorld* createWorld(btFactory* factory,
                                     btShapesFactory* shapesFactory,
                                     QVariant worldData);


    };

}

#endif // WORLDFACTORY_H
