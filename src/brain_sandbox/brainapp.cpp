#include "brainapp.h"
#include "ui_brainapp.h"

#include "classes.h"
#include "engine/brainengine.h"

#include <QLayout>
#include <QDebug>

using namespace GeneLabCore;
using namespace GeneLabWidget;

BrainApp::BrainApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BrainApp)
{
    ui->setupUi(this);

    qDebug() << "Creation !";
    engine = new BrainEngine();

    qDebug() << "Creation !";

    engine->addNetwork(4); // 10x10 network

    qDebug() << "Creation !";

    QWidget* w = engine->getRenderWidget(ui->centralWidget);

    qDebug() << "Creation !";
    this->setCentralWidget(w);
    this->timer = new QTimer();
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer->start();

}

void BrainApp::tick()  {
    qDebug() << "tick !";
   engine->beforeStep();
   engine->step();
   engine->afterStep();
}

BrainApp::~BrainApp()
{
    delete ui;
}
