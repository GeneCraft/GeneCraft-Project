#include "experimentspropertiescontroller.h"
#include "ui_experimentspropertiescontroller.h"

#include <QWhatsThis>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>

#include "experiment/experiment.h"

// mutations
#include "floatmutationcontroller.h"
#include "integermutationcontroller.h"
#include "simpleprobabilitycontroller.h"
#include "structuralmutationcontroller.h"
#include "mutation/mutationsmanager.h"

// world
#include "world/btobiome.h"

// ressources
#include "ressources/jsonfile.h"
#include "qxtjson.h"
#include "ressourcesItems.h"
#include "ressources/ressourcesmanager.h"

// others
#include "tools.h"

using namespace GeneLabCore;

QList<QString> gravitiesName;
QList<double> gravities;
QList<QString> skyMaterials;

ExperimentsPropertiesController::ExperimentsPropertiesController(Experiment *experiment, QWidget *parent) :
    QWidget(parent), ui(new Ui::ExperimentsPropertiesController)
{
    ui->setupUi(this);

    setupForm();

    setExperiment(experiment);
}

void ExperimentsPropertiesController::setupForm() {

    // ----------------
    // -- connexions --
    // ----------------
    connect(ui->pbSave,SIGNAL(clicked()),this,SLOT(save()));
    connect(ui->pbClose,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->pbHelp,SIGNAL(clicked()),this,SLOT(enterInWhatsThisMode()));

    connect(ui->pbLoadExp,SIGNAL(clicked()),this,SLOT(loadExpFromFile()));
    connect(ui->pbSaveToFile,SIGNAL(clicked()),this,SLOT(saveExpToFile()));

    connect(ui->pbLoadWorldFromFile,SIGNAL(clicked()),this,SLOT(loadWorldFromFile()));
    connect(ui->pbSaveWorldToFile,SIGNAL(clicked()),this,SLOT(saveWorldToFile()));

    connect(ui->pbAddEntityToSeed,SIGNAL(clicked()),this,SLOT(addEntityToSeed()));
    connect(ui->pbRemoveEntityFromSeed,SIGNAL(clicked()),this,SLOT(removeEntityFromSeed()));
    connect(ui->pbViewGenome,SIGNAL(clicked()),this,SLOT(viewGenome()));

    connect(ui->gbFamily,SIGNAL(toggled(bool)),this,SLOT(gbFamilyToggled(bool)));
    connect(ui->gbFixedGenomes,SIGNAL(toggled(bool)),this,SLOT(gbFixedGenomes(bool)));
    connect(ui->pbRefreshRessources,SIGNAL(clicked()),this,SLOT(refreshRessources()));

    // -----------
    // -- world --
    // -----------
    gravitiesName << "Earth" << "Moon" << "Mercury" << "Venus" << "Mars" << "Jupiter"
                  << "Io" << "Europa" << "Ganymede" << "Callisto" << "Saturn" << "Titan" << "Uranus"
                  << "Titania" << "Oberon" << "Neptune" << "Triton" << "Pluto" << "Eris" << "Sun" << "Space";

    gravities << 9.81 << 1.625 << 3.703 << 8.872  << 3.728 << 25.93 << 1.789 << 1.314
              << 1.426 << 1.24 << 11.19 << 1.3455 << 9.01 << 0.379 << 0.347 << 11.28 << 0.779 << 0.61 << 0.8 << 274.1 << 0.0;

    for(int i=0; i<gravitiesName.count();++i)
        ui->cbGravity->addItem(QString::number(gravities.at(i)) + " - " + gravitiesName.at(i));

    skyMaterials << "Examples/TrippySkyBox"
                 << "Examples/SpaceSkyBox"
                 << "Examples/CloudyNoonSkyBox"
                 << "Examples/StormySkyBox"
                 << "Examples/EarlyMorningSkyBox"
                 << "Examples/MorningSkyBox"
                 << "Examples/EveningSkyBox"
                 << "Examples/CloudySky";

    for(int i=0; i<skyMaterials.count();++i)
        ui->cbSkyMaterial->addItem(skyMaterials.at(i));


    // ----------------
    // -- ressources --
    // ----------------

    // TODO QSettings
    DataBase database;
    database.dbName = "/db/genecraft/";
    database.url = "http://www.genecraft-project.org";
    database.port = 80;

    localRessourceManager = new RessourcesManager(database,QDir("ressources"));
}

void ExperimentsPropertiesController::removeEntityFromSeed() {

    if(ui->twEntitiesSelected->currentItem() > 0) {

        QTreeWidgetItem * item = ui->twEntitiesSelected->currentItem();
        int i = ui->twEntitiesSelected->indexOfTopLevelItem(item);
        ui->twEntitiesSelected->takeTopLevelItem(i);
        delete item;

        //EntityTreeWidgetItem *entity = (EntityTreeWidgetItem *) ui->twEntitiesSelected->currentItem();
        //ui->twEntitiesSelected->removeItemWidget(entity,0);
        //ui->twEntitiesSelected->setCurrentItem(NULL,0);
        //delete entity;
    }
    else
        qDebug() << "no items selected";
}

