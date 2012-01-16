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

#ifndef CREATUREPROPERTIESCONTROLLER_H
#define CREATUREPROPERTIESCONTROLLER_H

#include <QWidget>
#include "bodyitems.h"
#include "genecraftcoreclasses.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include <QTimer>

namespace Ui {
    class EntityPropertiesController;
}

using namespace GeneCraftCore;

class EntityPropertiesController : public QWidget
{
    Q_OBJECT

public:

    explicit EntityPropertiesController(QWidget *parent = 0);
    ~EntityPropertiesController();
    void connectToInspectorInputManager(InspectorsInputManager *iim);

    // GETTERS / SETTERS
    void setBrainViz(PlugGridVisualizer* brainViz);
    void setBrainDesignViz(PlugGridDesignVisualizer* brainViz);

signals:

    void sSensorsSelected(QList<Sensor*> s);
    void sFixationSelected(Fixation*);
    void sBoneSelected(Bone *);

public slots:

    void saveOrigins();
    void setEntity(Entity *entity, Bone *selectedBone = NULL);
    void setOutFromNormalPosition();
    void setOutFromNone();
    void setOutFromBrain();
    void setOutFromRandom();
    void setOutFrom(int outsFrom);
    void viewGenotype();

    void fixationSelected(Fixation *fixation);
    void boneSelected(Bone *bone);
    void shapeUpdated();
    void entityUpdated(Entity *entity);
    void entityDeleted(Entity *entity);

    void resetBonesProperties();
    void itemClicked(QTreeWidgetItem *,int);

private:

    Ui::EntityPropertiesController *ui;

    void setupBodyTree(Fixation * fixation, Bone *selectedBone, QTreeWidgetItem *rootItem = 0);

    Entity *entity;
};

#endif // CREATUREPROPERTIESCONTROLLER_H
