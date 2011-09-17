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
};

}

#endif // EXPERIMENTSPROPERTIESCONTROLLER_H
