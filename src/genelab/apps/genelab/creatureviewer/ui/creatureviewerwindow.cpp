#include "creatureviewerwindow.h"
#include "ui_creatureviewerwindow.h"

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
#include "fixation.h"
#include "bone.h"
#include "entity.h"
#include "rigidbodyorigin.h"
#include "fixationproperties.h"
#include "bonepropertiescontroller.h"
#include "entitypropertiescontroller.h"
#include "genericfamily.h"
#include "treeshape.h"

// Engine
#include "bulletengine.h"
#include "OGRE/Ogre.h"
#include "ogreengine.h"
#include "mainfactory.h"
#include "simulationmanager.h"
#include "eventmanager.h"
#include "bulletogreengine.h"
#include "entitiesengine.h"
#include "brainengine.h"
#include "pluggridvisualizer.h"

// Listeners
#include "creatureviewerinputmanager.h"

// Ressources
#include "ressources/ressource.h"
#include "ressources/jsonfile.h"


using namespace GeneLabCore;

CreatureViewerWindow::CreatureViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreatureViewer), selectedEntity(NULL), inspector(NULL), openGLWidget(NULL), boneSelected(NULL), fixSelected(NULL)
{
    ui->setupUi(this);

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

    // add listener in events manager
    EventManager *eventsManager =  static_cast<EventManager*>(factory->getEngines().find("Event").value());
    eventsManager->addListener(cvim);

    // connect listener to window
    connect(cvim,SIGNAL(rigidBodySelected(btRigidBody*)),this,SLOT(rigidBodySelected(btRigidBody*)));

    // ------------------------
    // -- Simulation Manager --
    // ------------------------
    qDebug() << "Init Simulation Manager";
    simulationManager = new SimulationManager(factory->getEngines());

    simulationManager->setup();
    qDebug() << "[OK]\n";


    ui->dwCreature->setWidget(Entity::getInspectorWidget());
    BrainEngine* bEngine = (BrainEngine*)(factory->getEngines().find("Brain").value());
    PlugGridVisualizer* bViz = (PlugGridVisualizer*)bEngine->getRenderWidget(Entity::getInspectorWidget());
    Entity::getInspectorWidget()->setBrainViz(bViz);
    // Connection to Inspectors
    connect(Entity::getInspectorWidget(),SIGNAL(rigidBodySelected(btRigidBody*)),this,SLOT(rigidBodySelected(btRigidBody*)));

    qDebug() << "Start simulation";
    simulationManager->start();
    qDebug() << "[OK]\n";

}

CreatureViewerWindow::~CreatureViewerWindow()
{
    delete ui;
}

void CreatureViewerWindow::setInspector(QWidget * inspector)
{
    if(inspector != 0)
        ui->dwInspector->setWidget(inspector);
    else
        ui->dwCreature->setWidget(new QLabel("No element selected.")); // TODO NOT new !!!
}

void CreatureViewerWindow::setOpenGLWidget(QWidget * openGLWidget)
{
    setCentralWidget(openGLWidget);
}

void CreatureViewerWindow::setEntity(Entity *entity, btRigidBody *selectedBody)
{
    if(entity != NULL)
        ui->dwCreature->setWidget(Entity::getInspectorWidget(entity,selectedBody));
    else
        ui->dwCreature->setWidget(new QLabel("No creature selected.")); // TODO NOT new !!!
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
    Entity * e = GenericFamily::createViginEntity(factory->getShapesFactory(), btScalar(1.0), initPosition);
    e->setup();
    EntitiesEngine *entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngines().find("Entities").value());
    entitiesEngine->addEntity(e);
    setEntity(e,e->getShape()->getRoot()->getRigidBody());
}

void CreatureViewerWindow::loadEntityFromFile()
{
    simulationManager->stop();
    const QString DEFAULT_DIR_KEY("default_dir"); // TODO static
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

        Entity *e = GenericFamily::createEntity(genotype, factory->getShapesFactory(), initPosition);
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
        const QString DEFAULT_DIR_KEY("default_dir");  // TODO static
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
