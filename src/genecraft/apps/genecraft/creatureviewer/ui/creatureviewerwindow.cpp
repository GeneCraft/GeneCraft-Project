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

#include "creatureviewerwindow.h"
#include "ui_creatureviewerwindow.h"

#include "bullet/btworld.h"

// Qt
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QSettings>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QMap>
#include <QWhatsThis>
#include "creatureviewerabout.h"

// Entity
#include "body/fixation.h"
#include "body/bone.h"
#include "entity.h"
#include "bullet/rigidbodyorigin.h"
#include "families/genericfamily.h"
#include "body/treeshape.h"

// Engine
#include "bullet/bulletengine.h"
#include "Ogre.h"
#include "ogre/ogreengine.h"
#include "btofactory.h"
#include "simulationmanager.h"
#include "events/eventsmanager.h"
#include "bulletogre/bulletogreengine.h"
#include "entities/entitiesengine.h"

// Widgets
#include "widgets/entities/pluggridvisualizer.h"
#include "widgets/entities/pluggriddesignvisualizer.h"
#include "widgets/entities/fixationpropertiescontroller.h"
#include "widgets/entities/bonepropertiescontroller.h"
#include "widgets/entities/entitypropertiescontroller.h"
#include "widgets/experiments/workerctrl.h"
#include "widgets/experiments/experimentctrl.h"
#include "welcomewidget.h"

// Ressources
#include "ressources/ressource.h"
#include "ressources/jsonfile.h"
#include "ressources/dbrecord.h"

#include "families/spiderfamily.h"
#include "families/snakefamily.h"
#include "families/antfamily.h"
#include "families/caterpillarfamily.h"

#include "tools.h"
#include "bulletogre/btoworld.h"
#include "bulletogre/btobiome.h"
#include "bulletogre/btoscene.h"

#include "btoshapesfactory.h"
#include "creaturefactory.h"
#include "btoworldfactory.h"

#include <QThread>
#include <QInputDialog>
#include <QMessageBox>

#include "experiment/experiment.h"
#include "mutation/mutationsmanager.h"

#include "btshapesfactory.h"
#include "btfactory.h"
#include "engines/ogre/ogreengine.h"
#include "engines/ogre/ogrewidget.h"
#include "engines/ogre/entities/ogrefreecamera.h"
#include "bullet/btworld.h"

#include "body/fixation.h"

#include "terrain/terrain.h"

using namespace GeneCraftCore;

CreatureViewerWindow::CreatureViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreatureViewer), selectedEntity(NULL), selectedBone(NULL), selectedFix(NULL)
{
    ui->setupUi(this);
    init();
}

