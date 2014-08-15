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

#include "simpleprobabilitycontroller.h"
#include "ui_simpleprobabilitycontroller.h"

#include "mutation/simpleprobabilitymutation.h"

#define PROBABILITY_PRECISION 1000.0

using namespace GeneCraftCore;

SimpleProbabilityController::SimpleProbabilityController(SimpleProbabilityMutation * mutation, QString name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimpleProbabilityController)
{
    ui->setupUi(this);

    this->mutation = mutation;

    ui->cbName->setText(name);

    connect(ui->cbName,SIGNAL(toggled(bool)),this,SLOT(nameToggled(bool)));
    connect(ui->sProbability,SIGNAL(valueChanged(int)),this,SLOT(probabilityChanged(int)));

    ui->sProbability->setValue(qRound(mutation->probability * PROBABILITY_PRECISION));
    ui->cbName->setChecked(mutation->enable);
    nameToggled(mutation->enable);
}


SimpleProbabilityController::~SimpleProbabilityController()
{
    delete ui;
}

void SimpleProbabilityController::save() {

    if(mutation != NULL) {
        mutation->enable = ui->cbName->isChecked();
        mutation->probability = ui->sProbability->value() / PROBABILITY_PRECISION;
    }
}

void SimpleProbabilityController::nameToggled(bool checked){
    ui->fForm->setEnabled(checked);

    QFont f(ui->cbName->font());
    f.setBold(checked);
    ui->cbName->setFont(f);
}

void SimpleProbabilityController::probabilityChanged(int value){
    ui->lProbabilty->setText(QString::number(value / PROBABILITY_PRECISION * 100.0).append("%"));
}


