#include "brainapp.h"
#include "ui_brainapp.h"

#include "genelabcoreclasses.h"
#include "brainengine.h"

#include <QLayout>
#include <QDebug>

using namespace GeneLabCore;

BrainApp::BrainApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BrainApp)
{
    ui->setupUi(this);

    engine = new BrainEngine();

    engine->createGrid(51); // 10x10 network
    QWidget* w = engine->getRenderWidget(ui->centralWidget);

    this->setCentralWidget(w);

    this->timer = new QTimer();
    timer->setInterval(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer->start();

}

void BrainApp::tick()  {
   engine->beforeStep();
   engine->step();
   engine->afterStep();
}

BrainApp::~BrainApp()
{
    delete ui;
}
