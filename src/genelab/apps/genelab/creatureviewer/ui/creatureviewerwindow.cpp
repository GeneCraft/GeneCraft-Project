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

// Widget
#include "widgets/entities/pluggridvisualizer.h"
#include "widgets/entities/pluggriddesignvisualizer.h"
#include "widgets/entities/fixationproperties.h"
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

#include <QThread>
#include <QInputDialog>
#include <QMessageBox>

#include "mutation/mutationsmanager.h"

using namespace GeneLabCore;

CreatureViewerWindow::CreatureViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreatureViewer), boneSelected(NULL), fixSelected(NULL), selectedEntity(NULL), inspector(NULL)
{
    ui->setupUi(this);
    this->init();
}

void CreatureViewerWindow::init() {

    factory = new btoFactory(this->ui->centralwidget, (unsigned long) this->winId() );

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
    QAction *aSaveCreature = ui->toolBar->addAction(QIcon(":img/icons/entity_save"),QString(tr("Save creature")));
    QAction *aRemoveCreature =  ui->toolBar->addAction(QIcon(":img/icons/entity_delete"),QString(tr("Remove creature")));
    ui->toolBar->addSeparator();

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
    connect(aSaveCreature,SIGNAL(triggered()),this,SLOT(saveEntityToFile()));
    connect(aRemoveCreature,SIGNAL(triggered()),this,SLOT(removeEntity()));

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


    ui->dwCreature->setWidget(Entity::getInspectorWidget());
    PlugGridVisualizer* bViz = new PlugGridVisualizer();
    PlugGridDesignVisualizer* bDezViz = new PlugGridDesignVisualizer();
    ee->addPlugGridDezVisualizer(bDezViz);
    ee->addPlugGridVisualizer(bViz);
    Entity::getInspectorWidget()->setBrainViz(bViz);
    Entity::getInspectorWidget()->setBrainDesignViz(bDezViz);

    // connect emitter of rigidBodySelected
    connect(cvim,SIGNAL(rigidBodySelected(btRigidBody*)),this,SLOT(rigidBodySelected(btRigidBody*)));
    connect(Fixation::getEmptyInspectorWidget(),SIGNAL(rigidBodySelected(btRigidBody*)),this,SLOT(rigidBodySelected(btRigidBody*)));
    connect(Bone::getEmptyInspectorWidget(),SIGNAL(rigidBodySelected(btRigidBody*)),this,SLOT(rigidBodySelected(btRigidBody*)));
    connect(Entity::getInspectorWidget(),SIGNAL(rigidBodySelected(btRigidBody*)),this,SLOT(rigidBodySelected(btRigidBody*)));

    connect(Fixation::getEmptyInspectorWidget(), SIGNAL(boneDeleted(Bone*)), this, SLOT(boneDeleted(Bone*)));
    connect(Bone::getEmptyInspectorWidget(), SIGNAL(boneDeleted(Bone*)), this, SLOT(boneDeleted(Bone*)));

    qDebug() << "Start simulation";
    simulationManager->start();

    connect(sPhysicStep,SIGNAL(valueChanged(int)),this->simulationManager,SLOT(setPhysicsFreq(int)));
    connect(aTogglePhysics,SIGNAL(triggered()),this,SLOT(togglePhysics()));

    qDebug() << "[OK]\n";


    // -----------
    // -- World --
    // -----------

    // World from program (soon from file)
    QVariantMap worldData;
    worldData.insert("name", "Earth");

    // Biome
    QVariantMap biomeData;
    biomeData.insert("gravity", (float)9.81);
    biomeData.insert("sky", "Examples/CloudySky");
    biomeData.insert("aR", (float)0.8);
    biomeData.insert("aG", (float)0.8);
    biomeData.insert("aB", (float)0.8);
    biomeData.insert("lR", (float)0.6);
    biomeData.insert("lG", (float)0.6);
    biomeData.insert("lB", (float)0.6);

    // Camera
    QVariantMap camData;
    camData.insert("cX", (float) -20);
    camData.insert("cY", (float) 10);
    camData.insert("cZ", (float) -20);
    camData.insert("lX", (float) 15);
    camData.insert("lY", (float) -5);
    camData.insert("lZ", (float) 15);

    // Spawn areas
    QVariantList spawns;
    QVariantMap zoneSpawn;
    QVariantMap positionSpawn;

    zoneSpawn.insert("type", (int)Spawn::Zone);
    zoneSpawn.insert("minX", (float)-60);
    zoneSpawn.insert("minY", (float)10);
    zoneSpawn.insert("minZ", (float)-60);
    zoneSpawn.insert("maxX", (float)60);
    zoneSpawn.insert("maxY", (float)30);
    zoneSpawn.insert("maxZ", (float)60);
    spawns.append(zoneSpawn);

    positionSpawn.insert("type", (int)Spawn::Position);
    positionSpawn.insert("x", -10);
    positionSpawn.insert("y", 15);
    positionSpawn.insert("z", -10);
    //spawns.append(positionSpawn);

    // Static boxes
    QVariantList staticBoxes;

    // MineCraft Floor
//    int sizeX = 10;
//    int sizeZ = 10;
//    for(int i=-10;i<10;++i){
//        for(int j=-10;j<10;++j){

//            double sizeY = Tools::random(0.1, 3.0);

//            QVariantMap staticBox;
//            staticBox.insert("posX",i*10);
//            staticBox.insert("posY",sizeY/2.0);
//            staticBox.insert("posZ",j*10);
//            staticBox.insert("eulerX",0);
//            staticBox.insert("eulerY",0);
//            staticBox.insert("eulerZ",0);
//            staticBox.insert("sizeX",sizeX);
//            staticBox.insert("sizeY",sizeY);
//            staticBox.insert("sizeZ",sizeZ);
//            staticBoxes.append(staticBox);
//        }
//    }

//    // Ruin Floor
//    for(int i=0;i<100;++i){

//        double sizeX = Tools::random(1.0, 10.0);
//        double sizeY = Tools::random(1.0, 10.0);
//        double sizeZ = Tools::random(1.0, 10.0);

//        double posX = Tools::random(-100, 100);
//        double posZ = Tools::random(-100, 100);

//        QVariantMap staticBox;
//        staticBox.insert("posX",posX);
//        staticBox.insert("posY",sizeY/2.0);
//        staticBox.insert("posZ",posZ);
//        staticBox.insert("eulerX",0);
//        staticBox.insert("eulerY",0);
//        staticBox.insert("eulerZ",0);
//        staticBox.insert("sizeX",sizeX);
//        staticBox.insert("sizeY",sizeY);
//        staticBox.insert("sizeZ",sizeZ);
//        staticBoxes.append(staticBox);
//    }


    // Scene
    QVariantMap sceneData;
    sceneData.insert("type", "flatland");
    sceneData.insert("cam", camData);
    sceneData.insert("spawns", spawns);
    sceneData.insert("staticBoxes", staticBoxes);
    sceneData.insert("floor", "Examples/GrassFloor");

    // Create the world
    shapesFactory = new btoShapesFactory(btoEngine);
    world = new btoWorld(factory, shapesFactory, worldData);
    shapesFactory->setWorld(world);

    btBiome* biome = new btoBiome(world, biomeData);
    world->setBiome(biome);

    btScene* scene = new btoScene(world, sceneData);
    world->setScene(scene);

    world->setup();
    cvim->setWorld(world);
/*
    btoWorld* world2 = new btoWorld(factory, worldData);
    btShapesFactory* shapesFactory2 = new btoShapesFactory(world2, btoEngine);

    btBiome* biome2 = new btoBiome(factory, biomeData);
    world2->setBiome(biome2);

    btScene* scene2 = new btoScene(factory, sceneData);
    world2->setScene(scene2);

    world2->setup();

*/

    // Spider
    qDebug() << "Spider creation !";

    qDebug() << time(NULL);
    srand(time(NULL));
    qsrand(time(NULL));
    int b = 0;
    for(int i = 0; i < 1000; i++) {
        int a = rand();
        b += a;
    }
    qDebug() << b;

    spawnNew();

    entitySpawner = new QTimer();
    entitySpawner->setInterval(5000);
    //entitySpawner->start();
    connect(entitySpawner, SIGNAL(timeout()), this, SLOT(spawnNew()));

    base.url = "http://www.genecraft-project.org";
    base.dbName = "db/genecraft";
    base.port = 80;

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

    Entity *e = GenericFamily::createEntity(genotype, shapesFactory, initPosition);
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

void CreatureViewerWindow::spawnNew() {

    EntitiesEngine *entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngineByName("Entities"));

    // Clear entities
    while(ents.size() != 0){
        Entity * old = ents.takeFirst();
        entitiesEngine->removeEntity(old);
        delete old;
    }

    // RANDOM ENTITIES
    spawnRandomEntities(1);
    Entity* e = ents.first();
    spawnMutationSample(e, 8);

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

    // Mutations tests
    MutationsManager *mm = new MutationsManager(QVariant());

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

        QVariant newGenome = mm->mutateEntity(originGenome);

        btVector3 pos(sin(i*angle)*r,0,cos(i*angle)*r); //pos(0, 0, i*15 + 15);//

        e = GenericFamily::createEntity(newGenome,shapesFactory,pos + originPos);

        if(e){
            e->setup();
            entitiesEngine->addEntity(e);
            ents.append(e);
            originGenome = e->serialize();
        } else {
            qDebug() << "NOT CREATED ANY ENTITY ... STRANGE !";
        }
    }
}

