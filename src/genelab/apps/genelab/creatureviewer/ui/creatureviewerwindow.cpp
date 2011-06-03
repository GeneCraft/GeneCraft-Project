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
    ui(new Ui::CreatureViewer), selectedEntity(NULL), inspector(NULL), openGLWidget(NULL)
{
    ui->setupUi(this);

    factory = new MainFactory(this->ui->centralwidget, (unsigned long) this->winId() );

    // ----------
    // -- Menu --
    // ----------
    connect(this->ui->actionFrom_file,SIGNAL(triggered()),this,SLOT(loadEntityFromFile()));
    connect(this->ui->actionTo_file,SIGNAL(triggered()),this,SLOT(saveEntityToFile()));
    connect(this->ui->actionNew_creature,SIGNAL(triggered()),this,SLOT(createNewEntity()));

    connect(this->ui->actionAbout_CreatureViewer,SIGNAL(triggered()),this,SLOT(showAbout()));

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
    SimulationManager* simulationManager
            = new SimulationManager(factory->getEngines().values());

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
    selectedEntity = NULL;

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
                            //bone->setSelected(true); // TODO stock selection into rigidbody origin
                            setInspector(bone->getInspectorWidget());
                            selectedEntity = bone->getEntity();
                            setEntity(bone->getEntity(),bone->getRigidBody());
                            }
                            break;

                        case RigidBodyOrigin::FIXATION:{

                            Fixation *fix = dynamic_cast<Fixation*>(origin->getObject());
                            //fix->setSelected(true); // TODO stock selection into rigidbody origin
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

        //pickedBody = body;
        //pickedrigidBody->setActivationState(DISABLE_DEACTIVATION);
//                btVector3 pickPos = rayCallback.m_hitPointWorld;
//                qDebug() << "pickPos=" << pickPos.getX() << pickPos.getY() << pickPos.getZ();


//                btVector3 localPivot = rigidBody->getCenterOfMassTransform().inverse() * pickPos;

//                if (use6Dof)
//                {
//                    btTransform tr;
//                    tr.setIdentity();
//                    tr.setOrigin(localPivot);
//                    btGeneric6DofConstraint* dof6 = new btGeneric6DofConstraint(*body, tr,false);
//                    dof6->setLinearLowerLimit(btVector3(0,0,0));
//                    dof6->setLinearUpperLimit(btVector3(0,0,0));
//                    dof6->setAngularLowerLimit(btVector3(0,0,0));
//                    dof6->setAngularUpperLimit(btVector3(0,0,0));

//                    game->getBulletEngine()->getDynamicsWorld()->addConstraint(dof6);
//                    m_pickConstraint = dof6;

//                    dof6->setParam(BT_CONSTRAINT_STOP_CFM,0.8,0);
//                    dof6->setParam(BT_CONSTRAINT_STOP_CFM,0.8,1);
//                    dof6->setParam(BT_CONSTRAINT_STOP_CFM,0.8,2);
//                    dof6->setParam(BT_CONSTRAINT_STOP_CFM,0.8,3);
//                    dof6->setParam(BT_CONSTRAINT_STOP_CFM,0.8,4);
//                    dof6->setParam(BT_CONSTRAINT_STOP_CFM,0.8,5);

//                    dof6->setParam(BT_CONSTRAINT_STOP_ERP,0.1,0);
//                    dof6->setParam(BT_CONSTRAINT_STOP_ERP,0.1,1);
//                    dof6->setParam(BT_CONSTRAINT_STOP_ERP,0.1,2);
//                    dof6->setParam(BT_CONSTRAINT_STOP_ERP,0.1,3);
//                    dof6->setParam(BT_CONSTRAINT_STOP_ERP,0.1,4);
//                    dof6->setParam(BT_CONSTRAINT_STOP_ERP,0.1,5);
//                } else
//                {
//                    btPoint2PointConstraint* p2p = new btPoint2PointConstraint(*body,localPivot);
//                    game->getBulletEngine()->getDynamicsWorld()->addConstraint(p2p);
//                    m_pickConstraint = p2p;
//                    p2p->m_setting.m_impulseClamp = mousePickClamping;
//                    //very weak constraint for picking
//                    p2p->m_setting.m_tau = 0.001f;
//                    /*
//                                            p2p->setParam(BT_CONSTRAINT_CFM,0.8,0);
//                                            p2p->setParam(BT_CONSTRAINT_CFM,0.8,1);
//                                            p2p->setParam(BT_CONSTRAINT_CFM,0.8,2);
//                                            p2p->setParam(BT_CONSTRAINT_ERP,0.1,0);
//                                            p2p->setParam(BT_CONSTRAINT_ERP,0.1,1);
//                                            p2p->setParam(BT_CONSTRAINT_ERP,0.1,2);
//                                            */
//                }
//                use6Dof = !use6Dof;

//                //save mouse position for dragging
//                gOldPickingPos = rayTo;
//                gHitPos = pickPos;

//                gOldPickingDist  = (pickPos-rayFrom).length();
    }
}

void CreatureViewerWindow::showAbout()
{
    CreatureViewerAbout *cwa = new CreatureViewerAbout();
    cwa->show();
}

void CreatureViewerWindow::createNewEntity()
{
//    Entity * e = GenericFamily::createViginEntity(factory->getShapesFactory(), btScalar(1.0), btVector3(0,10,0));
//    e->setup();
//    EntitiesEngine *entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngines().find("Entities").value());
//    entitiesEngine->addEntity(e);
//    setEntity(e,e->getShape()->getRoot()->getRigidBody());
}

void CreatureViewerWindow::loadEntityFromFile()
{
    const QString DEFAULT_DIR_KEY("default_dir"); // TODO static
    QSettings mySettings;
    QString selectedFile = QFileDialog::getOpenFileName(this, "Select a genome", mySettings.value(DEFAULT_DIR_KEY).toString(),"Genome (*.genome)");

    if (!selectedFile.isEmpty()) {
        QDir CurrentDir;
        mySettings.setValue(DEFAULT_DIR_KEY, CurrentDir.absoluteFilePath(selectedFile));

        // Load Generic Entity
        Ressource* from = new JsonFile(selectedFile);
        QVariant genotype = from->load();
        Entity *e = GenericFamily::createEntity(genotype, factory->getShapesFactory(), btVector3(0,10,0));
        e->setup();
        EntitiesEngine *entitiesEngine = static_cast<EntitiesEngine*>(factory->getEngines().find("Entities").value());
        entitiesEngine->addEntity(e);

    }
}

void CreatureViewerWindow::saveEntityToFile()
{
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
}
