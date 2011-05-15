#ifndef BRAINENGINE_H
#define BRAINENGINE_H

#include <QObject>

#include "classes.h"
#include "engine/engine.h"

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
        void addNetwork(int size);
        void addNetwork(NeuralNetwork* network);

        void beforeStep();
        void step();
        void afterStep();

    private:
        QList<NeuralNetwork*> networks;
        QList<GeneLabWidget::NeuralNetworkVisualizer*> visualizers;

    };
}

#endif // BRAINENGINE_H
