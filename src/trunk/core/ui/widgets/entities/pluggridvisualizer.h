#ifndef NEURALNETWORKVISUALIZER_H
#define NEURALNETWORKVISUALIZER_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPaintEvent>
#include "genecraftcoreclasses.h"

namespace GeneCraftCore {

    class PlugGridVisualizer : public QWidget
    {
        Q_OBJECT
    public:
        explicit PlugGridVisualizer(QWidget *parent = 0);
        void setBrain(Brain* b) {
            this->brain = b;
        }

    signals:

    public slots:
        void step();
        void paintEvent(QPaintEvent* e);

    private:
        Brain* brain;
        QGraphicsView* view;
        btScalar* neurons;
        bool init;
    };

}

#endif // NEURALNETWORKVISUALIZER_H
