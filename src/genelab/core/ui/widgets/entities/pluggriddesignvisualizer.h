#ifndef PLUGGRIDDESIGNVISUALIYER_H
#define PLUGGRIDDESIGNVISUALIYER_H

#include <QWidget>
#include <QGraphicsView>
#include "genelabcoreclasses.h"
#include <QDebug>

namespace GeneLabCore {
    class PlugGridDesignVisualizer : public QWidget
    {

        Q_OBJECT
    public:
        explicit PlugGridDesignVisualizer(QWidget *parent = 0);
        void setBrain(Brain* b) {
            this->brain = b;
        }

        void setSelectedSensors(QList<Sensor*> s) {
            selectedSensors = s;
            this->update();
        }

    signals:

    public slots:
        void step();
        void paintEvent(QPaintEvent* e);

    private:
        QList<Sensor*> selectedSensors;
        Brain* brain;
        QGraphicsView* view;
        float* neurons;
        bool init;

    };
}

#endif // PLUGGRIDDESIGNVISUALIYER_H