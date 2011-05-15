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

// Factory
#include "core/factory/mainfactory.h"

// Core
#include "core/entity/entity.h"

// GeneLab
#include "core/engine/ogremanager.h"
#include "ui/widget/ogrewidget.h"
#include "core/engine/bulletmanager.h"
#include "core/simulation/simulationmanager.h"
#include "core/factory/jsonloader.h"
#include "core/engine/eventmanager.h"
#include "core/entity/sample/snakefamily.h"
#include "core/entity/struct/treeshape.h"
#include "core/entity/struct/fixation.h"
#include "core/entity/ogrebulletentity.h"

// App
#include "ui/ogrebulletwindows.h"
#include "ui_ogrebulletwindows.h"
#include "core/utils/sandboxtools.h"
#include "core/engine/input/creatureviewerinputmanager.h"
#include "ui/widget/generic6dofconstraintcontroller.h"


namespace GeneLabCore {

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
    Generic6DofConstraintController*  g6DofCC = new Generic6DofConstraintController();
    tbInspector->addItem(g6DofCC,"g6DofCC");

    // group 1
    QWidget *tbSimulation = new QWidget();
    //QPushButton*  bPlaySimulation = new QPushButton("Play",tbSimulation);
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

    MainFactory* factory = new MainFactory(this->ui->centralWidget, (unsigned long) this->winId() );


    // TODO :
    // Move into EntityFactory
    // Discussion about entity management to do...
    SnakeFamily * snakeFamily = new SnakeFamily(QVariant());
    OgreBulletEntity* snake = snakeFamily->createOgreBulletEntity();

    snake->init((OgreManager*)factory->getEngines().find("Ogre").value(),
                (BulletManager*)factory->getEngines().find("Bullet").value(),
                (BrainEngine*)factory->getEngines().find("Brain").value());

    snake->setup(); // position

    // attach the nose in the air
    btGeneric6DofConstraint *ctRoot = new btGeneric6DofConstraint(*snake->getShape()->getRoot()->getRigidBody()->getBulletRigidBody(),btTransform(btQuaternion(),btVector3(0,0,0)),true);
    ctRoot->setAngularLowerLimit(btVector3(0,0,0));
    ctRoot->setAngularUpperLimit(btVector3(0,0,0));
    ((BulletManager*)factory->getEngines().find("Bullet").value())->getWorld()->getBulletDynamicsWorld()->addConstraint(ctRoot);

    // ------------------------
    // -- Simulation Manager --
    // ------------------------
    qDebug() << "Init Simulation Manager";
    SimulationManager* simulationManager
            = new SimulationManager(factory->getEngines().values());

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

}
