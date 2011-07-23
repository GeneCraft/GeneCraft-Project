#ifndef EXPERIMENTSPROPERTIESCONTROLLER_H
#define EXPERIMENTSPROPERTIESCONTROLLER_H

#include <QWidget>
#include <QVariantMap>
#include "genelabcoreclasses.h"

namespace Ui {
    class ExperimentsPropertiesController;
}


namespace GeneLabCore {

class ExperimentsPropertiesController : public QWidget
{
    Q_OBJECT

public:

    ExperimentsPropertiesController(QWidget *parent = 0);
    ~ExperimentsPropertiesController();

    void connectToInspectorInputManager(GeneLabCore::InspectorsInputManager * iim);

    QVariantMap getWorldMap();
    QVariantMap getSeedMap();

signals:
    void sLoadExperiment(Experiment *experiment);

public slots:
    void setupForm();

    void save();
    void saveExpToFile();

    void updateStructures();
    void enterInWhatsThisMode();

    void loadExpFromFile();

    void loadWorldFromFile();
    void saveWorldToFile();

    void setWorld(QVariantMap worldData);
    void setExperiment(GeneLabCore::Experiment *exp);

    void removeEntityFromSeed();
    void addEntityToSeed();
    void viewGenome();
    void viewAvailableGenome();

    void gbFamilyToggled(bool);
    void gbFixedGenomes(bool);
    void refreshRessources();
    void addFromGenome();


private:

    Ui::ExperimentsPropertiesController *ui;

    GeneLabCore::Experiment *experiment;

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

    GeneLabCore::RessourcesManager *localRessourceManager;
};

}

#endif // EXPERIMENTSPROPERTIESCONTROLLER_H
