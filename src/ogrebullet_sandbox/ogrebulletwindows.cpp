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
#include "factory/mainfactory.h"

// Core
#include "entity/entity.h"

// GeneLab
#include "graphic/ogremanager.h"
#include "graphic/ogrewidget.h"
#include "graphic/ogrescene.h"
#include "physics/bulletmanager.h"
#include "simulation/simulationmanager.h"
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


using namespace GeneLabOgreBullet;
using namespace GeneLabCore;
using namespace GeneLabFactory;

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


    // ---------------------
    // -- Scene (Content) --
    // ---------------------
    qDebug() << "Scene creation";
    OgreBulletSandBoxScene *scene = new OgreBulletSandBoxScene((BulletManager*)factory->getEngines().find("Bullet").value(),
                                                               (OgreManager*)factory->getEngines().find("Ogre").value());
    scene->init();
    qDebug() << "[OK]\n";



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