void CreatureViewerWindow::init() {

    // -------------------------
    // -- Essential instances --
    // -------------------------
    factory = new btoFactory(this->ui->centralwidget, (unsigned long) this->winId() );
    BulletOgreEngine *btoEngine = static_cast<BulletOgreEngine*>(factory->getEngineByName("BulletOgre"));
    OgreEngine *ogreEngine = static_cast<OgreEngine*>(factory->getEngineByName("Ogre"));
    Terrain* terrainEngine = (Terrain*)factory->getEngineByName("Terrain");
    shapesFactory   = new btoShapesFactory(btoEngine);
    terrainEngine->setShapesFactory(shapesFactory);
    creatureFactory = new CreatureFactory();
    experiment      = new Experiment();
    world           = btoWorldFactory::createWorld(factory,shapesFactory,experiment->getWorldDataMap());

    // ----------
    // -- Menu --
    // ----------
    connect(this->ui->actionFrom_file,SIGNAL(triggered()),this,SLOT(loadEntityFromFile()));
    connect(this->ui->actionTo_file,SIGNAL(triggered()),this,SLOT(saveEntityToFile()));
    connect(this->ui->actionDatabase, SIGNAL(triggered()), this, SLOT(saveEntityToDb()));
    connect(this->ui->actionNew_creature,SIGNAL(triggered()),this,SLOT(createNewEntity()));
    connect(this->ui->actionRemove_creature,SIGNAL(triggered()),this,SLOT(removeEntity()));
    connect(this->ui->actionAbout_CreatureViewer,SIGNAL(triggered()),this,SLOT(showAbout()));
    connect(this->ui->aEnterInWhatsThisMode,SIGNAL(triggered()),this,SLOT(enterInWhatsThisMode()));

    // FIXME What's mode doesn't work on MacOS
    #ifdef __APPLE__
        this->ui->aEnterInWhatsThisMode->setEnabled(false);
    #endif

    // -------------------
    // -- Mode Tool bar --
    // -------------------

    QToolBar *tb = new QToolBar(this);
    tb->setWindowTitle("Mode Toolbar");
    addToolBar(Qt::LeftToolBarArea, tb);
    tb->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tb->setIconSize(QSize(32,32));

    aWelcomeMode = tb->addAction(QIcon(":img/logos/GeneCraft_logo"),"Welcome");
    aDesignerMode = tb->addAction(QIcon(":img/icons/ruler_pencil_32"),"Designer");
    aExperimentMode = tb->addAction(QIcon(":img/icons/dna_32"),"Experiment");
    aTheaterMode = tb->addAction(QIcon(":img/icons/theater_32"),"Theater");

    aWelcomeMode->setCheckable(true);
    aDesignerMode->setCheckable(true);
    aExperimentMode->setCheckable(true);
    aTheaterMode->setCheckable(true);

    connect(aWelcomeMode,SIGNAL(triggered()),this,SLOT(switchToWelcomeMode()));
    connect(aDesignerMode,SIGNAL(triggered()),this,SLOT(switchToDesignerMode()));
    connect(aExperimentMode,SIGNAL(triggered()),this,SLOT(switchToExperimentMode()));
    connect(aTheaterMode,SIGNAL(triggered()),this,SLOT(switchToTheaterMode()));

    // -------------------
    // -- Main Tool bar --
    // -------------------

    // create actions & add to bar
    ui->toolBar->setWindowTitle("Main Toolbar");
    QAction *aNewCreature = ui->toolBar->addAction(QIcon(":img/icons/entity_new"),QString(tr("New creature")));
    QAction *aAddCreature = ui->toolBar->addAction(QIcon(":img/icons/entity_add"),QString(tr("Add creature")));
    QAction *aSaveCreature = ui->toolBar->addAction(QIcon(":img/icons/entity_save"),QString(tr("Save creature")));

    ui->toolBar->addSeparator();
    QAction *aRemoveCreature =  ui->toolBar->addAction(QIcon(":img/icons/entity_delete"),QString(tr("Remove creature")));
    QAction *aRemoveAllCreatures =  ui->toolBar->addAction(QIcon(":img/icons/entity_delete_all"),QString(tr("Remove all creatures")));
    QAction *aRemoveAllCreaturesExceptSelected = ui->toolBar->addAction(QIcon(":img/icons/entity_delete_all_except_one"),QString(tr("Remove all creatures except that selected")));

    ui->toolBar->addSeparator();
    QAction *aAddRandomCreature =  ui->toolBar->addAction(QIcon(":img/icons/entity_add_random"),QString(tr("Add random creature")));
    QAction *aCreateMutationSample =  ui->toolBar->addAction(QIcon(":img/icons/entity_mutation"),QString(tr("Create mutation sample")));

    ui->toolBar->addSeparator();
    aFollowCreature = ui->toolBar->addAction(QIcon(":img/icons/entity_follow"),QString(tr("Follow selected creature")));
    //aFollowCreature->setCheckable(true);
    aShowShadows = ui->toolBar->addAction(QIcon(":img/icons/enable_shadows"),QString(tr("Enable shadows")));
    aShowShadows->setCheckable(true);

    // step manager
    //ui->toolBar->addWidget(new QLabel(tr("Step manager :"));
    ui->toolBar->addSeparator();
    aTogglePhysics = ui->toolBar->addAction(QIcon(":img/icons/bullet_physics_library_stop"),QString(tr("Toggle physics")));
    QSlider *sPhysicStep = new QSlider();
    sPhysicStep->setToolTip(tr("Physical steps by sec. [1..1000]"));
    sPhysicStep->setOrientation(Qt::Horizontal);
    sPhysicStep->setMinimum(1);
    sPhysicStep->setMaximum(1000);
    sPhysicStep->setMaximumWidth(200);
    sPhysicStep->setTickInterval(100);
    sPhysicStep->setTickPosition(QSlider::TicksBelow);
    ui->toolBar->addWidget(sPhysicStep);

    // connections
    connect(aNewCreature,SIGNAL(triggered()),this,SLOT(createNewEntity()));
    connect(aAddCreature,SIGNAL(triggered()),this,SLOT(loadEntityFromFile()));
    connect(aSaveCreature,SIGNAL(triggered()),this,SLOT(saveEntityToFile()));

    connect(aRemoveCreature,SIGNAL(triggered()),this,SLOT(removeEntity()));
    connect(aRemoveAllCreatures,SIGNAL(triggered()),this,SLOT(removeAllEntities()));
    connect(aRemoveAllCreaturesExceptSelected,SIGNAL(triggered()),this,SLOT(removeAllEntitiesExceptSelected()));

    connect(aAddRandomCreature,SIGNAL(triggered()),this,SLOT(addRandomEntity()));
    connect(aCreateMutationSample,SIGNAL(triggered()),this,SLOT(createMutationSample()));

    connect(aFollowCreature,SIGNAL(triggered()),this,SLOT(followSelectedEntity()));
    connect(aShowShadows,SIGNAL(triggered()),this,SLOT(toggleShadows()));


    // -----------
    // -- Docks --
    // -----------

    addDockWidget(Qt::RightDockWidgetArea,ui->dwFixation);
    tabifyDockWidget(ui->dwFixation,ui->dwBone);
    //tabifyDockWidget(ui->dwCreature,ui->dwBrain);
    setTabPosition(Qt::LeftDockWidgetArea,QTabWidget::North);
    //setTabShape(QTabWidget::Triangular);

    // get the QTabBar
    QList<QTabBar *> tabList = findChildren<QTabBar *>();
    foreach(QTabBar * bar,tabList) {
        bar->setCurrentIndex(0);
    }

    setTabPosition(Qt::RightDockWidgetArea,QTabWidget::North);


    // ----------------------
    // -- Events Listeners --
    // ----------------------

    cvim = new CreatureViewerInputManager(btoEngine,ogreEngine->getOgreSceneManager()->getCamera("firstCamera"));
    // add listener in events manager
    EventsManager *eventsManager =  static_cast<EventsManager*>(factory->getEngines().find("Events").value());
    eventsManager->addListener(cvim);



    // ------------------------
    // -- Simulation Manager --
    // ------------------------
    qDebug() << "Init Simulation Manager";
    simulationManager = new SimulationManager(factory->getEngines());
    simulationManager->setup();
    sPhysicStep->setValue(simulationManager->getPhysicsFreq());
    qDebug() << "[OK]\n";


    // ------------------
    // -- Create docks --
    // ------------------

    // Welcome
    WelcomeWidget *welcomeWidget = new WelcomeWidget();
    welcomeWidget->setMaximumSize(400, 166725);
    ui->dwWelcome->setWidget(welcomeWidget);

    // Entity
    entityPropertiesController = new EntityPropertiesController();
    ui->dwCreature->setWidget(entityPropertiesController);
    entityPropertiesController->connectToInspectorInputManager(cvim);

    // Brain
    brainPropertiesController = new BrainPropertiesController();
    PlugGridVisualizer* bViz = new PlugGridVisualizer();
    PlugGridDesignVisualizer* bDezViz = new PlugGridDesignVisualizer();
    brainPropertiesController->setBrainViz(bViz);
    brainPropertiesController->setBrainDesignViz(bDezViz);
    ui->dwBrain->setWidget(brainPropertiesController);
    brainPropertiesController->connectToInspectorInputManager(cvim);

    // Fixation
    fixationPropertiesController = new FixationPropertiesController();
    fixationPropertiesController->connectToInspectorInputManager(cvim);
    ui->dwFixation->setWidget(fixationPropertiesController);

    // Bone
    bonePropertiesController = new BonePropertiesController();
    bonePropertiesController->connectToInspectorInputManager(cvim);
    ui->dwBone->setWidget(bonePropertiesController);

    // Stats
    statsPropertiesController = new StatisticsPropertiesController();
    ui->dwStats->setWidget(statsPropertiesController);
    statsPropertiesController->connectToInspectorInputManager(cvim);

    // Ressources browser
    ressourcesBrowser = new RessourcesBrowser();
    ui->dwRessourcesBrowser->setWidget(ressourcesBrowser);
    ressourcesBrowser->connectToInspectorInputManager(cvim);

    // Worker controller
    workerCtrl = new WorkerCtrl();
    this->ui->dwWorker->setWidget(workerCtrl);
    workerCtrl->connectToInspectorInputManager(cvim);

    // Experiment controller
    expCtrl = new ExperimentCtrl();
    this->ui->dwExperiment->setWidget(expCtrl);
    expCtrl->connectToInspectorInputManager(cvim);
    //connect(expCtrl, SIGNAL(addEntity(QVariantMap, Ressource*)), this, SLOT(addResult(QVariantMap,Ressource*)));

    // ----------------------------------
    // -- Connections to input manager --
    // ----------------------------------

    // To emit when a entity is deleted from tools bar
    connect(cvim,SIGNAL(sEntitySelected(Entity*)),this,SLOT(entitySelected(Entity*)));
    connect(this,SIGNAL(sEntityDeleted(Entity*)),cvim,SLOT(entityDeleted(Entity*)),Qt::DirectConnection);
    connect(cvim,SIGNAL(sBoneDeleted(Bone*)),this,SLOT(boneDeleted(Bone*)),Qt::DirectConnection);
    connect(cvim,SIGNAL(sFixationDeleted(Fixation*)),this,SLOT(fixationDeleted(Fixation*)),Qt::DirectConnection);
    connect(cvim,SIGNAL(sBoneSelected(Bone*)),this,SLOT(boneSelected(Bone*)));
    connect(cvim,SIGNAL(sFixationSelected(Fixation*)),this,SLOT(fixationSelected(Fixation*)));
    connect(cvim,SIGNAL(sLoadExperiment(Experiment*)),this,SLOT(setExperiment(Experiment*)));
    connect(this,SIGNAL(sLoadExperiment(Experiment*)),cvim,SLOT(loadExperiment(Experiment*)),Qt::DirectConnection);
    emit sLoadExperiment(experiment);
    connect(cvim,SIGNAL(sLoadWorld(QVariantMap)),this,SLOT(setWorld(QVariantMap)));
    connect(cvim,SIGNAL(sLoadEntity(QVariantMap,Ressource*)),this,SLOT(addEntity(QVariantMap,Ressource*)));
    connect(cvim,SIGNAL(sLoadResult(Result*)),this,SLOT(loadResult(Result*)));

    // --------------
    // -- Starting --
    // --------------

    qDebug() << "Start simulation";
    simulationManager->fitness = statsPropertiesController->fitness;
    simulationManager->start();
    connect(sPhysicStep,SIGNAL(valueChanged(int)),this->simulationManager,SLOT(setPhysicsFreq(int)));
    connect(aTogglePhysics,SIGNAL(triggered()),this,SLOT(togglePhysics()));
    qDebug() << "[OK]\n";

    cvim->setWorld(world);

    // Init Random
    srand(time(NULL));
    qsrand(time(NULL));

    base.url = "http://www.genecraft-project.org";
    base.dbName = "db/genecraft";
    base.port = 80;

    spawnNew();

    entitySpawner = new QTimer();
    entitySpawner->setInterval(5000);
    //entitySpawner->start();
    connect(entitySpawner, SIGNAL(timeout()), this, SLOT(spawnNew()));


    switchToWelcomeMode();
}

