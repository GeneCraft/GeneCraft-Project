// Qt
#include <QDebug>
#include <QToolBox>
#include <QComboBox>
#include <QDockWidget>
#include <QTextEdit>
#include <QPushButton>

// Ogre
#include "OGRE/Ogre.h"

// OgreBullet
#include "OgreBulletDynamicsConstraint.h"
#include "Dynamics/Constraints/OgreBulletDynamics6DofConstraint.h"

// Core
#include "entity/entity.h"

// GeneLab
#include "graphic/ogremanager.h"
#include "graphic/ogrewidget.h"
#include "graphic/ogrescene.h"
#include "physics/bulletmanager.h"
#include "simulation/simulationmanager.h"
#include "simulation/ogrebulletsimulationmanager.h".h"
#include "factory/jsonloader.h"
#include "defaulteventmanager.h"
#include "sample/snakefamily.h"
#include "ogrebulletentity.h"

// App
#include "ogrebulletwindows.h"
#include "ui_ogrebulletwindows.h"
#include "sandboxtools.h"
#include "generic6dofconstraintcontroller.h"
#include "sample/snakefamily.h"

OgreBulletWindows::OgreBulletWindows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OgreBulletWindows)
{
    ui->setupUi(this);


    // --
    // -- GUI : Qt
    // --

    // TOOL BOX

    // boxe
    QToolBox *tbInspector = new QToolBox(this);


    // group G6Dof
    QWidget *tbG6DofC = new QWidget();
    Generic6DofConstraintController*  g6DofCC = new Generic6DofConstraintController();
    tbInspector->addItem(g6DofCC,"g6DofCC");

    // group 1
    QWidget *tbSimulation = new QWidget();
    QPushButton*  bPlaySimulation = new QPushButton("Play",tbSimulation);
    tbInspector->addItem(tbSimulation,"Simulation");

    //connect(bPlaySimulation,SIGNAL(clicked()),simulationScene,SLOT(refresh()));

    // group 2

    QComboBox *cbRenderMode = new QComboBox();
    cbRenderMode->addItem("Fill");
    cbRenderMode->addItem("Line");
    cbRenderMode->addItem("Point");
    //QPushButton*   but2=new QPushButton("Render",this);
    tbInspector->addItem(cbRenderMode,"Render");

    // group 3
    QPushButton*   but3=new QPushButton("",this);
    tbInspector->addItem(but3,"Fitness");

    // add to main win
    tbInspector->setStyleSheet("* { padding: 7px; width:100px}");


    // DOCKS

    // Createque
    QDockWidget *dwCreateque = new QDockWidget("Creatheque");
    QWidget *wCreatheque = new QWidget();
    wCreatheque->setStyleSheet("* {padding: 7px; width:100px}");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QPushButton("New Creature"));
    wCreatheque->setLayout(layout);

    dwCreateque->setWidget(wCreatheque);
    dwCreateque->setStyleSheet("* {padding: 7px; width:100px}");
    addDockWidget(Qt::LeftDockWidgetArea,dwCreateque);

    // Inspector
    QDockWidget *dwInspector = new QDockWidget("Inspector");
    dwInspector->setWidget(tbInspector);
    addDockWidget(Qt::RightDockWidgetArea,dwInspector);

    // Scene
    //setCentralWidget(simulationScene);
    //QDockWidget *dwScene = new QDockWidget("Scene");
    //dwScene->setWidget(w);
    //addDockWidget(Qt::LeftDockWidgetArea,dwScene);

    // Console
    QDockWidget *dwConsole = new QDockWidget("Console");
    dwConsole->setWidget(new QTextEdit(">> GeneLab Launched!"));
    addDockWidget(Qt::BottomDockWidgetArea,dwConsole);

    // Genome
    QDockWidget *dwGenome = new QDockWidget("Genome");
    dwGenome->setWidget(new QTextEdit("{blablabla...}"));
    addDockWidget(Qt::BottomDockWidgetArea,dwGenome);

    // --
    // -- Graphics : Ogre
    // --
    qDebug() << "Init Ogre";
    graphics = new GeneLabOgreBullet::OgreManager((unsigned long)this->winId());
    graphics->init();
    qDebug() << "[OK]\n";

    //qDebug() << "Create Scene";
    //GeneLabOgreBullet::OgreScene* scn = new GeneLabOgreBullet::OgreScene();

    qDebug() << "Init Cameras";
    // camera 1
    Ogre::Camera* cam1 = graphics->getOgreSceneManager()->createCamera("first");
    cam1->setPosition(Ogre::Vector3(0, 18, 70));
    cam1->lookAt(Ogre::Vector3(0, 0, -300));
    cam1->setNearClipDistance(5);

    // camera 2
    Ogre::Camera* cam2 = graphics->getOgreSceneManager()->createCamera("second");
    cam2->setPosition(Ogre::Vector3(0, 18, 0));
    cam2->lookAt(Ogre::Vector3(0, 0, 70));
    cam2->setNearClipDistance(5);
    qDebug() << "[OK]\n";

    qDebug() << "Init Widgets";
    // widget 1
    QWidget*    oW1 = graphics->createOgreWidget(cam1, this->ui->centralWidget);
    QWidget*    oW2 = graphics->createOgreWidget(cam2, this->ui->centralWidget);

    // widget 2
    this->ui->centralWidget->layout()->addWidget(oW1);
    this->ui->centralWidget->layout()->addWidget(oW2);

    // --
    // -- Physics : Bullet
    // --
    qDebug() << "Init Physics";
    physics = new GeneLabOgreBullet::BulletManager();
    physics->init(this->graphics);
    qDebug() << "[OK]\n";


    // --
    // -- Events
    // --
    qDebug() << "Init Events Manager";
    // Events
    GeneLabOgreBullet::DefaultEventManager *em = new GeneLabOgreBullet::DefaultEventManager(graphics,physics->getWorld());
    connect(oW1,SIGNAL(mousePressed(QMouseEvent*)),em,SLOT(mousePressEvent(QMouseEvent*)));
    connect(oW1,SIGNAL(mouseReleased(QMouseEvent*)),em,SLOT(mouseReleaseEvent(QMouseEvent*)));
    connect(oW1,SIGNAL(mouseMoved(QMouseEvent*)),em,SLOT(mouseMoveEvent(QMouseEvent*)));

    connect(oW1,SIGNAL(keyPressed(QKeyEvent*)),em,SLOT(keyPressEvent(QKeyEvent*)));
    connect(oW1,SIGNAL(keyReleased(QKeyEvent*)),em,SLOT(keyReleaseEvent(QKeyEvent*)));

    connect(oW1,SIGNAL(entered(QEvent*)),em,SLOT(enterViewPortEvent(QEvent*)));
    connect(oW1,SIGNAL(leaved(QEvent*)),em,SLOT(leaveViewPortEvent(QEvent*)));

    qDebug() << "[OK]\n";


    // --
    // -- Content (Sandbox) : OgreBullet
    // --

    // Cube of cubes