void ExperimentsPropertiesController::addEntityToSeed() {

    if(ui->twEntitiesAvailable->currentItem() && ui->twEntitiesAvailable->columnCount() > 0) {

        // can't copy directly the pointer !
        // esle error during Tools::clearTreeWidget (double delete)
        EntityTreeWidgetItem *entity = (EntityTreeWidgetItem *)  ui->twEntitiesAvailable->currentItem();
        EntityTreeWidgetItem *newEntity = new EntityTreeWidgetItem(entity->dataw.data);
        ui->twEntitiesSelected->insertTopLevelItem(0,newEntity);
    }
    else
        qDebug() << "no items selected";
}

void ExperimentsPropertiesController::viewGenome() {

    if(ui->twEntitiesSelected->currentItem() && ui->twEntitiesAvailable->columnCount() > 0) {
        EntityTreeWidgetItem *entity = (EntityTreeWidgetItem *) ui->twEntitiesSelected->currentItem();
        ui->teGenome->setText(QxtJSON::stringify(entity->dataw.data));
    }
    else
        qDebug() << "no items selected";
}

void ExperimentsPropertiesController::refreshRessources() {

    // clear lists
    Tools::clearTreeWidget(this->ui->twEntitiesAvailable);

    // available genomes
    localRessourceManager->reloadDir();
    foreach(DataWrapper entity, localRessourceManager->getCreatures())
        ui->twEntitiesAvailable->insertTopLevelItem(0,new EntityTreeWidgetItem(entity));
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
    setWorld(experiment->getWorldDataMap());

    // -----------
    // -- seeds --
    // -----------

    // clear lists
    Tools::clearTreeWidget(this->ui->twEntitiesAvailable);
    Tools::clearTreeWidget(this->ui->twEntitiesSelected);

    // available genomes
    localRessourceManager->reloadDir();
    foreach(DataWrapper entity, localRessourceManager->getCreatures())
        ui->twEntitiesAvailable->insertTopLevelItem(0,new EntityTreeWidgetItem(entity));

    // default check in QtCreator, check false to emit toggle and disable others...
    ui->gbFixedGenomes->setChecked(false);

    QVariantMap seedsMap = experiment->getSeedInfo();
    QString seedType = seedsMap["type"].toString();
    if(seedType == "family") {

        ui->gbFamily->setChecked(true);
        QString family = seedsMap["family"].toString();

        for(int i=0;i < ui->cbFamily->count();++i)
            if(family == ui->cbFamily->itemText(i).toLower())
                ui->cbFamily->setCurrentIndex(i);

    } else if(seedType == "fixedGenomes") {

        ui->gbFixedGenomes->setChecked(true);
        if(seedsMap.contains("genomes"))
        {
            QVariantList genomesList = seedsMap["genomes"].toList();

            foreach(QVariant genome, genomesList)
                ui->twEntitiesSelected->insertTopLevelItem(0,new EntityTreeWidgetItem(genome.toMap()));
        }
    }
}

void ExperimentsPropertiesController::setWorld(QVariantMap worldData){

    // -- world --
    ui->leWorldName->setText(worldData["name"].toString());

    // -- Biome --
    QVariantMap biomeMap = worldData["biome"].toMap();
    double gravity = biomeMap["gravity"].toDouble();

    for(int i=0; i<gravitiesName.count();++i)
        if(gravity == gravities.at(i))
            ui->cbGravity->setCurrentIndex(i);

    QString skyMaterial = biomeMap["skyMaterial"].toString();
    for(int i=0; i<skyMaterials.count();++i)
        if(skyMaterial == skyMaterials.at(i))
            ui->cbSkyMaterial->setCurrentIndex(i);

    // lights
    ui->teLights->setText(QxtJSON::stringify(biomeMap["lights"]));

    // -- Scene --
    QVariantMap sceneMap = worldData["scene"].toMap();

    // floor
    QVariantMap floorMap = sceneMap["floor"].toMap();
    QString type = floorMap["type"].toString();
    for(int i=0;i<ui->cbFloor->count();++i)
        if(type == ui->cbFloor->itemText(i))
            ui->cbFloor->setCurrentIndex(i);

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

    emit experimentLoaded(experiment);
}

