#include "creatureviewerwindow.h"
#include "ui_creatureviewerwindow.h"

#include "world/btworld.h"

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

// Listeners
#include "creatureviewerinputmanager.h"

// Ressources
#include "ressources/ressource.h"
#include "ressources/jsonfile.h"
#include "ressources/dbrecord.h"

#include "families/spiderfamily.h"
#include "families/snakefamily.h"
#include "families/antfamily.h"
#include "families/caterpillarfamily.h"

#include "tools.h"
#include "world/btoworld.h"
#include "world/btobiome.h"
#include "world/btoscene.h"

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
#include "world/btworld.h"

using namespace GeneLabCore;

CreatureViewerWindow::CreatureViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreatureViewer), selectedEntity(NULL), selectedBone(NULL), selectedFix(NULL), epc(NULL)
{
    ui->setupUi(this);
    init();
}

void CreatureViewerWindow::init() {

    factory = new btoFactory(this->ui->centralwidget, (unsigned long) this->winId() );
    creatureFactory = new CreatureFactory();
    worldFactory    = new btoWorldFactory();
    experiment      = new Experiment();

    // ----------
    // -- Menu --
    // ----------
    connect(this->ui->actionFrom_file,SIGNAL(triggered()),this,SLOT(loadEntityFromFile()));
    connect(this->ui->actionTo_file,SIGNAL(triggered()),this,SLOT(saveEntityToFile()));
    connect(this->ui->actionFrom_database, SIGNAL(triggered()), this, SLOT(loadEntityFromDb()));
    connect(this->ui->actionDatabase, SIGNAL(triggered()), this, SLOT(saveEntityToDb()));
    connect(this->ui->actionNew_creature,SIGNAL(triggered()),this,SLOT(createNewEntity()));
    connect(this->ui->actionRemove_creature,SIGNAL(triggered()),this,SLOT(removeEntity()));
    connect(this->ui->actionAbout_CreatureViewer,SIGNAL(triggered()),this,SLOT(showAbout()));
    connect(this->ui->aEnterInWhatsThisMode,SIGNAL(triggered()),this,SLOT(enterInWhatsThisMode()));

    // --------------
    // -- Tool bar --
    // --------------

    // create actions & add to bar
    QAction *aNewCreature = ui->toolBar->addAction(QIcon(":img/icons/entity_new"),QString(tr("New creature")));
    QAction *aAddCreature = ui->toolBar->addAction(QIcon(":img/icons/entity_add"),QString(tr("Add creature")));
    QAction *aAddCreatureFromBdd = ui->toolBar->addAction(QIcon(":img/icons/entity_add_from_bdd"),QString(tr("Add creature from database")));
    QAction *aAddRandomCreature =  ui->toolBar->addAction(QIcon(":img/icons/entity_add_random"),QString(tr("Add random creature")));
    ui->toolBar->addSeparator();
    QAction *aSaveCreature = ui->toolBar->addAction(QIcon(":img/icons/entity_save"),QString(tr("Save creature")));
    ui->toolBar->addSeparator();
    QAction *aRemoveCreature =  ui->toolBar->addAction(QIcon(":img/icons/entity_delete"),QString(tr("Remove creature")));
    QAction *aRemoveAllCreatures =  ui->toolBar->addAction(QIcon(":img/icons/entity_delete_all"),QString(tr("Remove all creatures")));
    QAction *aRemoveAllCreaturesExceptSelected = ui->toolBar->addAction(QIcon(":img/icons/entity_delete_all_except_one"),QString(tr("Remove all creatures except that selected")));


    ui->toolBar->addSeparator();
    QAction *aCreateMutationSample =  ui->toolBar->addAction(QIcon(":img/icons/entity_mutation"),QString(tr("Create mutation sample")));
    QAction *aEditExperiment =  ui->toolBar->addAction(QIcon(":img/icons/report"),QString(tr("Edit current experiment")));
    ui->toolBar->addSeparator();

    QAction *aFollowCreature = ui->toolBar->addAction(QIcon(":img/icons/entity_follow"),QString(tr("Follow selected creature")));



    // step manager
    //ui->toolBar->addWidget(new QLabel(tr("Step manager :"));
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
    connect(aAddCreatureFromBdd,SIGNAL(triggered()),this,SLOT(loadEntityFromDb()));
    connect(aAddRandomCreature,SIGNAL(triggered()),this,SLOT(addRandomEntity()));
    connect(aSaveCreature,SIGNAL(triggered()),this,SLOT(saveEntityToFile()));
    connect(aRemoveCreature,SIGNAL(triggered()),this,SLOT(removeEntity()));
    connect(aRemoveAllCreatures,SIGNAL(triggered()),this,SLOT(removeAllEntities()));
    connect(aRemoveAllCreaturesExceptSelected,SIGNAL(triggered()),this,SLOT(removeAllEntitiesExceptSelected()));

    connect(aFollowCreature,SIGNAL(triggered()),this,SLOT(followSelectedEntity()));

    connect(aCreateMutationSample,SIGNAL(triggered()),this,SLOT(createMutationSample()));
    connect(aEditExperiment,SIGNAL(triggered()),this,SLOT(openExperimentPropertiesController()));



    // -----------
    // -- Docks --
    // -----------

    tabifyDockWidget(ui->dwCreature,ui->dwBone);
    tabifyDockWidget(ui->dwCreature,ui->dwFixation);
    tabifyDockWidget(ui->dwCreature,ui->dwBrain);
    setTabPosition(Qt::LeftDockWidgetArea,QTabWidget::North);
    //setTabShape(QTabWidget::Triangular);

    // get the QTabBar
    QList<QTabBar *> tabList = findChildren<QTabBar *>();
    if(!tabList.isEmpty()){
        QTabBar *tabBar = tabList.at(0);
        tabBar->setCurrentIndex(0);
    }


    // ----------------------
    // -- Events Listeners --
    // ----------------------
    BulletOgreEngine *btoEngine = static_cast<BulletOgreEngine*>(factory->getEngines().find("BulletOgre").value());
    OgreEngine *ogreEngine = static_cast<OgreEngine*>(factory->getEngines().find("Ogre").value());

    CreatureViewerInputManager *cvim = new CreatureViewerInputManager(btoEngine,ogreEngine->getOgreSceneManager()->getCamera("firstCamera"));
    EntitiesEngine* ee = static_cast<EntitiesEngine*>(factory->getEngines().find("Entities").value());
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

    // Entity
    entityPropertiesController = new EntityPropertiesController();
    ui->dwCreature->setWidget(entityPropertiesController);
    entityPropertiesController->connectToInspectorInputManager(cvim);

    // Brain
    brainPropertiesController = new BrainPropertiesController();
    PlugGridVisualizer* bViz = new PlugGridVisualizer();
    PlugGridDesignVisualizer* bDezViz = new PlugGridDesignVisualizer();
    ee->addPlugGridDezVisualizer(bDezViz);
    ee->addPlugGridVisualizer(bViz);
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


    qDebug() << "Start simulation";
    simulationManager->start();

    connect(sPhysicStep,SIGNAL(valueChanged(int)),this->simulationManager,SLOT(setPhysicsFreq(int)));
    connect(aTogglePhysics,SIGNAL(triggered()),this,SLOT(togglePhysics()));

    qDebug() << "[OK]\n";


    shapesFactory = new btoShapesFactory(btoEngine);
    world = worldFactory->createWorld(factory, shapesFactory, worldFactory->createSimpleWorld());
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

}

