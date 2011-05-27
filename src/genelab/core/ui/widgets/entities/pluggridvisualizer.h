#ifndef NEURALNETWORKVISUALIZER_H
#define NEURALNETWORKVISUALIZER_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPaintEvent>
#include "genelabcoreclasses.h"

namespace GeneLabCore {

    class PlugGridVisualizer : public QWidget
    {
        Q_OBJECT
    public:
        explicit PlugGridVisualizer(GeneLabCore::BrainEngine* network, QWidget *parent = 0);

    signals:

    public slots:
        void step();
        void paintEvent(QPaintEvent* e);

    private:
        GeneLabCore::BrainEngine* brainEngine;
        QGraphicsView* view;
        float* neurons;
        bool init;
    };

}

#endif // NEURALNETWORKVISUALIZER_H