void CreatureViewerWindow::setExperiment(Experiment* experiment)
{
    bool status = simulationManager->status();
    simulationManager->stop();

    // delete the current experiment if it exists and it be different that the new
    if(this->experiment != NULL && this->experiment != experiment)
        delete this->experiment;

    this->experiment = experiment;

    // --------------
    // -- Clearing --
    // --------------

    // entities
    removeAllEntities();

    // bullet
    delete world;
    world = NULL;

    // bullet ogre engine
    BulletOgreEngine *btoEngine = static_cast<BulletOgreEngine*>(factory->getEngineByName("BulletOgre"));
    btoEngine->clearAll();

    // ogre engine
    OgreEngine *ogreEngine = static_cast<OgreEngine*>(factory->getEngineByName("Ogre"));
    ogreEngine->getOgreSceneManager()->clearScene();

    // --------------------------
    // -- Create the new world --
    // --------------------------
    if(experiment != NULL)
        world  = btoWorldFactory::createWorld(factory,shapesFactory,experiment->getWorldDataMap());

    cvim->setWorld(world);

    simulationManager->setStatus(status);
}

void CreatureViewerWindow::setWorld(QVariantMap worldMap) {
    bool status = simulationManager->status();
    this->simulationManager->stop();
    if(experiment != NULL) {
        experiment->setWorldData(worldMap);
        setExperiment(experiment);
    }
    simulationManager->setStatus(status);
}

