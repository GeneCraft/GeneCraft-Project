#include "workerconfiguration.h"
#include "ui_workerconfiguration.h"

#include <ctime>

WorkerConfiguration::WorkerConfiguration(QVariant workerData, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkerConfiguration)
{
    QVariantMap worker = workerData.toMap();
    QVariantMap selection = worker["selection"].toMap();

    ui->setupUi(this);
    ui->sldBestResults->setValue(selection["bestResult"].toInt());
    ui->sldRandomResults->setValue(selection["randomResult"].toInt());
    ui->sldBestPop->setValue(selection["bestPop"].toInt());
    ui->sldRandomPop->setValue(selection["randomPop"].toInt());
    ui->sldRandomSeed->setValue(selection["randomNew"].toInt());
    ui->spbMaxGen->setValue(worker["maxGen"].toInt());
    ui->spbPopSize->setValue(worker["popSize"].toInt());
    ui->spbBestResults->setValue(worker["nbBestResults"].toInt());
    ui->spbRandomResults->setValue(worker["nbRandomResults"].toInt());
    ui->txtWorkerName->setText(worker["name"].toString());

    this->validated = false;

    connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(valid()));
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

bool WorkerConfiguration::isValidated() {
    return validated;
}

void WorkerConfiguration::valid() {
    this->validated = true;
    this->close();
}

WorkerConfiguration::~WorkerConfiguration()
{
    delete ui;
}
