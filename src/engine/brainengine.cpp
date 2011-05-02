#include "brainengine.h"
#include "widget/neuralnetworkvisualizer.h"
#include "entity/neural/neuralnetwork.h"

#include <QLabel>

namespace GeneLabCore {

    BrainEngine::BrainEngine(QObject *parent) :
        Engine(parent)
    {
    }


    QWidget* BrainEngine::getRenderWidget(QWidget* parent) {
        GeneLabWidget::NeuralNetworkVisualizer* w = new GeneLabWidget::NeuralNetworkVisualizer(this);
        this->visualizers.append(w);
        return w;
    }

    void BrainEngine::beforeStep() {
        // Maybe nothing to do
        foreach(NeuralNetwork* n, this->networks) {
            n->beforeStep();
        }
    }

    void BrainEngine::step() {
        // Get In and calculate weights / etc...
        foreach(NeuralNetwork* n, this->networks) {
            n->neuralStep();
        }


        foreach(GeneLabWidget::NeuralNetworkVisualizer* viz, this->visualizers) {
            viz->step();
        }
    }

    void BrainEngine::afterStep() {
        // Set out, but we'll see if we don't do this in step...
        foreach(NeuralNetwork* n, this->networks) {
            n->afterStep();
        }
    }

    void BrainEngine::addNetwork(int size) {
        this->networks.append(new NeuralNetwork(size));
    }

    void BrainEngine::addNetwork(NeuralNetwork* network) {
        this->networks.append(network);
    }

    QList<NeuralNetwork*> BrainEngine::getNetworks() {
        return this->networks;
    }

}

