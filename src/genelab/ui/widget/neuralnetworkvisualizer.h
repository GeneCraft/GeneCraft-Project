#ifndef NEURALNETWORKVISUALIZER_H
#define NEURALNETWORKVISUALIZER_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPaintEvent>
#include "classes.h"

namespace GeneLabCore {

    class NeuralNetworkVisualizer : public QWidget
    {
        Q_OBJECT
    public:
        explicit NeuralNetworkVisualizer(GeneLabCore::BrainEngine* network, QWidget *parent = 0);

    signals:

    public slots:
        void step();
        void paintEvent(QPaintEvent* e);

    private:
        GeneLabCore::BrainEngine* networks;
        QGraphicsView* view;
        float* neurons;
        bool init;
    };

}

#endif // NEURALNETWORKVISUALIZER_H
