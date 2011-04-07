#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include "classes.h"
#include <QTimer>
#include <QDebug>

namespace GeneLabCore {

    class SimulationManager : public QObject
    {
        Q_OBJECT
    public:

        SimulationManager(QObject *parent = 0): QObject(parent) {}


    signals:

    public slots:
        virtual void setup() = 0;

        // added by ADC
        // the world manager the time
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void update() = 0;

    private:
    };

}

#endif // SIMULATIONMANAGER_H
