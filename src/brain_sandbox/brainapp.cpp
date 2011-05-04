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

    engine->addNetwork(5); // 10x10 network

    qDebug() << "Creation !";

    QWidget* w = engine->getRenderWidget(ui->centralWidget);

    qDebug() << "Creation !";
    this->setCentralWidget(w);
    this->timer = new QTimer();
    timer->setInterval(50);
    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer->start();

}

int cpt = 0;
void BrainApp::tick()  {
    cpt++;
    if(!(cpt % 10000)) {
        qDebug() << cpt;
    }
   engine->beforeStep();
   engine->step();
   engine->afterStep();
}

BrainApp::~BrainApp()
{
    delete ui;
}
