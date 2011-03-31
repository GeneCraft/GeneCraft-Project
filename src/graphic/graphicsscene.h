#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QObject>
#include "classes.h"

namespace GeneLabCore {

    class GraphicsScene : public QObject
    {
        Q_OBJECT
    public:
        explicit GraphicsScene(QObject *parent = 0);

        // Add and remove of world, entity
        virtual void addWorld(GeneLabCore::World* world) = 0;
        virtual void addEntity(GeneLabCore::Entity* entity) = 0;
        virtual void removeWorld(GeneLabCore::World* world) = 0;
        virtual void removeEntity(GeneLabCore::Entity* entity) = 0;

    signals:

    public slots:

    };
}

#endif // GRAPHICSSCENE_H
