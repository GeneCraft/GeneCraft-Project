#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "OpenGL/GLCreatureViewer.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // WINDOW PROPERTIES
    setWindowTitle("GenLab");

    // OpenGL Widget
    GLCreatureViewer *simulationScene = new GLCreatureViewer();

    // MENU

    // file
    QMenu *mFile = menuBar()->addMenu(tr("&File"));
    QAction *aLoad = mFile->addAction("Load creature");
    QAction *aQuit = mFile->addAction("Quit");
    //connect(aQuit,SIGNAL(triggered()),this,SLOT(close()));

    // windows
    QMenu *mWindow = menuBar()->addMenu(tr("&Window"));
    QAction *aCreatheque = mWindow->addAction("Creatheque");


    // TOOL BOX

    // boxe
    QToolBox *tbInspector = new QToolBox(this);

    // group 1
    QWidget *tbSimulation = new QWidget();
    QPushButton*  bPlaySimulation = new QPushButton("Play",tbSimulation);
    tbInspector->addItem(tbSimulation,"Simulation");

    connect(bPlaySimulation,SIGNAL(clicked()),simulationScene,SLOT(refresh()));

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
    setCentralWidget(simulationScene);
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

    /*
    // FENETRES INTERNES

    QMdiArea *mdiArea = new QMdiArea();
    this->setCentralWidget(mdiArea);

    mdiArea->addSubWindow(w);

    QWidget *menuOptions = new QWidget();

    QVBoxLayout *ltOptions = new QVBoxLayout;
    QCheckBox *cbLightning = new QCheckBox("Lightning");
    ltOptions->addWidget(cbLightning);
    menuOptions->setLayout(ltOptions);
    mdiArea->addSubWindow(box);
    */


    /*

     // GRID BOX

     QWidget *window = new QWidget;

     QGridLayout *layout = new QGridLayout;

     // GLWidget
     GLWidget_1 *w = new GLWidget_1();

     layout->addWidget(w,0,0,1,1);
     w->setGeometry(0,0,800,600);

     // Options
     QVBoxLayout *ltOptions = new QVBoxLayout;
     QCheckBox *cbLightning = new QCheckBox("Lightning");
     ltOptions->addWidget(cbLightning);
     ltOptions->setGeometry(QRect(0,0,100,800));


     layout->addLayout(ltOptions,0,1,1,1,Qt::AlignTop);


     window->setLayout(layout);
     this->setCentralWidget(window);
    */

    //showFullScreen();
    //QRect screenResolution = QApplication::desktop()->screenGeometry();
    //setGeometry(0,0,screenResolution.width(),screenResolution.height());
    setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
    delete ui;
}
