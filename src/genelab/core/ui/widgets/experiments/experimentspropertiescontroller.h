#ifndef EXPERIMENTSPROPERTIESCONTROLLER_H
#define EXPERIMENTSPROPERTIESCONTROLLER_H

#include <QWidget>
#include <QVariantMap>
#include "genelabcoreclasses.h"

namespace Ui {
    class ExperimentsPropertiesController;
}

class ExperimentsPropertiesController : public QWidget
{
    Q_OBJECT

public:

    ExperimentsPropertiesController(GeneLabCore::Experiment *experiment, QWidget *parent = 0);
    ~ExperimentsPropertiesController();

    QVariantMap getWorldMap();

signals:
    void experimentLoaded(GeneLabCore::Experiment *experiment);

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

private:

    Ui::ExperimentsPropertiesController *ui;

    GeneLabCore::Experiment *experiment;

    FloatMutationController *boneLengthMutation;
    FloatMutationController *boneRadiusMutation;
    FloatMutationController *fixationRadiusMutation;
    FloatMutationController *boneAngularOrigin;
    StructuralMutationController *bonesStructuralMutation;
    StructuralMutationController *sensorsStructuralMutation;

    IntegerMutationController *brainSize;
    FloatMutationController *brainInPos;
    FloatMutationController *brainInWeight;
    IntegerMutationController *brainMemorySize;
    IntegerMutationController *brainFrequency;
    FloatMutationController *constValue;
    SimpleProbabilityController *newBrainTree;
};

#endif // EXPERIMENTSPROPERTIESCONTROLLER_H
