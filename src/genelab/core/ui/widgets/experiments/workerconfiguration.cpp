#include "workerconfiguration.h"
#include "ui_workerconfiguration.h"

#include <ctime>

WorkerConfiguration::WorkerConfiguration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkerConfiguration)
{
    ui->setupUi(this);
    ui->sldBestResults->setValue(10);
    ui->sldRandomResults->setValue(20);
    ui->sldBestPop->setValue(20);
    ui->sldRandomPop->setValue(10);
    ui->sldRandomSeed->setValue(10);
    ui->spbMaxGen->setValue(100);
    ui->spbPopSize->setValue(20);
    ui->spbBestResults->setValue(20);
    ui->spbRandomResults->setValue(200);
    ui->txtWorkerName->setText("Anonymous");

    connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(close()));
}

QVariant WorkerConfiguration::getWorkerData() {
    QVariantMap workerData;

    workerData["maxGen"] = ui->spbMaxGen->value();
    workerData["popSize"] = ui->spbPopSize->value();
    workerData["name"] = ui->txtWorkerName->text();
    workerData["nbBestResults"] = ui->spbBestResults->value();
    workerData["nbRandomResults"] = ui->spbRandomResults->value();
    QVariantMap selectionData;
    selectionData["bestPop"] = ui->sldBestPop->value();
    selectionData["bestResult"] = ui->sldBestResults->value();
    selectionData["randomPop"] = ui->sldRandomPop->value();
    selectionData["randomResult"] = ui->sldRandomResults->value();
    selectionData["randomNew"] = ui->sldRandomSeed->value();
    workerData["selection"] = selectionData;

    return workerData;
}

WorkerConfiguration::~WorkerConfiguration()
{
    delete ui;
}
