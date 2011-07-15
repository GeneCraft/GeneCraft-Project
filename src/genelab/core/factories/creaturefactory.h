#ifndef CREATUREFACTORY_H
#define CREATUREFACTORY_H

#include "entity.h"
#include "LinearMath/btVector3.h"
#include <QObject>

namespace GeneLabCore {

    class CreatureFactory : public QObject
    {

    public:
        explicit CreatureFactory(QObject *parent = 0);
        Entity* createEntity(QVariant data,
                             btShapesFactory* shapesFactory,
                             btVector3 positionSensor);
        QString error;


    };

}

#endif // CREATUREFACTORY_H
