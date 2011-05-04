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
#include "eventmanager.h"
#include "sample/snakefamily.h"
#include "entity/struct/treeshape.h"
#include "entity/struct/fixation.h"
#include "ogrebulletentity.h"
#include "ogrescene.h"

// App
#include "ogrebulletwindows.h"
#include "ui_ogrebulletwindows.h"
#include "sandboxtools.h"
#include "creatureviewerinputmanager.h"
#include "ogrebulletsandboxscene.h"
#include "generic6dofconstraintcontroller.h"

OgreBulletWindows::OgreBulletWindows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OgreBulletWindows)
{
    ui->setupUi(this);

    // --------------
    // -- GUI : Qt --
    // --------------

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

    // group 2
    QComboBox *cbRenderMode = new QComboBox();
    cbRenderMode->addItem("Fill");
    cbRenderMode->addItem("Line");
    cbRenderMode->addItem("Point");
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

    // Console
    QDockWidget *dwConsole = new QDockWidget("Console");
    dwConsole->setWidget(new QTextEdit(">> GeneLab Launched!"));
    addDockWidget(Qt::BottomDockWidgetArea,dwConsole);

    // Genome
    QDockWidget *dwGenome = new QDockWidget("Genome");
    dwGenome->setWidget(new QTextEdit("{blablabla...}"));
    addDockWidget(Qt::BottomDockWidgetArea,dwGenome);




    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // !! It's really the windows that must do this ??? !!
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // I think to create a wrap named GeneLabEngine which contains
    // all engines is a good idea... no ?
    // GeneLabEngine geneLabEngine = new GeneLabEngine();
    // geneLabEngine->getOgreWidget();


    // ---------------------
    // -- Graphics : Ogre --
    // ---------------------

    qDebug() << "Init Ogre";
    ogreEngine = new GeneLabOgreBullet::OgreManager((unsigned long)this->winId());
    ogreEngine->init();
    qDebug() << "[OK]\n";

    qDebug() << "Init Cameras";

    // camera 1
    Ogre::Camera* cam1 = ogreEngine->getOgreSceneManager()->createCamera("firstCamera");
    cam1->setPosition(Ogre::Vector3(0, 2, 6));
    cam1->lookAt(Ogre::Vector3(0, 2, 0));
    cam1->setNearClipDistance(0.001); // 1 mm
    cam1->setFarClipDistance(100); // 100m

    // camera 2
    // Ogre::Camera* cam2 = graphics->getOgreSceneManager()->createCamera("secondCamera");
    // cam2->setPosition(Ogre::Vector3(0, 18, 0));
    // cam2->lookAt(Ogre::Vector3(0, 0, 70));
    // cam2->setNearClipDistance(5);
    // qDebug() << "[OK]\n";

    qDebug() << "Init Widgets";
    // widget 1
    QWidget* oW1 = ogreEngine->createOgreWidget(cam1, this->ui->centralWidget);
    this->ui->centralWidget->layout()->addWidget(oW1);

    // widget 2
    // this->ui->centralWidget->layout()->addWidget(oW2);
    // QWidget* oW2 = graphics->createOgreWidget(cam2, this->ui->centralWidget);


    // ----------------------
    // -- Physics : Bullet --
    // ----------------------

    qDebug() << "Init Bullet";
    bulletEngine = new GeneLabOgreBullet::BulletManager();
    bulletEngine->init(this->ogreEngine);
    qDebug() << "[OK]\n";


    // ------------
    // -- Events --
    // ------------
    qDebug() << "Init Events Manager";

    // Events
    GeneLabOgreBullet::EventManager *em = new GeneLabOgreBullet::EventManager();

    CreatureViewerInputManager *cvim = new CreatureViewerInputManager();
    cvim->initOgreBullet(ogreEngine,bulletEngine,cam1);
    em->addListener(cvim);

    connect(oW1,SIGNAL(mousePressed(QMouseEvent*)),em,SLOT(mousePressEvent(QMouseEvent*)));
    connect(oW1,SIGNAL(mouseReleased(QMouseEvent*)),em,SLOT(mouseReleaseEvent(QMouseEvent*)));
    connect(oW1,SIGNAL(mouseMoved(QMouseEvent*)),em,SLOT(mouseMoveEvent(QMouseEvent*)));

    connect(oW1,SIGNAL(keyPressed(QKeyEvent*)),em,SLOT(keyPressEvent(QKeyEvent*)));
    connect(oW1,SIGNAL(keyReleased(QKeyEvent*)),em,SLOT(keyReleaseEvent(QKeyEvent*)));

    connect(oW1,SIGNAL(entered(QEvent*)),em,SLOT(enterViewPortEvent(QEvent*)));
    connect(oW1,SIGNAL(leaved(QEvent*)),em,SLOT(leaveViewPortEvent(QEvent*)));

    qDebug() << "[OK]\n";


    // ---------------------
    // -- Scene (Content) --
    // ---------------------
    qDebug() << "Scene creation";
    OgreBulletSandBoxScene *scene = new OgreBulletSandBoxScene(bulletEngine, ogreEngine);
    scene->init();
    qDebug() << "[OK]\n";


    // ------------------------
    // -- Simulation Manager --
    // ------------------------
    qDebug() << "Init Simulation Manager";
    GeneLabCore::SimulationManager* simulationManager = new GeneLabOgreBullet::OgreBulletSimulationManager(bulletEngine,ogreEngine,em);
    simulationManager->setup();
    qDebug() << "[OK]\n";

    qDebug() << "Start simulation";
    simulationManager->start();
    qDebug() << "[OK]\n";
}

OgreBulletWindows::~OgreBulletWindows()
{
    delete ui;
}