void CreatureViewerWindow::loadResult(Result *result) {
    bool status = simulationManager->status();
    this->simulationManager->stop();
    setExperiment(experiment);

    QVariantMap genome = result->getGenome().toMap();

    Entity* e = createCreature(genome, world->getSpawnPosition(), result->getRessource());
    if(this->experiment->getOnlyIfEntityIsStable())
        e->addOutScript(0, fromNormal); // Normal position during stability time
    e->addOutScript(result->getStable(), fromBrain); // Next from brain
    e->setAge(0);

    this->simulationManager->setStatus(status);
}

void CreatureViewerWindow::saveEntityToDb() {
    if(selectedEntity != NULL)
    {
        if(!selectedEntity->getRessource()) {
            QString id = QInputDialog::getText(this, "Saving to genecraft-project", "Please, enter the creature id");
            if (id != "") {

                // Load Generic Entity
                DbRecord* to = new DbRecord(base, id);
                to->save(selectedEntity->serialize());

                if(to->error) {
                    QMessageBox msg;
                    msg.setDetailedText(to->errorString);
                    msg.setText("An error did occur during save");
                    msg.setIcon(QMessageBox::Critical);
                    msg.setWindowTitle("Saving to genecraft-project");
                    msg.exec();
                    return;
                } else {
                    selectedEntity->setRessource(to);
                }
            }
        } else {
            selectedEntity->getRessource()->save(selectedEntity->serialize());
        }
    }
    else
        QMessageBox::warning(this, "No entity selected.", "No entity selected.");
}