//    float size = 10.0f;
//    for(int i=0;i<10;i++)
//        for(int j=0;j<10;j++)
//            for(int k=0;k<10;k++)
//                SandboxTools::addBox(graphics,physics,Ogre::Vector3(i*size,k*size+size/2,j*size),Ogre::Vector3(size,size,size));

    // Six dof constraint
//    OgreBulletDynamics::RigidBody *boxA = SandboxTools::addBox(graphics,physics,Ogre::Vector3(0,10,0),Ogre::Vector3(1,1,1));
//    OgreBulletDynamics::RigidBody *boxB = SandboxTools::addBox(graphics,physics,Ogre::Vector3(4,10,0),Ogre::Vector3(1,1,1));


//    OgreBulletDynamics::SixDofConstraint *ct = new OgreBulletDynamics::SixDofConstraint(boxA,boxB,Ogre::Vector3(1,0,0),Ogre::Quaternion(),Ogre::Vector3(-1,0,0),Ogre::Quaternion());
//    physics->getWorld()->addConstraint(ct);

//    g6DofCC->setConstraint((btGeneric6DofConstraint*) ct->getBulletTypedConstraint());




    // Family params
    //QMap<QString, QString> map;
    //map.insert("length","10");
    //map.insert("piecelength","10");

    // Create snake
    GeneLabOgreBullet::SnakeFamily * snakeFamily = new GeneLabOgreBullet::SnakeFamily(QVariant());
    GeneLabOgreBullet::OgreBulletEntity* snake = snakeFamily->createOgreBulletEntity();
    snake->setup(graphics,physics);


    // --
    // -- World : RENAME TO SimulationManager or SimulationEngine
    // --
    qDebug() << "Init World";
    GeneLabCore::SimulationManager* world = new GeneLabOgreBullet::OgreBulletSimulationManager(physics,graphics,em);
    world->setup();
    qDebug() << "[OK]\n";

    qDebug() << "Start World";
    world->start();
    qDebug() << "[OK]\n";
}

OgreBulletWindows::~OgreBulletWindows()
{
    delete ui;
}

void OgreBulletWindows::updateGraphics() {
//    qDebug() << "update graphics..";
//    graphics->beforeStep();
//    physics->beforeStep();
//    graphics->step();
//    physics ->step();
//    graphics->afterStep();
//    physics->afterStep();
}
