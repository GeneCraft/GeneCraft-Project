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
#include "uitools.h"
#include "events/inspectorsinputmanager.h"

// floor dialog
#include "floordialog.h"

namespace GeneCraftCore {

QList<QString> gravitiesName;
QList<double> gravities;
QList<QString> skyMaterials;
QList<QString> floorsMaterials;

ExperimentsPropertiesController::ExperimentsPropertiesController(QWidget *parent) :
    QWidget(parent), ui(new Ui::ExperimentsPropertiesController)
{
    ui->setupUi(this);

    setupForm();

    setExperiment(NULL);
}

void ExperimentsPropertiesController::setupForm() {

    // ----------------
    // -- connexions --
    // ----------------
    connect(ui->pbSave,SIGNAL(clicked()),this,SLOT(save()));
    connect(ui->pbSaveAndReload,SIGNAL(clicked()),this,SLOT(saveAndReload()));
    connect(ui->pbClose,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->pbHelp,SIGNAL(clicked()),this,SLOT(enterInWhatsThisMode()));

    // FIXME What's mode doesn't work on MacOS
    #ifdef __APPLE__
        this->ui->pbHelp->setEnabled(false);
    #endif

    connect(ui->pbLoadExp,SIGNAL(clicked()),this,SLOT(loadExpFromFile()));
    connect(ui->pbSaveToFile,SIGNAL(clicked()),this,SLOT(saveExpToFile()));

    connect(ui->pbLoadWorldFromFile,SIGNAL(clicked()),this,SLOT(loadWorldFromFile()));
    connect(ui->pbSaveWorldToFile,SIGNAL(clicked()),this,SLOT(saveWorldToFile()));

    connect(ui->pbAddEntityToSeed,SIGNAL(clicked()),this,SLOT(addEntityToSeed()));
    connect(ui->pbRemoveEntityFromSeed,SIGNAL(clicked()),this,SLOT(removeEntityFromSeed()));
    connect(ui->pbViewGenome,SIGNAL(clicked()),this,SLOT(viewGenome()));
    connect(ui->pbViewAvailableGenome,SIGNAL(clicked()),this,SLOT(viewAvailableGenome()));

    connect(ui->gbFamily,SIGNAL(toggled(bool)),this,SLOT(gbFamilyToggled(bool)));
    connect(ui->gbFixedGenomes,SIGNAL(toggled(bool)),this,SLOT(gbFixedGenomes(bool)));
    connect(ui->pbRefreshRessources,SIGNAL(clicked()),this,SLOT(refreshRessources()));
    connect(ui->pbAddFromGenome,SIGNAL(clicked()),this,SLOT(addFromGenome()));

    connect(ui->pbTakeFromCamera,SIGNAL(clicked()),this,SLOT(takeFromCamera()));

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

    skyMaterials << "Examples/SpaceSkyBox"
                 << "Examples/CloudyNoonSkyBox"
                 << "Examples/StormySkyBox"
                 << "Examples/EarlyMorningSkyBox"
                 << "Examples/MorningSkyBox"
                 << "Examples/EveningSkyBox"
                 << "Examples/CloudySky";

    for(int i=0; i<skyMaterials.count();++i)
        ui->cbSkyMaterial->addItem(skyMaterials.at(i));

    floorsMaterials << "GeneCraft/GrassFloor"
                   << "GeneCraft/DesertFloor"
                   << "GeneCraft/DesertFloor_2"
                   << "GeneCraft/StoneRoadFloor"
                   << "GeneCraft/MoonFloor"
                   << "GeneCraft/WoodFloor";

    for(int i=0; i<floorsMaterials.count();++i)
        ui->cbFloorMaterial->addItem(floorsMaterials.at(i));

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

void ExperimentsPropertiesController::connectToInspectorInputManager(InspectorsInputManager * iim) {

    connect(this,SIGNAL(sLoadExperiment(Experiment *)),iim,SLOT(loadExperiment(Experiment*)));
    connect(this,SIGNAL(sExperimentUpdated(Experiment*)),iim,SLOT(experimentUpdated(Experiment*)));
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

    if(ui->twEntitiesSelected->currentItem()) {
        EntityTreeWidgetItem *entity = (EntityTreeWidgetItem *) ui->twEntitiesSelected->currentItem();
        ui->teGenome->setText(Ressource::beautifullJson(entity->dataw.data));
    }
    else
        qDebug() << "no items selected";
}

void ExperimentsPropertiesController::viewAvailableGenome() {

    if(ui->twEntitiesAvailable->currentItem()) {
        EntityTreeWidgetItem *entity = (EntityTreeWidgetItem *) ui->twEntitiesAvailable->currentItem();
        ui->teGenome->setText(Ressource::beautifullJson(entity->dataw.data));
    }
    else
        qDebug() << "no items selected";
}

void ExperimentsPropertiesController::addFromGenome() {

    QString text = ui->teGenome->toPlainText().trimmed();

    if(!text.isEmpty())
        ui->twEntitiesSelected->insertTopLevelItem(0,new EntityTreeWidgetItem(QxtJSON::parse(text).toMap()));
    else
        qDebug() << "genome empty";
}

void ExperimentsPropertiesController::refreshRessources() {

    // clear lists
    UITools::clearTreeWidget(this->ui->twEntitiesAvailable);

    // available genomes
    localRessourceManager->reloadDir();
    foreach(DataWrapper entity, localRessourceManager->getCreatures())
        ui->twEntitiesAvailable->insertTopLevelItem(0,new EntityTreeWidgetItem(entity));
}

void ExperimentsPropertiesController::setExperiment(Experiment *experiment){

    this->experiment = experiment;

    setEnabled((bool) experiment);

    if(experiment) {

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
        ui->teDieFunction->setText(Ressource::beautifullJson(experiment->getDieFunction()));
        ui->teEndFunction->setText(Ressource::beautifullJson(experiment->getEndFunction()));

        // ----------------
        // -- evaluation --
        // ----------------
        ui->teValidateFunction->setText(Ressource::beautifullJson(experiment->getValidityFunction()));
        ui->teFitnessFunction->setText(Ressource::beautifullJson(experiment->getEvalFunction()));
        ui->spbNbRun->setValue(experiment->getNbRun());
        ui->chkRandomPos->setChecked(experiment->getSpawnNoise());

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
        while(ui->vlSensorsAndEffectorsMutations->count() != 0) {
            QWidget *w = ui->vlSensorsAndEffectorsMutations->itemAt(0)->widget();
            ui->vlSensorsAndEffectorsMutations->removeWidget(w);
            delete w;
        }


        // -- Create mutations widgets --
        MutationsManager *mutationsManager = experiment->getMutationsManager();

        // bone
        boneLengthMutation = new FloatMutationController(mutationsManager->boneLength,"Bones Length");
        boneRadiusMutation = new FloatMutationController(mutationsManager->boneRadius,"Bones Radius");
        boneAngularOrigin = new FloatMutationController(mutationsManager->boneAngularOrigin,"Bones angular origin");
        boneAngularLimitsMutation = new FloatMutationController(mutationsManager->boneAngularLimits->axisMutation,"Bones angular limits");
        bonesStructuralMutation = new StructuralMutationController(mutationsManager->bonesStructural,"Bones Structural");

        // fixation
        fixationRadiusMutation = new FloatMutationController(mutationsManager->fixRadius,"Fixations Radius");

        // snesors & effectors
        sensorsStructuralMutation = new StructuralMutationController(mutationsManager->sensorsStructural,"Sensors Structural", mutationsManager->sensorsStructuralList);
        effectorsStructuralMutation = new StructuralMutationController(mutationsManager->effectorsStructural,"Effectors Structural", mutationsManager->effectorsStructuralList);

        // brain
        brainDistance = new FloatMutationController(mutationsManager->brainDistance,"Input propagation");
        brainInPos = new FloatMutationController(mutationsManager->brainInPos,"BrainIn Position");
        brainInWeight = new FloatMutationController(mutationsManager->brainWeight,"BrainIn Weight");
        brainMemorySize = new IntegerMutationController(mutationsManager->brainMemorySize,"Brain Mermory Size");
        brainFrequency = new IntegerMutationController(mutationsManager->brainFrequency,"Brain Frequency");
        constValue = new FloatMutationController(mutationsManager->constValue,"Constant Value");
        brainStructuralMutation = new StructuralMutationController(mutationsManager->brainStructural, "Brain Structural", mutationsManager->brainNodeList);

        // -- Add mutations widgets --
        ui->vlBodyMutations->addWidget(boneLengthMutation);
        ui->vlBodyMutations->addWidget(boneRadiusMutation);
        ui->vlBodyMutations->addWidget(boneAngularOrigin);
        ui->vlBodyMutations->addWidget(boneAngularLimitsMutation);
        ui->vlBodyMutations->addWidget(bonesStructuralMutation);

        ui->vlBodyMutations->addWidget(fixationRadiusMutation);

        ui->vlSensorsAndEffectorsMutations->addWidget(sensorsStructuralMutation);
        ui->vlSensorsAndEffectorsMutations->addWidget(effectorsStructuralMutation);

        ui->vlBrainMutations->addWidget(brainDistance);
        ui->vlBrainMutations->addWidget(brainInPos);
        ui->vlBrainMutations->addWidget(brainInWeight);
        ui->vlBrainMutations->addWidget(brainMemorySize);
        ui->vlBrainMutations->addWidget(brainFrequency);
        ui->vlBrainMutations->addWidget(constValue);
        ui->vlBrainMutations->addWidget(brainStructuralMutation);

        // -----------
        // -- world --
        // -----------
        setWorld(experiment->getWorldDataMap());

        // -----------
        // -- seeds --
        // -----------

        // clear lists
        UITools::clearTreeWidget(this->ui->twEntitiesAvailable);
        UITools::clearTreeWidget(this->ui->twEntitiesSelected);

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
    ui->teLights->setText(Ressource::beautifullJson(biomeMap["lights"]));

    // -- Scene --
    QVariantMap sceneMap = worldData["scene"].toMap();

    // floor
    QVariantMap floorMap = sceneMap["floor"].toMap();
    QString type = floorMap["type"].toString();

    this->ui->lblFloorType->setText(type);
    /*if(type == "flatland") {

        ui->cbFloor->setCurrentIndex(1);

        QString material = floorMap["material"].toString();

        for(int i=0; i<floorsMaterials.count();++i)
            if(material == floorsMaterials.at(i))
                ui->cbFloorMaterial->setCurrentIndex(i);
    } else if(type =="boxfloor") {

        ui->cbFloor->setCurrentIndex(2);

        QString material = floorMap["material"].toString();

        for(int i=0; i<floorsMaterials.count();++i)
            if(material == floorsMaterials.at(i))
                ui->cbFloorMaterial->setCurrentIndex(i);
    }
    else
        ui->cbFloor->setCurrentIndex(0);*/

    // camera
    QVariantMap camMap = sceneMap["camera"].toMap();
    ui->leCamPosX->setText(camMap["posX"].toString());
    ui->leCamPosY->setText(camMap["posY"].toString());
    ui->leCamPosZ->setText(camMap["posZ"].toString());
    ui->leCamTargetX->setText(camMap["targetX"].toString());
    ui->leCamTargetY->setText(camMap["targetY"].toString());
    ui->leCamTargetZ->setText(camMap["targetZ"].toString());

    // shapes
    ui->teStaticShapes->setText(Ressource::beautifullJson(sceneMap["shapes"]));

    // spawns
    ui->teSpawns->setText(Ressource::beautifullJson(sceneMap["spawns"]));
}

ExperimentsPropertiesController::~ExperimentsPropertiesController() {
    delete ui;
}

void ExperimentsPropertiesController::save() {

    if(experiment->hasRessource()) {

        updateStructures();

        // To exp ressource
        Ressource* to = experiment->getRessource();
        int code = to->save(experiment->serialize());

        // Error
        if(code != 0) {
            QMessageBox::warning(this, "Impossible to save experiment",
            QString("Impossible to save experiment : error code : ") + QString::number(code));

            experiment->setRessource(NULL);
            return;
        }

        emit sExperimentUpdated(experiment);
    }
    else
        saveExpToFile();
}

void ExperimentsPropertiesController::saveAndReload() {

    save();

    emit sLoadExperiment(experiment);
}

void ExperimentsPropertiesController::saveExpToFile() {

    updateStructures();

    // To new file
    QString selectedFile = QFileDialog::getSaveFileName(this, "Save your experiment", "./ressources/" + experiment->getId() + ".exp","Experiment (*.exp)");

    if(selectedFile.isEmpty())
        return;

    Ressource* to = new JsonFile(selectedFile);
    int code = to->save(experiment->serialize());

    if(code == 0) {
        experiment->setRessource(to);
        emit sExperimentUpdated(experiment);
    }
    else {
        QMessageBox::warning(this, "Impossible to save experiment",
                             QString("Impossible to save experiment : error code : ") + QString::number(code));

        experiment->setRessource(NULL);
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
    experiment->setDieFunction(Ressource::beautifullJson(ui->teDieFunction->toPlainText()));
    experiment->setEndFunction(Ressource::beautifullJson(ui->teEndFunction->toPlainText()));

    // Evaluation
    experiment->setValidityFunction(Ressource::beautifullJson(ui->teValidateFunction->toPlainText()));
    experiment->setEvalFunction(Ressource::beautifullJson(ui->teFitnessFunction->toPlainText()));
    experiment->setNbRun(ui->spbNbRun->value());
    experiment->setSpawnNoise(ui->chkRandomPos->isChecked());

    // Mutations
    boneLengthMutation->save();
    boneRadiusMutation->save(); 
    boneAngularOrigin->save();
    boneAngularLimitsMutation->save();
    bonesStructuralMutation->save();

    fixationRadiusMutation->save();

    sensorsStructuralMutation->save();
    effectorsStructuralMutation->save();

    brainDistance->save();
    brainInPos->save();
    brainInWeight->save();
    brainMemorySize->save();
    brainFrequency->save();
    constValue->save();
    brainStructuralMutation->save();

    // World
    experiment->setWorldData(getWorldMap());

    // Seed
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
    QVariantMap worldMap = experiment->getWorldDataMap();
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

    //QVariantMap floorMap;
    //floorMap.insert("type",ui->cbFloor->currentText());

    /*if(ui->cbFloor->currentText() == "flatland")
        floorMap.insert("material",ui->cbFloorMaterial->currentText());
    if(ui->cbFloor->currentText() == "boxfloor")
        floorMap.insert("material",ui->cbFloorMaterial->currentText());
    */

    //sceneMap.insert("floor",floorMap);
    sceneMap.insert("shapes",QxtJSON::parse(ui->teStaticShapes->toPlainText()));
    sceneMap.insert("spawns",QxtJSON::parse(ui->teSpawns->toPlainText()));
    worldMap.insert("scene",sceneMap);

    return worldMap;
}


void ExperimentsPropertiesController::loadExpFromFile() {

    QSettings mySettings;
    QString selectedFile = QFileDialog::getOpenFileName(this, "Select an experiment", mySettings.value("RESSOURCES_FOLDER").toString(),"Exp (*.exp)");

    if (!selectedFile.isEmpty()) {
        QDir CurrentDir;
        mySettings.setValue("RESSOURCES_FOLDER", CurrentDir.absoluteFilePath(selectedFile));

        // Load Generic Entity
        Ressource* from = new JsonFile(selectedFile);
        QVariant expData = from->load();
        Experiment *experiment = new Experiment(expData);
        experiment->setRessource(from);
        setExperiment(experiment);
        //emit sLoadExperiment(experiment);
    }
}

void ExperimentsPropertiesController::loadWorldFromFile() {

    const QString DEFAULT_DIR_KEY("RESSOURCES_FOLDER");
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

    QVariantMap worldMap = getWorldMap();

    // To new file
    QString selectedFile = QFileDialog::getSaveFileName(this, "Save your world", "./ressources/" + worldMap["name"].toString() + ".world", "World (*.world)");

    if (selectedFile.isEmpty())
        return;

    Ressource* to = new JsonFile(selectedFile);
    int code = to->save(worldMap);

    if(code != 0) {
        QMessageBox::warning(this, "Impossible to save world",
                             QString("Impossible to save world : error code : ") + QString::number(code));
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

void ExperimentsPropertiesController::takeFromCamera() {

    // TODO need factory...
    // get camera position
//    OgreEngine *ogreEngine = static_cast<OgreEngine*>(factory->getEngines().find("Ogre").value());
//    Ogre::Camera *camera = ogreEngine->getOgreSceneManager()->getCamera("firstCamera");
//    Ogre::Vector3 position = camera->getPosition();
//    Ogre::Vector3 target = camera->getPosition() + camera->getDirection() * 10;
}

void GeneCraftCore::ExperimentsPropertiesController::on_btnFloor_clicked()
{
    QVariantMap map = experiment->getWorldDataMap();
    QVariant floorMap = map["floor"];
    FloorDialog fd(floorMap);
    fd.exec();
    floorMap = fd.serialize();

    map.remove("floor");
    map.insert("floor", floorMap);
    experiment->setWorldData(map);

    this->ui->lblFloorType->setText(floorMap.toMap()["type"].toString());
}

}