void CreatureViewerWindow::addRandomEntity(){

    spawnRandomEntities(1);
}

void CreatureViewerWindow::createMutationSample(){

    if(selectedEntity){
        spawnMutationSample(selectedEntity,8);
    }
}

void CreatureViewerWindow::spawnNew() {

    //EntitiesEngine *entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngineByName("Entities"));

    // Clear entities
    /*while(ents.size() != 0){
        Entity * old = ents.takeFirst();
        entitiesEngine->removeEntity(old);
        delete old;
    }*/

    // RANDOM ENTITIES
    spawnRandomEntities(1);
    //Entity* e = entitiesEngine->getAllEntities().first();
    //spawnMutationSample(e, 8);

    // MUTATION
//    //CaterpillarFamily *family = new CaterpillarFamily();
//    //SnakeFamily *family = new SnakeFamily();
//    SpiderFamily *family = new SpiderFamily();
//    //AntFamily *family = new AntFamily();
//    btVector3 pos(0,5,0);
//    Entity *originEntity = family->createEntity(shapesFactory, pos);
//    spawnMutationSample(originEntity, 8);
}

void CreatureViewerWindow::spawnMutationSample(Entity *originEntity, int nbCreatures){

    Entity *e = NULL;
    btVector3 originPos = originEntity->getShape()->getRoot()->getRigidBody()->getWorldTransform().getOrigin();

    //originEntity->setup();
    EntitiesEngine *entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngines().find("Entities").value());
    //entitiesEngine->addEntity(originEntity);
    //ents.append(originEntity);
    QVariant originGenome = originEntity->serialize();

    // circle
    btScalar r = 3 * nbCreatures;
    btScalar angle = 2 * SIMD_PI / nbCreatures;

    // mutations
    for(int i = 0; i < nbCreatures; i++) {

        QVariant newGenome = experiment->getMutationsManager()->mutateEntity(originGenome);

        btVector3 pos(sin(i*angle)*r,5,cos(i*angle)*r); //pos(0, 0, i*15 + 15);//

        e = CreatureFactory::createEntity(newGenome, shapesFactory, pos + originPos);
        if(e == NULL) {
            QMessageBox::warning(this, "Impossible to load entity",
    "Entity could not be created, maybe version of genotype don't match. Please update your client.");
        }

        if(e){
            e->setup();
            entitiesEngine->addEntity(e);
            ents.append(e);
            originGenome = e->serialize();
        }
    }
}

