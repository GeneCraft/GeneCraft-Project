#ifndef BRAINENGINE_H
#define BRAINENGINE_H

#include <QObject>

#include "classes.h"
#include "engine.h"

namespace GeneLabCore {

    class BrainEngine : public Engine
    {
        Q_OBJECT
    public:
        explicit BrainEngine(QObject *parent = 0);

        bool isRenderable() {
            return true;
        }

        QWidget* getRenderWidget(QWidget* parent);
        QList<NeuralNetwork*> getNetworks();

    signals:

    public slots:
        NeuralNetwork* addNetwork(int size);
        void addNetwork(NeuralNetwork* network);

        void beforeStep();
        void step();
        void afterStep();

    private:
        QList<NeuralNetwork*> networks;
        QList<NeuralNetworkVisualizer*> visualizers;

    };
}

#endif // BRAINENGINE_H
