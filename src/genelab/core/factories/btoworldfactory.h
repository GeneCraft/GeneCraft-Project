#ifndef BTOWORLDFACTORY_H
#define BTOWORLDFACTORY_H

#include "btworldfactory.h"
#include "genelabcoreclasses.h"

namespace GeneLabCore {

    class btoWorldFactory : public btWorldFactory
    {
    public:
        btoWorldFactory();
        virtual btoWorld* createWorld(btoFactory* factory,
                                     btoShapesFactory* shapesFactory,
                                     QVariant worldData);
    };

}

#endif // BTOWORLDFACTORY_H