void CreatureViewerWindow::spawnRandomEntities(int nbEntities){

    Entity *e = NULL;
    EntitiesEngine *entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngines().find("Entities").value());

    for(int i = 0; i < nbEntities; i++) {

        int enttype = Tools::random(0,3);
        //enttype = 3;

        btVector3 pos = world->getSpawnPosition();

        switch(enttype)
        {

        case 0 :{
            SpiderFamily *family = new SpiderFamily();
            e = family->createEntity(shapesFactory, pos);
            break;
        }
        case 1 : {
            SnakeFamily *family = new SnakeFamily();
            e = family->createEntity(shapesFactory, pos);
            break;
        }
        case 2 : {
            AntFamily *family = new AntFamily();
            e = family->createEntity(shapesFactory, pos);
            break;
        }
        case 3 : {
            CaterpillarFamily *family = new CaterpillarFamily();
            e = family->createEntity(shapesFactory, pos);
            break;
        }
        }

        if(e){
            e->setup();
            entitiesEngine->addEntity(e);
            cvim->entitySelected(e);
            ents.append(e);
        }
    }
}

CreatureViewerWindow::~CreatureViewerWindow()
{
    simulationManager->stop();
    //delete ui;
}

void CreatureViewerWindow::showAbout()
{
    CreatureViewerAbout *cwa = new CreatureViewerAbout();
    cwa->show();
}

Entity * CreatureViewerWindow::createNewEntity()
{
    // get initial position
    OgreEngine *ogreEngine = static_cast<OgreEngine*>(factory->getEngines().find("Ogre").value());
    Ogre::Camera *camera = ogreEngine->getOgreSceneManager()->getCamera("firstCamera");
    Ogre::Vector3 initOgrePosition = camera->getPosition() + camera->getDirection() * 10;
    btVector3 initPosition(btScalar(initOgrePosition.x),btScalar(initOgrePosition.y),btScalar(initOgrePosition.z));

    // TODO choice of radius root
    Entity * e = GenericFamily::createVirginEntity(shapesFactory, btScalar(1.0), initPosition);
    e->setup();
    EntitiesEngine *entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngines().find("Entities").value());
    entitiesEngine->addEntity(e);
    ents.append(e);
    e->getShape()->getRoot()->fixeInTheAir();

    //entitySelected(e);
    //setEntity(e,e->getShape()->getRoot()->getRigidBody());
    QMessageBox::information(this, "Root fixation fixed in the air", "Default, the root fixation is fixed in the air.\n\nTo unfix it, select it and go to \"Tools\" tab of the fixation controller.");
    cvim->entitySelected(e);
    cvim->fixationSelected(e->getShape()->getRoot());
    return e;
}

void CreatureViewerWindow::addEntity(QVariantMap entityData,Ressource *ressource) {
    createCreature(entityData, getCameraPosition(), ressource);
}

//void CreatureViewerWindow::addResult(QVariantMap resultData, Ressource *ressource) {
//    Entity* e = createCreature(resultData, world->getSpawnPosition(), ressource);
//    e->addOutScript(0, fromNormal); // Normal position during stability time
//    e->addOutScript(resultData["stable"].toInt(), fromBrain); // Next from brain
//    e->setAge(0);
//}

void CreatureViewerWindow::loadEntityFromFile()
{
    simulationManager->stop();
    const QString DEFAULT_DIR_KEY("default_dir");
    QSettings mySettings;
    QString selectedFile = QFileDialog::getOpenFileName(this, "Select a genome", mySettings.value(DEFAULT_DIR_KEY).toString(),"Genome (*.genome)");

    if (!selectedFile.isEmpty()) {
        QDir CurrentDir;
        mySettings.setValue(DEFAULT_DIR_KEY, CurrentDir.absoluteFilePath(selectedFile));

        // Load Generic Entity
        Ressource* from = new JsonFile(selectedFile);
        QVariant genotype = from->load();

        Entity *e = createCreature(genotype, getCameraPosition(),from);

        if(e != NULL)
            e->setRessource(from);
    }

    simulationManager->start();
}

