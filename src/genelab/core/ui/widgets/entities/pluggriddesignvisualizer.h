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
        void setBrain(Brain* b);

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
        btScalar* neurons;
        bool init;
        QList<QGraphicsRectItem*> neurones;
        QMap<int, QMap<int, QGraphicsEllipseItem* > > ellipses;

    };
}

#endif // PLUGGRIDDESIGNVISUALIYER_H
