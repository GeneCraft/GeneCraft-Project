#ifndef PHYSICSSCENE_H
#define PHYSICSSCENE_H

#include <QObject>
#include "classes.h"


namespace GeneLabCore {
    class PhysicsScene : public QObject
    {
        Q_OBJECT
    public:
        explicit PhysicsScene(QObject *parent = 0);

    signals:

    public slots:

    };
}

#endif // PHYSICSSCENE_H