void CreatureViewerWindow::openExperimentPropertiesController(){

    if(epc == NULL) {
        epc = new ExperimentsPropertiesController(experiment);
        connect(epc, SIGNAL(experimentLoaded(GeneLabCore::Experiment*)), this, SLOT(setExperiment(GeneLabCore::Experiment*)));
    }

    epc->show();
}

void CreatureViewerWindow::setExperiment(Experiment* experiment)
{
    this->experiment = experiment;

    // TODO reload world...
}

void CreatureViewerWindow::loadEntityFromDb() {
    QString id = QInputDialog::getText(this, "Loading from database genecraft-project", "Please, enter the creature id");
    Ressource* r = new DbRecord(this->base, id);
    QVariant genotype = r->load();

    QVariantMap data = genotype.toMap();
    if(data.contains("error")) {

        QMessageBox msg;
        msg.setDetailedText(data["error"].toString());
        msg.setText("this creature didn't exist in the database, please check your internet connexion and the creature id.");
        msg.setIcon(QMessageBox::Critical);
        msg.setWindowTitle("Loading from database genecraft-project");
        msg.exec();
        return;
    }

    // get initial position
    OgreEngine *ogreEngine = static_cast<OgreEngine*>(factory->getEngines().find("Ogre").value());
    Ogre::Camera *camera = ogreEngine->getOgreSceneManager()->getCamera("firstCamera");
    Ogre::Vector3 initOgrePosition = camera->getPosition() + camera->getDirection() * 10;
    btVector3 initPosition(btScalar(initOgrePosition.x),btScalar(initOgrePosition.y),btScalar(initOgrePosition.z));

    Entity *e = creatureFactory->createEntity(genotype, shapesFactory, initPosition);

    if(e == NULL) {
        QMessageBox::warning(this, "Impossible to load entity",
"Entity could not be created, maybe version of genotype don't match. Please update your client.");
        return;
    }

    e->setup();
    e->setRessource(r);
    EntitiesEngine *entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngines().find("Entities").value());
    entitiesEngine->addEntity(e);
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

    EntitiesEngine *entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngineByName("Entities"));

    // Clear entities
    /*while(ents.size() != 0){
        Entity * old = ents.takeFirst();
        entitiesEngine->removeEntity(old);
        delete old;
    }*/

    // RANDOM ENTITIES
    spawnRandomEntities(1);
    Entity* e = entitiesEngine->getAllEntities().first();
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
    float r = 3 * nbCreatures;
    float angle = 2 * M_PI / nbCreatures;

    // mutations
    for(int i = 0; i < nbCreatures; i++) {

        QVariant newGenome = experiment->getMutationsManager()->mutateEntity(originGenome);

        btVector3 pos(sin(i*angle)*r,5,cos(i*angle)*r); //pos(0, 0, i*15 + 15);//

        e = creatureFactory->createEntity(newGenome, shapesFactory, pos + originPos);
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
            ents.append(e);
        }
    }
}

