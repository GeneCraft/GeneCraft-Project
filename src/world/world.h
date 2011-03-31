#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include "classes.h"

namespace GeneLabCore {
    class World : public QObject
    {
        Q_OBJECT
    public:
        explicit World(QObject *parent = 0);

        virtual void setPhysics (PhysicsScene*  scene) = 0;
        virtual void setGraphics(GraphicsScene* scene) = 0;
    signals:

    public slots:

    };
}

#endif // WORLD_H
