/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PLUGGRIDDESIGNVISUALIYER_H
#define PLUGGRIDDESIGNVISUALIYER_H

#include <QWidget>
#include <QGraphicsView>
#include "genecraftcoreclasses.h"
#include <QDebug>

namespace GeneCraftCore {
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
