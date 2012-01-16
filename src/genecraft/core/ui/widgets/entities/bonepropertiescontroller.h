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

#ifndef BONEPROPERTIESCONTROLLER_H
#define BONEPROPERTIESCONTROLLER_H

#include <QWidget>
#include "bodyitems.h"
#include "genecraftcoreclasses.h"
#include "sensors/sensor.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "widgets/graphicalwidget.h"

using namespace GeneCraftCore;

namespace Ui {
    class BonePropertiesController;
}

class BonePropertiesController : public GraphicalWidget
{
    Q_OBJECT

public:
    explicit BonePropertiesController(QWidget *parent = 0);
    ~BonePropertiesController();
    void connectToInspectorInputManager(InspectorsInputManager * iim);
    virtual void step();

signals:

    void rigidBodySelected(btRigidBody *);
    void sBoneDeleted(Bone *);

public slots:

    void setBone(Bone * bone);
    void boneDeleted(Bone *bone);
    void entityDeleted(Entity *entity);

private:
    Ui::BonePropertiesController *ui;

    Bone *bone;

private slots:

    void saveChanges();
    void deleteBone();
    void deleteBoneAndAttachChildrenToParent();
    void randomValues();
    void resetMotors();
    void setOutFrom();
    void changeSize();
    void changeLengthFromSlider(int value);
    void changeRadiusFromSlider(int value);
    void rigidBodySelectedFromFix(btRigidBody*);
    void validateAngularInputs();

    void cbEffectorX_stateChanged(int value);
    void cbEffectorY_stateChanged(int value);
    void cbEffectorZ_stateChanged(int value);
};

#endif // BONEPROPERTIESCONTROLLER_H
