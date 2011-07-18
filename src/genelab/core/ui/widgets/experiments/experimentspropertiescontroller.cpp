#include "experimentspropertiescontroller.h"
#include "ui_experimentspropertiescontroller.h"

#include <QWhatsThis>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>

#include "floatmutationcontroller.h"
#include "integermutationcontroller.h"
#include "simpleprobabilitycontroller.h"
#include "structuralmutationcontroller.h"

#include "experiment/experiment.h"
#include "mutation/mutationsmanager.h"
#include "ressources/jsonfile.h"

#include "world/btobiome.h"
#include "qxtjson.h"


using namespace GeneLabCore;

ExperimentsPropertiesController::ExperimentsPropertiesController(Experiment *experiment, QWidget *parent) :
    QWidget(parent), ui(new Ui::ExperimentsPropertiesController)
{
    ui->setupUi(this);

    setupForm();

    setExperiment(experiment);
}

void ExperimentsPropertiesController::setupForm() {

    // Buttons
    connect(ui->pbSave,SIGNAL(clicked()),this,SLOT(save()));
    connect(ui->pbClose,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->pbHelp,SIGNAL(clicked()),this,SLOT(enterInWhatsThisMode()));
    connect(ui->pbLoadExp,SIGNAL(clicked()),this,SLOT(loadExp()));
    connect(ui->pbSaveToFile,SIGNAL(clicked()),this,SLOT(saveToFile()));

}

void ExperimentsPropertiesController::setExperiment(Experiment *experiment){

    this->experiment = experiment;

    // -----------------
    // -- information --
    // -----------------
    ui->lDateOfCreation->setText(experiment->getDateOfCreation().toString("yyyy-MM-dd hh:mm:ss"));
    ui->leId->setText(experiment->getId());
    ui->leDescription->setText(experiment->getDescription());
    ui->leAuthor->setText(experiment->getAuthor());
    ui->leComments->setText(experiment->getComments());

    // ----------------
    // -- simulation --
    // ----------------
    ui->leDuration->setText(QString::number(experiment->getDuration()));
    ui->leTimeToWaitForStability->setText(QString::number(experiment->getTimeToWaitForStability()));
    ui->cbOnlyIfEntityIsStable->setChecked(experiment->getOnlyIfEntityIsStable());
    ui->cbStopIfEntityIsNotInOnePiece->setChecked(experiment->getStopIfEntityIsNotInOnePiece());

    // ---------------
    // -- mutations --
    // ---------------
    // clean mutations widgets
    while(ui->vlBodyMutations->count() != 0) {
        QWidget *w = ui->vlBodyMutations->itemAt(0)->widget();
        ui->vlBodyMutations->removeWidget(w);
        delete w;
    }
    while(ui->vlBrainMutations->count() != 0) {
        QWidget *w = ui->vlBrainMutations->itemAt(0)->widget();
        ui->vlBrainMutations->removeWidget(w);
        delete w;
    }

    // Create mutations widgets
    MutationsManager *mutationsManager = experiment->getMutationsManager();

    boneLengthMutation = new FloatMutationController(mutationsManager->boneLength,"Bones Length");
    boneRadiusMutation = new FloatMutationController(mutationsManager->boneRadius,"Bones Radius");
    fixationRadiusMutation = new FloatMutationController(mutationsManager->fixRadius,"Fixations Radius");
    boneAngularOrigin = new FloatMutationController(mutationsManager->boneAngularOrigin,"Bones angular origin");
    bonesStructuralMutation = new StructuralMutationController(mutationsManager->bonesStructural,"Bones Structural");
    sensorsStructuralMutation = new StructuralMutationController(mutationsManager->sensorsStructural,"Sensors Structural", mutationsManager->sensorStructuralList);

    brainSize = new IntegerMutationController(mutationsManager->brainSize,"Brain Size");
    brainInPos = new FloatMutationController(mutationsManager->brainInPos,"BrainIn Position");
    brainInWeight = new FloatMutationController(mutationsManager->brainWeight,"BrainIn Weight");
    brainMemorySize = new IntegerMutationController(mutationsManager->brainMemorySize,"Brain Mermory Size");
    brainFrequency = new IntegerMutationController(mutationsManager->brainFrequency,"Brain Frequency");
    constValue = new FloatMutationController(mutationsManager->constValue,"Constant Value");
    newBrainTree = new SimpleProbabilityController(mutationsManager->newBrainTree,"New Brain Tree");


    ui->vlBodyMutations->addWidget(boneLengthMutation);
    ui->vlBodyMutations->addWidget(boneRadiusMutation);
    ui->vlBodyMutations->addWidget(fixationRadiusMutation);
    ui->vlBodyMutations->addWidget(boneAngularOrigin);
    ui->vlBodyMutations->addWidget(bonesStructuralMutation);
    ui->vlBodyMutations->addWidget(sensorsStructuralMutation);

    ui->vlBrainMutations->addWidget(brainSize);
    ui->vlBrainMutations->addWidget(brainInPos);
    ui->vlBrainMutations->addWidget(brainInWeight);
    ui->vlBrainMutations->addWidget(brainMemorySize);
    ui->vlBrainMutations->addWidget(brainFrequency);
    ui->vlBrainMutations->addWidget(constValue);
    ui->vlBrainMutations->addWidget(newBrainTree);

    // -----------
    // -- world --
    // -----------

    // -- Biome --
    QVariantMap biomeMap = experiment->getWorldDataMap()["biome"].toMap();

    // lights
    ui->teLights->setText(QxtJSON::stringify(biomeMap["lights"]));

    // -- Scene --
    QVariantMap sceneMap = experiment->getWorldDataMap()["scene"].toMap();

    // camera
    QVariantMap camMap = sceneMap["camera"].toMap();
    ui->leCamPosX->setText(camMap["posX"].toString());
    ui->leCamPosY->setText(camMap["posY"].toString());
    ui->leCamPosZ->setText(camMap["posZ"].toString());
    ui->leCamTargetX->setText(camMap["targetX"].toString());
    ui->leCamTargetY->setText(camMap["targetY"].toString());
    ui->leCamTargetZ->setText(camMap["targetZ"].toString());

    // shapes
    ui->teStaticShapes->setText(QxtJSON::stringify(sceneMap["shapes"]));

    // spawns
    ui->teSpawns->setText(QxtJSON::stringify(sceneMap["spawns"]));
}

