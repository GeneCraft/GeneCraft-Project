#ifndef CREATUREFACTORY_H
#define CREATUREFACTORY_H

#include "entity.h"
#include "LinearMath/btVector3.h"
#include <QObject>

namespace GeneLabCore {

    class CreatureFactory : public QObject
    {
        Q_OBJECT
    public:
        explicit CreatureFactory(QObject *parent = 0);

    signals:
    public:
        Entity* createEntity(QVariant data,
                             btShapesFactory* shapesFactory,
                             btVector3 position);
        QString error;

    public slots:

    };

}

#endif // CREATUREFACTORY_H
