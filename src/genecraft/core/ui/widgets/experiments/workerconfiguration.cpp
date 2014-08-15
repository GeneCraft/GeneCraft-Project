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

#include "workerconfiguration.h"
#include "ui_workerconfiguration.h"

#include <ctime>

WorkerConfiguration::WorkerConfiguration(QVariant workerData, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkerConfiguration)
{
    ui->setupUi(this);

    init(workerData.toMap());

    this->validated = false;

    connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(valid()));
    connect(ui->pbReset, SIGNAL(clicked()), this ,SLOT(reset()));
}

void WorkerConfiguration::init(QVariantMap worker) {

    QVariantMap selection = worker["selection"].toMap();

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

void WorkerConfiguration::reset() {

    QVariantMap worker;

    worker.insert("name", "Anonymous");
    worker.insert("maxGen", 100);
    worker.insert("popSize", 20);
    worker.insert("nbBestResults", 20);
    worker.insert("nbRandomResults", 200);
    QVariantMap selection;
    selection.insert("bestPop", 20);
    selection.insert("bestResult", 10);
    selection.insert("randomNew", 10);
    selection.insert("randomPop", 10);
    selection.insert("randomResult", 20);
    worker.insert("selection", selection);

    init(worker);
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
