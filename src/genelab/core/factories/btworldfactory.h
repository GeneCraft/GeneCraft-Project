#ifndef WORLDFACTORY_H
#define WORLDFACTORY_H

#include <QObject>
#include "world/btworld.h"


namespace GeneLabCore {

    class btWorldFactory : public QObject
    {

    public:
        explicit btWorldFactory(QObject *parent = 0);

        QVariant createSimpleWorld();
        virtual btWorld* createWorld(btFactory* factory,
                                     btShapesFactory* shapesFactory,
                                     QVariant worldData);


    };

}

#endif // WORLDFACTORY_H
