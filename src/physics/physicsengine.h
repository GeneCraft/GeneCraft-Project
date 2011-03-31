#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <QObject>
#include "classes.h"

namespace GeneLabCore {
    class PhysicsEngine : public QObject
    {
        Q_OBJECT
    public:
        explicit PhysicsEngine(QObject *parent = 0);
        virtual PhysicsScene* getPhysicsScene() = 0;
    signals:

    public slots:
        virtual void physicsStep() = 0;

    };
}

#endif // PHYSICSENGINE_H
