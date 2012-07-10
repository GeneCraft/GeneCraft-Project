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

#ifndef EXPERIMENTSPROPERTIESCONTROLLER_H
#define EXPERIMENTSPROPERTIESCONTROLLER_H

#include <QWidget>
#include <QVariantMap>
#include "genecraftcoreclasses.h"

namespace Ui {
    class ExperimentsPropertiesController;
}


namespace GeneCraftCore {

class ExperimentsPropertiesController : public QWidget
{
    Q_OBJECT

public:

    ExperimentsPropertiesController(QWidget *parent = 0);
    ~ExperimentsPropertiesController();

    void connectToInspectorInputManager(GeneCraftCore::InspectorsInputManager * iim);

    QVariantMap getWorldMap();
    QVariantMap getSeedMap();

signals:
    void sLoadExperiment(Experiment *experiment);
    void sExperimentUpdated(Experiment*);

public slots:
    void setupForm();

    void save();
    void saveAndReload();
    void saveExpToFile();

    void updateStructures();
    void enterInWhatsThisMode();

    void loadExpFromFile();

    void loadWorldFromFile();
    void saveWorldToFile();

    void setWorld(QVariantMap worldData);
    void setExperiment(GeneCraftCore::Experiment *exp);

    void removeEntityFromSeed();
    void addEntityToSeed();
    void viewGenome();
    void viewAvailableGenome();

    void gbFamilyToggled(bool);
    void gbFixedGenomes(bool);
    void refreshRessources();
    void addFromGenome();

    void takeFromCamera();


private:

    Ui::ExperimentsPropertiesController *ui;

    GeneCraftCore::Experiment *experiment;

    // bone
    FloatMutationController *boneLengthMutation;
    FloatMutationController *boneRadiusMutation;
    FloatMutationController *boneAngularOrigin;
    FloatMutationController *boneAngularLimitsMutation;
    StructuralMutationController *bonesStructuralMutation;
    FloatMutationController* legLengthMutation;
    FloatMutationController* legRadiusMutation;
    FloatMutationController* bodyRadiusMutation;
    FloatMutationController* kneeRadiusMutation;

    // fixation
    FloatMutationController *fixationRadiusMutation;

    // sensors & effectors
    StructuralMutationController *sensorsStructuralMutation;
    StructuralMutationController *effectorsStructuralMutation;

    // brain
    FloatMutationController *brainDistance;
    FloatMutationController *brainInPos;
    FloatMutationController *brainInWeight;
    IntegerMutationController *brainMemorySize;
    IntegerMutationController *brainFrequency;
    FloatMutationController *constValue;
    StructuralMutationController *brainStructuralMutation;

    GeneCraftCore::RessourcesManager *localRessourceManager;


private slots:
    void on_btnFloor_clicked();
    void on_cbFamily_currentIndexChanged(const QString &family);
};

}

#endif // EXPERIMENTSPROPERTIESCONTROLLER_H
