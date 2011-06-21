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
#include "OGRE/Ogre.h"
#include "ogre/ogreengine.h"
#include "mainfactory.h"
#include "simulationmanager.h"
#include "events/eventmanager.h"
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

#include "families/spider/spider.h"


#include "world/btoworld.h"
#include "btoshapesfactory.h"

#include <QThread>

using namespace GeneLabCore;

CreatureViewerWindow::CreatureViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreatureViewer), boneSelected(NULL), fixSelected(NULL), selectedEntity(NULL), inspector(NULL)
{
    ui->setupUi(this);
    this->init();
}

void CreatureViewerWindow::init() {

    factory = new MainFactory(this->ui->centralwidget, (unsigned long) this->winId() );

    // ----------
    // -- Menu --
    // ----------
    connect(this->ui->actionFrom_file,SIGNAL(triggered()),this,SLOT(loadEntityFromFile()));
    connect(this->ui->actionTo_file,SIGNAL(triggered()),this,SLOT(saveEntityToFile()));
    connect(this->ui->actionNew_creature,SIGNAL(triggered()),this,SLOT(createNewEntity()));
    connect(this->ui->actionRemove_creature,SIGNAL(triggered()),this,SLOT(removeEntity()));
    connect(this->ui->actionAbout_CreatureViewer,SIGNAL(triggered()),this,SLOT(showAbout()));


    // --------------
    // -- Tool bar --
    // --------------

    // create actions & add to bar
    QAction *aNewCreature = ui->toolBar->addAction(QIcon(":img/icons/entity_new"),QString("New creature"));
    QAction *aAddCreature = ui->toolBar->addAction(QIcon(":img/icons/entity_add"),QString("Add creature"));
    QAction *aSaveCreature = ui->toolBar->addAction(QIcon(":img/icons/entity_save"),QString("Save creature"));
    QAction *aRemoveCreature =  ui->toolBar->addAction(QIcon(":img/icons/entity_delete"),QString("Remove creature"));
    ui->toolBar->addSeparator();
    aTogglePhysics = ui->toolBar->addAction(QIcon(":img/icons/bullet_physics_library_play"),QString("Toggle physics"));

    // connections
    connect(aNewCreature,SIGNAL(triggered()),this,SLOT(createNewEntity()));
    connect(aAddCreature,SIGNAL(triggered()),this,SLOT(loadEntityFromFile()));
    connect(aSaveCreature,SIGNAL(triggered()),this,SLOT(saveEntityToFile()));
    connect(aRemoveCreature,SIGNAL(triggered()),this,SLOT(removeEntity()));
    connect(aTogglePhysics,SIGNAL(triggered()),this,SLOT(togglePhysics()));


    // ----------------------
    // -- Events Listeners --
    // ----------------------
    BulletOgreEngine *btoEngine = static_cast<BulletOgreEngine*>(factory->getEngines().find("BulletOgre").value());
    OgreEngine *ogreEngine = static_cast<OgreEngine*>(factory->getEngines().find("Ogre").value());

    CreatureViewerInputManager *cvim = new CreatureViewerInputManager(btoEngine,ogreEngine->getOgreSceneManager()->getCamera("firstCamera"));
    EntitiesEngine* ee = static_cast<EntitiesEngine*>(factory->getEngines().find("Entities").value());
    // add listener in events manager
    EventManager *eventsManager =  static_cast<EventManager*>(factory->getEngines().find("Event").value());
    eventsManager->addListener(cvim);



    // ------------------------
    // -- Simulation Manager --
    // ------------------------
    qDebug() << "Init Simulation Manager";
    simulationManager = new SimulationManager(factory->getEngines());

    simulationManager->setup();
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

    qDebug() << "Start simulation";
    simulationManager->start();
    qDebug() << "[OK]\n";


    // Création du monde
    btoWorld* world = new btoWorld(factory);
    world->setup();
    cvim->setWorld(world);
    shapesFactory = new btoShapesFactory(world, btoEngine);


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
    Entity* e;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            Spider *spider = new Spider();
            e = spider->createEntity(shapesFactory, btVector3(j*30,7,i*30));
            qDebug() << "spider setup !";
            e->setup();
            ee->addEntity(e);
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
    // unselection
    selectedEntity = NULL;

    if(boneSelected != NULL){
        boneSelected->setSelected(false);
        boneSelected = NULL;
    }

    if(fixSelected != NULL) {
        fixSelected->setSelected(false);
        fixSelected = NULL;
    }

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
        const QString DEFAULT_DIR_KEY("default_dir");
        QSettings mySettings;
        QString selectedFile = QFileDialog::getSaveFileName(this, "Save your genome", mySettings.value(DEFAULT_DIR_KEY).toString(),"Genome (*.genome)");

        if (!selectedFile.isEmpty()) {
            QDir CurrentDir;
            mySettings.setValue(DEFAULT_DIR_KEY, CurrentDir.absoluteFilePath(selectedFile));

            // Load Generic Entity
            Ressource* to = new JsonFile(selectedFile);
            to->save(selectedEntity->serialize());
        }
    }
    else
        QMessageBox::warning(this, "No entity selected.", "No entity selected.");
    simulationManager->start();
}

void CreatureViewerWindow::togglePhysics()
{
    BulletOgreEngine *btoEngine = static_cast<BulletOgreEngine*>(factory->getEngines().find("BulletOgre").value());
    btoEngine->getBulletEngine()->setPhysicsEnable(!btoEngine->getBulletEngine()->getPhysicsEnable());

    if(btoEngine->getBulletEngine()->getPhysicsEnable())
        aTogglePhysics->setIcon(QIcon(":img/icons/bullet_physics_library_stop"));
    else
        aTogglePhysics->setIcon(QIcon(":img/icons/bullet_physics_library_play"));
}

void CreatureViewerWindow::removeEntity()
{
    if(selectedEntity != NULL)
    {
        //EntitiesEngine *entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngines().find("Entities").value());
        //entitiesEngine->removeEntity(e);

        delete selectedEntity;
        selectedEntity = NULL;
    }
    else
        QMessageBox::warning(this, "No entity selected.", "No entity selected.");
}
