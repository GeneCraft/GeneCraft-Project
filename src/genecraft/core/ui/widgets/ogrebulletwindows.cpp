/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

// Qt
#include <QDebug>
#include <QToolBox>
#include <QComboBox>
#include <QDockWidget>
#include <QTextEdit>
#include <QPushButton>

// Ogre
#include "Ogre.h"

// Factory
#include "btofactory.h"

// Core
#include "entity.h"

// GeneCraft
#include "ogre/ogreengine.h"
#include "ogre/ogrewidget.h"
#include "bullet/bulletengine.h"
#include "simulationmanager.h"
#include "events/eventsmanager.h"
#include "families/snakefamily.h"
#include "body/treeshape.h"
#include "body/fixation.h"
#include "bulletogre/shapes/btosphere.h"
#include "bulletogre/shapes/btobox.h"

// App
#include "ogrebulletwindows.h"
#include "ui_ogrebulletwindows.h"
//#include "sandboxtools.h"
#include "creatureviewerinputmanager.h"
#include "widgets/entities/generic6dofconstraintcontroller.h"

namespace GeneCraftCore {

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
    dwConsole->setWidget(new QTextEdit(">> GeneCraft Launched!"));
    addDockWidget(Qt::BottomDockWidgetArea,dwConsole);

    // Genome
    QDockWidget *dwGenome = new QDockWidget("Genome");
    dwGenome->setWidget(new QTextEdit("{blablabla...}"));
    addDockWidget(Qt::BottomDockWidgetArea,dwGenome);


    // Make all :)
    factory = new btoFactory(this->ui->centralWidget, (unsigned long) this->winId() );

    // ------------------------
    // -- Simulation Manager --
    // ------------------------
    qDebug() << "Init Simulation Manager";
    SimulationManager* simulationManager
            = new SimulationManager(factory->getEngines());

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
