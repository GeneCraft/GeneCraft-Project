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

#ifndef FIXATIONPROPERTIESCONTROLLER_H
#define FIXATIONPROPERTIESCONTROLLER_H

#include <QWidget>
#include <QListWidgetItem>

#include "genecraftcoreclasses.h"
#include "sensors/sensor.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

using namespace GeneCraftCore;

namespace Ui {
    class FixationPropertiesController;
}

class FixationPropertiesController : public QWidget
{
    Q_OBJECT

public:
    explicit FixationPropertiesController(QWidget *parent = 0);
    ~FixationPropertiesController();
    void connectToInspectorInputManager(InspectorsInputManager *iim);

signals:

    void rigidBodySelected(btRigidBody *);
    void sBoneDeleted(Bone* bone);
    void sBoneSelected(Bone *);
    void sFixationUpdated(Fixation *fixation);

public slots:

    void setFixation(Fixation *fixation);

    void addBone();
    void addSensor();
    void addEffector();

    void selectBone();

    void removeSelectedBone();
    void removeSelectedSensor();
    void removeSelectedEffector();

    void fixInTheAir();
    void changeRadiusFromSlider(int value);
    void changeRadiusFromButton();

    // Notifications
    void boneSelected(Bone *);
    void fixationDeleted(Fixation * fixation);
    void entityDeleted(Entity *entity);

private:
    Ui::FixationPropertiesController *ui;

    Fixation *fixation;
};

#endif // FIXATIONPROPERTIESCONTROLLER_H