void CreatureViewerWindow::spawnRandomEntities(int nbEntities){

    Entity *e = NULL;
    EntitiesEngine *entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngines().find("Entities").value());

    for(int i = 0; i < nbEntities; i++) {

        int enttype = Tools::random(0,3);
        enttype = 3;

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

void CreatureViewerWindow::setInspector(QWidget * inspector)
{
    if(inspector != 0)
        ui->dwInspector->setWidget(inspector);
    else
        ui->dwCreature->setWidget(new QLabel("No element selected."));
}


void CreatureViewerWindow::setEntity(Entity *entity, btRigidBody *selectedBody)
{
    if(entity != NULL)
        ui->dwCreature->setWidget(Entity::getInspectorWidget(entity,selectedBody));
    else
        ui->dwCreature->setWidget(new QLabel("No creature selected."));
}

void CreatureViewerWindow::rigidBodySelected(btRigidBody *rigidBody)
{

    if(selectedEntity && boneSelected != NULL){
        boneSelected->setSelected(false);
        boneSelected = NULL;
    }

    if(selectedEntity && fixSelected != NULL) {
        fixSelected->setSelected(false);
        fixSelected = NULL;
    }


    // unselection
    selectedEntity = NULL;

    // you can also unselect by calling rigidBodySelected(NULL)
    if(rigidBody != NULL)
    {
        //other exclusions ?
        if (!(rigidBody->isStaticObject() || rigidBody->isKinematicObject()))
        {
            if(rigidBody->getUserPointer() != NULL)
            {
                RigidBodyOrigin* origin = static_cast<RigidBodyOrigin*>(rigidBody->getUserPointer());
                if(origin != 0)
                {
                    if(origin->getObject() != NULL)
                    {
                        switch(origin->getType())
                        {
                            case RigidBodyOrigin::BONE:{

                                Bone *bone = dynamic_cast<Bone*>(origin->getObject());
                                bone->setSelected(true); // TODO stock selection into rigidbody origin
                                boneSelected = bone;
                                setInspector(bone->getInspectorWidget());
                                selectedEntity = bone->getEntity();
                                setEntity(bone->getEntity(),bone->getRigidBody());
                                }
                                break;

                            case RigidBodyOrigin::FIXATION:{

                                Fixation *fix = dynamic_cast<Fixation*>(origin->getObject());
                                fix->setSelected(true); // TODO stock selection into rigidbody origin
                                fixSelected = fix;
                                setInspector(fix->getInspectorWidget());
                                selectedEntity = fix->getEntity();
                                setEntity(fix->getEntity(),fix->getRigidBody());
                                }
                                break;

                            case RigidBodyOrigin::BASIC_SHAPE:{

                                //BasicShape *shape = dynamic_cast<BasicShape*>(reinterpret_cast<QObject*>(origin->getObject()));
                                //game->getOpenGLEngine()->getScene()->removeDrawableObject(shape);
                                //game->getBulletEngine()->getDynamicsWorld()->removeRigidBody(shape->getRigidBody());
                                setInspector(new QLabel("BASIC_SHAPE"));

                                }
                                break;

                            default:
                                setInspector(0);
                        }
                    }
                    else
                        qDebug() << "CreatureViewer::rigidBodySelected : object NULL";
                }
                else
                    qDebug() << "CreatureViewer::rigidBodySelected : RigidBodyOrigin NULL";
            }
        }
    }
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
    Entity * e = GenericFamily::createViginEntity(shapesFactory, btScalar(1.0), initPosition);
    e->setup();
    EntitiesEngine *entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngines().find("Entities").value());
    entitiesEngine->addEntity(e);
    e->getShape()->getRoot()->fixeInTheAir();
    setEntity(e,e->getShape()->getRoot()->getRigidBody());

    QMessageBox::information(this, "Root fixation fixed in the air", "By default, the root fixation is fixed in the air.\n\nTo unfix it, select it and go to \"Tools\" tab.");
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

        Entity *e = GenericFamily::createEntity(genotype, shapesFactory, initPosition);
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
        this->setEntity(NULL, NULL);
        delete selectedEntity;
        selectedEntity = NULL;
        boneSelected = NULL;
        fixSelected = NULL;
    }
    else
        QMessageBox::warning(this, "No entity selected.", "No entity selected.");
}

void CreatureViewerWindow::enterInWhatsThisMode(){
    QWhatsThis::enterWhatsThisMode();
}


void CreatureViewerWindow::entityDeleted(Entity*) {
    this->setEntity(NULL, NULL);
}

void CreatureViewerWindow::boneDeleted(Bone* bone) {
    this->setEntity(bone->getEntity(), NULL);
}

void CreatureViewerWindow::fixationDeleted(Fixation* fix) {
    this->setEntity(fix->getEntity(), NULL);
}