CreatureViewerWindow::~CreatureViewerWindow()
{
    simulationManager->stop();
    // Cheat anti double free
    ui->dwCreature->setWidget(new QWidget());
    delete ui;
}

void CreatureViewerWindow::showAbout()
{
    CreatureViewerAbout *cwa = new CreatureViewerAbout();
    cwa->show();
}

void CreatureViewerWindow::createNewEntity()
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
}

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

        // get initial position
        OgreEngine *ogreEngine = static_cast<OgreEngine*>(factory->getEngines().find("Ogre").value());
        Ogre::Camera *camera = ogreEngine->getOgreSceneManager()->getCamera("firstCamera");
        Ogre::Vector3 initOgrePosition = camera->getPosition() + camera->getDirection() * 10;
        btVector3 initPosition(btScalar(initOgrePosition.x),btScalar(initOgrePosition.y),btScalar(initOgrePosition.z));

        Entity *e = creatureFactory->createEntity(genotype, shapesFactory, initPosition);

        if(e == NULL) {
            QMessageBox::warning(this, "Impossible to load entity",
"Entity could not be created, maybe version of genotype don't match. Please update your client.");
            return;
        }

        e->setup();
        e->setRessource(from);
        EntitiesEngine *entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngines().find("Entities").value());
        entitiesEngine->addEntity(e);

    }

    simulationManager->start();
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
        const QString DEFAULT_DIR_KEY("default_dir");
        QSettings mySettings;
        QString selectedFile = QFileDialog::getSaveFileName(this, "Save your genome", mySettings.value(DEFAULT_DIR_KEY).toString(),"Genome (*.genome)");

        if (!selectedFile.isEmpty()) {
            QDir CurrentDir;
            mySettings.setValue(DEFAULT_DIR_KEY, CurrentDir.absoluteFilePath(selectedFile));

            // Load Generic Entity
            Ressource* to = new JsonFile(selectedFile);
            to->save(selectedEntity->serialize());
            selectedEntity->setRessource(to);
        }
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
    EntitiesEngine *entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngines().find("Entities").value());
    ents = entitiesEngine->getAllEntities();
    while(ents.size() != 0){

        Entity * old = ents.takeFirst();
        entitiesEngine->removeEntity(old);
        emit sEntityDeleted(old);

        delete old;
    }
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

    if(bone)
        bone->setSelected(true);

    selectedBone = bone;
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
}

void CreatureViewerWindow::followSelectedEntity() {

    qDebug() << Q_FUNC_INFO;

    if(selectedEntity) {

        OgreEngine * ogre = (OgreEngine *) factory->getEngineByName("Ogre");
        OgreWidget *ogreWidget = ogre->getOgreWidget("MainWidget");
        OgreFreeCamera * cam = ogreWidget->getOgreFreeCamera();

        cam->followBody(selectedEntity->getShape()->getRoot()->getRigidBody());
        ogreWidget->setFocus(Qt::MouseFocusReason);
    }
}

void CreatureViewerWindow::unfollowEntity() {

    // TODO save widget !!!
    OgreEngine * ogre = (OgreEngine *) factory->getEngineByName("Ogre");
    OgreWidget *ogreWidget = ogre->getOgreWidget("MainWidget");
    OgreFreeCamera * cam = ogreWidget->getOgreFreeCamera();
    cam->unfollowBody();

}


