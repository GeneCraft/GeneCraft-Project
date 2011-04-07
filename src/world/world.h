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

    signals:

    public slots:
        virtual void setup() = 0;

        // added by ADC // Moved by cyp in simulationmanager
        // the world manager the time
        /*virtual void start() = 0;
        virtual void stop() = 0;
        virtual void update() = 0;*/
    };
}

#endif // WORLD_H