ExperimentsPropertiesController::~ExperimentsPropertiesController() {
    delete ui;
}

void ExperimentsPropertiesController::save() {

    updateStructures();

    if(experiment->hasRessource()) {

        // To exp ressource
        Ressource* to = experiment->getRessource();
        int code = to->save(experiment->serialize());

        // Error
        if(code != 0) {
            QMessageBox::warning(this, "Impossible to save experiment",
            QString("Impossible to save experiment : error code : ") + QString::number(code));

            experiment->setRessource(NULL);
        }
    }
}

void ExperimentsPropertiesController::saveToFile() {

    updateStructures();

    // To new file
    const QString DEFAULT_DIR_KEY("default_dir");
    QSettings mySettings;
    QString selectedFile = QFileDialog::getSaveFileName(this, "Save your experiment", mySettings.value(DEFAULT_DIR_KEY).toString(),"Experiment (*.exp)");

    if (!selectedFile.isEmpty()) {
        QDir CurrentDir;
        mySettings.setValue(DEFAULT_DIR_KEY, CurrentDir.absoluteFilePath(selectedFile));

        Ressource* to = new JsonFile(selectedFile);
        int code = to->save(experiment->serialize());

        if(code == 0)
            experiment->setRessource(to);
        else {
            QMessageBox::warning(this, "Impossible to save experiment",
                                 QString("Impossible to save experiment : error code : ") + QString::number(code));

            experiment->setRessource(NULL);
        }
    }
}

void ExperimentsPropertiesController::updateStructures() {

    // Information
    experiment->setId(ui->leId->text());
    experiment->setDescription(ui->leDescription->toPlainText());
    experiment->setAuthor(ui->leAuthor->text());
    experiment->setComments(ui->leComments->toPlainText());
    experiment->setDateOfCreation(QDateTime::fromString(ui->lDateOfCreation->text(),"yyyy-MM-dd hh:mm:ss"));

    // Simulation
    experiment->setDuration(ui->leDuration->text().toInt());
    experiment->setTimeToWaitForStability(ui->leTimeToWaitForStability->text().toInt());
    experiment->setOnlyIfEntityIsStable(ui->cbOnlyIfEntityIsStable->isChecked());
    experiment->setStopIfEntityIsNotInOnePiece(ui->cbStopIfEntityIsNotInOnePiece->isChecked());

    // Mutations
    boneLengthMutation->save();
    boneRadiusMutation->save();
    fixationRadiusMutation->save();
    boneAngularOrigin->save();
    bonesStructuralMutation->save();
    sensorsStructuralMutation->save();

    brainSize->save();
    brainInPos->save();
    brainInWeight->save();
    brainMemorySize->save();
    brainFrequency->save();
    constValue->save();
    newBrainTree->save();

    // World
    QVariantMap worldMap;

    // -- Biome --
    QVariantMap biomeMap;
    biomeMap.insert("lights",QxtJSON::parse(ui->teLights->toPlainText()));
    worldMap.insert("biome",biomeMap);

    // -- Scene --
    QVariantMap sceneMap = experiment->getWorldDataMap()["scene"].toMap();
    QVariantMap camMap;
    camMap.insert("posX",ui->leCamPosX->text().toDouble());
    camMap.insert("posY",ui->leCamPosY->text().toDouble());
    camMap.insert("posZ",ui->leCamPosZ->text().toDouble());
    camMap.insert("targetX",ui->leCamTargetX->text().toDouble());
    camMap.insert("targetY",ui->leCamTargetY->text().toDouble());
    camMap.insert("targetZ",ui->leCamTargetZ->text().toDouble());
    sceneMap.insert("camera",camMap);
    sceneMap.insert("shapes",QxtJSON::parse(ui->teStaticShapes->toPlainText()));
    sceneMap.insert("spawns",QxtJSON::parse(ui->teSpawns->toPlainText()));

    worldMap.insert("scene",sceneMap);

    experiment->setWorldData(worldMap);
}

void ExperimentsPropertiesController::loadExp() {

    const QString DEFAULT_DIR_KEY("default_dir");
    QSettings mySettings;
    QString selectedFile = QFileDialog::getOpenFileName(this, "Select an experiment", mySettings.value(DEFAULT_DIR_KEY).toString(),"Exp (*.exp)");

    if (!selectedFile.isEmpty()) {
        QDir CurrentDir;
        mySettings.setValue(DEFAULT_DIR_KEY, CurrentDir.absoluteFilePath(selectedFile));

        // Load Generic Entity
        Ressource* from = new JsonFile(selectedFile);
        QVariant expData = from->load();

        // TODO Error ???
//        if(exp.toMap().contains("Error")){
//        }
//        else {
//        }

        Experiment *experiment = new Experiment(expData);
        experiment->setRessource(from);
        setExperiment(experiment);
        emit experimentLoaded(experiment);
    }
}

void ExperimentsPropertiesController::enterInWhatsThisMode() {
    QWhatsThis::enterWhatsThisMode();
}
