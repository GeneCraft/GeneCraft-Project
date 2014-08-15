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

#ifndef BRAINPROPERTIESCONTROLLER_H
#define BRAINPROPERTIESCONTROLLER_H

#include <QWidget>

#include "bodyitems.h"
#include "genecraftcoreclasses.h"

using namespace GeneCraftCore;

namespace Ui {
    class BrainPropertiesController;
}

class BrainPropertiesController : public QWidget
{
    Q_OBJECT

public:
    explicit BrainPropertiesController(QWidget *parent = 0);
    ~BrainPropertiesController();
    void connectToInspectorInputManager(InspectorsInputManager *iim);


public slots:

    void selectSensorFixation();
    void setBrainFrequency();
    void clearSensors();
    void clearEffectors();
    void computeMinimalOuts();

    void setEntity(Entity *entity);
    void entityUpdated(Entity *entity);
    void entityDeleted(Entity *entity);

    void refresh();
    void sensorsSelected(QList<Sensor*>);

    void setBrainViz(PlugGridVisualizer* brainViz);
    void setBrainDesignViz(PlugGridDesignVisualizer* brainViz);

signals:

    void sEntityUpdated(Entity *entity);
    void sFixationSelected(Fixation *fixation);
    void sFixationUpdated(Fixation *fixation);
    void sBoneSelected(Bone *bone);

private:
    Ui::BrainPropertiesController *ui;
    Entity *entity;

    PlugGridVisualizer* brainViz;
    PlugGridDesignVisualizer* brainDezViz;
};

#endif // BRAINPROPERTIESCONTROLLER_H