Entity * CreatureViewerWindow::createCreature(QVariant genotype, btVector3 position, Ressource *ressource) {

    Entity *e = CreatureFactory::createEntity(genotype, shapesFactory, position);

    if(e == NULL) {
        QMessageBox::warning(this, "Impossible to create entity",
"Entity could not be created, maybe version of genotype don't match. Please update your client.");
        return NULL;
    }

    if(ressource)
        e->setRessource(ressource);

    e->setup();
    EntitiesEngine *entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngines().find("Entities").value());
    entitiesEngine->addEntity(e);
    cvim->entitySelected(e);
    return e;
}

btVector3 CreatureViewerWindow::getCameraPosition() {

    // get initial position
    OgreEngine *ogreEngine = static_cast<OgreEngine*>(factory->getEngines().find("Ogre").value());
    Ogre::Camera *camera = ogreEngine->getOgreSceneManager()->getCamera("firstCamera");
    Ogre::Vector3 initOgrePosition = camera->getPosition() + camera->getDirection() * 10;
    btVector3 initPosition(btScalar(initOgrePosition.x),btScalar(initOgrePosition.y),btScalar(initOgrePosition.z));
    return initPosition;
}


void CreatureViewerWindow::saveEntityToFile()
{
    simulationManager->stop();
    if(selectedEntity != NULL)
    {
        // Short circuit if already save / load from something
        if(selectedEntity->getRessource()) {
            selectedEntity->getRessource()->save(selectedEntity->serialize());
            simulationManager->start();
            return;
        }

        QString selectedFile = QFileDialog::getSaveFileName(this, "Save your genome", "./ressources/" + selectedEntity->getName() + ".genome" ,"Genome (*.genome)");

        if (selectedFile.isEmpty())
            return;

        // Load Generic Entity
        Ressource* to = new JsonFile(selectedFile);
        to->save(selectedEntity->serialize());
        selectedEntity->setRessource(to);

    }
    else
        QMessageBox::warning(this, "No entity selected.", "No entity selected.");

    simulationManager->start();
}

void CreatureViewerWindow::togglePhysics()
{
    if(this->simulationManager->toggle())
        aTogglePhysics->setIcon(QIcon(":img/icons/bullet_physics_library_stop"));
    else
        aTogglePhysics->setIcon(QIcon(":img/icons/bullet_physics_library_play"));
}

void CreatureViewerWindow::removeEntity()
{
    if(selectedEntity != NULL)
    {
        EntitiesEngine *entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngines().find("Entities").value());
        entitiesEngine->removeEntity(selectedEntity);

        unfollowEntity();
        emit sEntityDeleted(selectedEntity);

        delete selectedEntity;

        selectedEntity = NULL;
        selectedBone = NULL;
        selectedFix = NULL;
    }
    else
        QMessageBox::warning(this, "No entity selected.", "No entity selected.");
}

void CreatureViewerWindow::removeAllEntities()
{
    selectedEntity = NULL;
    selectedBone = NULL;
    selectedFix= NULL;

    unfollowEntity();

    // Clear entities
    EntitiesEngine *entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngineByName("Entities"));

    foreach(Entity * entity, entitiesEngine->getAllEntities())
        emit sEntityDeleted(entity);

    entitiesEngine->removeAndDeleteAllEntities();
}

void CreatureViewerWindow::removeAllEntitiesExceptSelected() {

    if(selectedEntity != NULL) {

        // Clear entities except that selected entity
        EntitiesEngine *entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngines().find("Entities").value());
        ents = entitiesEngine->getAllEntities();
        while(ents.size() != 0){

            Entity * old = ents.takeFirst();

            if(old != selectedEntity) {
                entitiesEngine->removeEntity(old);
                emit sEntityDeleted(old);
                delete old;
            }
        }
    }
}

void CreatureViewerWindow::enterInWhatsThisMode(){
    QWhatsThis::enterWhatsThisMode();
}

void CreatureViewerWindow::entitySelected(Entity *entity)
{
      selectedEntity = entity;
}