void ExperimentsPropertiesController::saveExpToFile() {

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

    experiment->setWorldData(getWorldMap());

    experiment->setSeedInfo(getSeedMap());
}
QVariantMap ExperimentsPropertiesController::getSeedMap() {

    QVariantMap seedMap;
    if(ui->gbFamily->isChecked()) {

        seedMap.insert("type","family");
        seedMap.insert("family",ui->cbFamily->currentText().toLower());

    } else {

        seedMap.insert("type","fixedGenomes");

        QVariantList genomes;

        for(int i=0; i < ui->twEntitiesSelected->topLevelItemCount(); ++i) {
           EntityTreeWidgetItem *entityItem = (EntityTreeWidgetItem *) ui->twEntitiesSelected->topLevelItem(i);
           genomes.append(entityItem->dataw.data);
        }
        seedMap.insert("genomes",genomes);
    }

    return seedMap;
}


QVariantMap ExperimentsPropertiesController::getWorldMap() {

    // World
    QVariantMap worldMap;
    worldMap.insert("name",ui->leWorldName->text());

    // -- Biome --
    QVariantMap biomeMap;
    biomeMap.insert("gravity",gravities[ui->cbGravity->currentIndex()]);
    biomeMap.insert("lights",QxtJSON::parse(ui->teLights->toPlainText()));
    biomeMap.insert("skyMaterial",skyMaterials[ui->cbSkyMaterial->currentIndex()]);
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

    QVariantMap floorMap;
    floorMap.insert("type",ui->cbFloor->currentText());

    if(ui->cbFloor->currentText() == "flatland")
        floorMap.insert("material",ui->cbFloorMaterial->currentText());

    sceneMap.insert("floor",floorMap);
    sceneMap.insert("shapes",QxtJSON::parse(ui->teStaticShapes->toPlainText()));
    sceneMap.insert("spawns",QxtJSON::parse(ui->teSpawns->toPlainText()));
    worldMap.insert("scene",sceneMap);

    return worldMap;
}


void ExperimentsPropertiesController::loadExpFromFile() {

    const QString DEFAULT_DIR_KEY("default_dir");
    QSettings mySettings;
    QString selectedFile = QFileDialog::getOpenFileName(this, "Select an experiment", mySettings.value(DEFAULT_DIR_KEY).toString(),"Exp (*.exp)");

    if (!selectedFile.isEmpty()) {
        QDir CurrentDir;
        mySettings.setValue(DEFAULT_DIR_KEY, CurrentDir.absoluteFilePath(selectedFile));

        // Load Generic Entity
        Ressource* from = new JsonFile(selectedFile);
        QVariant expData = from->load();
        Experiment *experiment = new Experiment(expData);
        experiment->setRessource(from);
        setExperiment(experiment);
        emit experimentLoaded(experiment);
    }
}

void ExperimentsPropertiesController::loadWorldFromFile() {

    const QString DEFAULT_DIR_KEY("default_dir");
    QSettings mySettings;
    QString selectedFile = QFileDialog::getOpenFileName(this, "Select a world", mySettings.value(DEFAULT_DIR_KEY).toString(),"World (*.world)");

    if (!selectedFile.isEmpty()) {
        QDir CurrentDir;
        mySettings.setValue(DEFAULT_DIR_KEY, CurrentDir.absoluteFilePath(selectedFile));

        // Load Generic Entity
        Ressource* from = new JsonFile(selectedFile);
        QVariant data = from->load();
        setWorld(data.toMap());
    }
}

void ExperimentsPropertiesController::saveWorldToFile() {

    // To new file
    const QString DEFAULT_DIR_KEY("default_dir");
    QSettings mySettings;
    QString selectedFile = QFileDialog::getSaveFileName(this, "Save your world", mySettings.value(DEFAULT_DIR_KEY).toString(),"World (*.world)");

    if (!selectedFile.isEmpty()) {
        QDir CurrentDir;
        mySettings.setValue(DEFAULT_DIR_KEY, CurrentDir.absoluteFilePath(selectedFile));

        Ressource* to = new JsonFile(selectedFile);
        int code = to->save(getWorldMap());

        if(code != 0) {
            QMessageBox::warning(this, "Impossible to save world",
                                 QString("Impossible to save world : error code : ") + QString::number(code));
        }
    }
}


void ExperimentsPropertiesController::enterInWhatsThisMode() {
    QWhatsThis::enterWhatsThisMode();
}

void ExperimentsPropertiesController::gbFamilyToggled(bool checked) {

    disconnect(ui->gbFixedGenomes,SIGNAL(toggled(bool)),this,SLOT(gbFixedGenomes(bool)));
    ui->gbFixedGenomes->setChecked(!checked);
    connect(ui->gbFixedGenomes,SIGNAL(toggled(bool)),this,SLOT(gbFixedGenomes(bool)));
}

void ExperimentsPropertiesController::gbFixedGenomes(bool checked) {

    disconnect(ui->gbFamily,SIGNAL(toggled(bool)),this,SLOT(gbFamilyToggled(bool)));
    ui->gbFamily->setChecked(!checked);
    connect(ui->gbFamily,SIGNAL(toggled(bool)),this,SLOT(gbFamilyToggled(bool)));

}