void CreatureViewerWindow::boneDeleted(Bone* bone){
    if(selectedBone == bone) {
        selectedBone = NULL;
        selectedFix = NULL;
    }
}

void CreatureViewerWindow::entityDeleted(Entity* entity) {

   if(selectedEntity == entity)
       selectedEntity = NULL;
}

void CreatureViewerWindow::fixationDeleted(Fixation* fix){
    if(selectedFix == fix)
        selectedFix = NULL;
}

void CreatureViewerWindow::boneSelected(Bone* bone){

    // unselect old
    if(selectedBone)
        selectedBone->setSelected(false);
    if(selectedFix)
       selectedFix->setSelected(false);

    if(bone) {
        bone->setSelected(true);
        bone->getEndFixation()->setSelected(true);

        selectedBone = bone;
        selectedFix  = bone->getEndFixation();
    }
}

void CreatureViewerWindow::fixationSelected(Fixation* fix){

    // unselect old
    if(selectedFix)
        selectedFix->setSelected(false);
    if(selectedBone)
        selectedBone->setSelected(false);

    if(fix)
        fix->setSelected(true);

    selectedFix = fix;
    selectedBone = NULL;
}

void CreatureViewerWindow::followSelectedEntity() {

    if(selectedEntity) {

        OgreEngine * ogre = (OgreEngine *) factory->getEngineByName("Ogre");
        OgreWidget *ogreWidget = ogre->getOgreWidget("MainWidget");
        OgreFreeCamera * cam = ogreWidget->getOgreFreeCamera();

        cam->followBody(selectedEntity->getShape()->getRoot()->getRigidBody());
        ogreWidget->setFocus(Qt::MouseFocusReason);
        aFollowCreature->setChecked(true);
    }
}

void CreatureViewerWindow::unfollowEntity() {

    // TODO save widget !!!
    OgreEngine * ogre = (OgreEngine *) factory->getEngineByName("Ogre");
    OgreWidget *ogreWidget = ogre->getOgreWidget("MainWidget");
    OgreFreeCamera * cam = ogreWidget->getOgreFreeCamera();
    cam->unfollowBody();
    aFollowCreature->setChecked(false);

}

void CreatureViewerWindow::hideAllDocks(){
    ui->dwWelcome->setVisible(false);
    ui->dwBone->setVisible(false);
    ui->dwBrain->setVisible(false);
    ui->dwFixation->setVisible(false);
    ui->dwCreature->setVisible(false);
    ui->dwExperiment->setVisible(false);
    ui->dwWorker->setVisible(false);
    ui->dwRessourcesBrowser->setVisible(false);
    ui->dwStats->setVisible(false);

    aWelcomeMode->setChecked(false);
    aDesignerMode->setChecked(false);
    aExperimentMode->setChecked(false);
    aTheaterMode->setChecked(false);
}

void CreatureViewerWindow::switchToWelcomeMode() {

    hideAllDocks();

    aWelcomeMode->setChecked(true);

    ui->dwWelcome->setVisible(true);
}

void CreatureViewerWindow::switchToDesignerMode() {

    hideAllDocks();

    aDesignerMode->setChecked(true);

    ui->dwBone->setVisible(true);
    ui->dwBrain->setVisible(true);
    ui->dwFixation->setVisible(true);
    ui->dwCreature->setVisible(true);
}

void CreatureViewerWindow::switchToExperimentMode() {

    hideAllDocks();

    aExperimentMode->setChecked(true);

    ui->dwExperiment->setVisible(true);
    ui->dwWorker->setVisible(true);
    ui->dwRessourcesBrowser->setVisible(true);
}

void CreatureViewerWindow::switchToTheaterMode() {

    hideAllDocks();

    aTheaterMode->setChecked(true);
}

void CreatureViewerWindow::toggleShadows() {

    // TODO save widget !!!
    OgreEngine * ogre = (OgreEngine *) factory->getEngineByName("Ogre");

    if(ogre->getOgreSceneManager()->getShadowTechnique() == Ogre::SHADOWTYPE_NONE) {
        ogre->getOgreSceneManager()->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
        aShowShadows->setChecked(true);
    }
    else {
        ogre->getOgreSceneManager()->setShadowTechnique(Ogre::SHADOWTYPE_NONE);
        aShowShadows->setChecked(false);
    }
}
