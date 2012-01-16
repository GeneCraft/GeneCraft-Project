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

#include "structuralmutationcontroller.h"
#include "ui_structuralmutationcontroller.h"

#include "mutation/structuralmutation.h"
#include "mutation/structurallist.h"
#include "mutationelementcontroller.h"

#include <QDebug>

#define PROBABILITY_PRECISION 1000.0f

using namespace GeneCraftCore;

StructuralMutationController::StructuralMutationController(StructuralMutation *mutation,QString name,
                                                           StructuralList *list, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StructuralMutationController)
{
    ui->setupUi(this);

    this->mutation = mutation;
    this->list = list;

    ui->cbName->setText(name);

    connect(ui->cbName,SIGNAL(toggled(bool)),this,SLOT(nameToggled(bool)));
    connect(ui->sAddProbability,SIGNAL(valueChanged(int)),this,SLOT(addProbabilityChanged(int)));
    connect(ui->sRemoveProbability,SIGNAL(valueChanged(int)),this,SLOT(removeProbabilityChanged(int)));
    connect(ui->sReplaceProbability,SIGNAL(valueChanged(int)),this,SLOT(replaceProbabilityChanged(int)));

    if(list) {
        foreach(MutationElement *me, list->elements) {
            MutationElementController * mec = new MutationElementController(me);
            ui->vlStructuralList->addWidget(mec);
            mecs.append(mec);
        }
    }

    btScalar tmp;

    // WTF without qRound, value is false !
    tmp = qRound(mutation->addProbability * PROBABILITY_PRECISION);
    ui->sAddProbability->setValue(tmp);

    // WTF without qRound, value is false !
    tmp = qRound(mutation->deleteProbability * PROBABILITY_PRECISION);
    ui->sRemoveProbability->setValue(tmp);

    // WTF without qRound, value is false !
    tmp = qRound(mutation->replaceProbability * PROBABILITY_PRECISION);
    ui->sReplaceProbability->setValue(tmp);

    ui->cbName->setChecked(mutation->enable);
    nameToggled(mutation->enable);
}

StructuralMutationController::~StructuralMutationController()
{
    delete ui;
}

void StructuralMutationController::save() {

    if(mutation != NULL) {
        mutation->enable = ui->cbName->isChecked();
        mutation->addProbability = ui->sAddProbability->value() / PROBABILITY_PRECISION;
        mutation->deleteProbability = ui->sRemoveProbability->value() / PROBABILITY_PRECISION;
        mutation->replaceProbability = ui->sReplaceProbability->value() / PROBABILITY_PRECISION;

        foreach(MutationElementController *mec, mecs)
            mec->save();
    }
}

void StructuralMutationController::nameToggled(bool checked){
    ui->fForm->setEnabled(checked);

    QFont f(ui->cbName->font());
    f.setBold(checked);
    ui->cbName->setFont(f);

    foreach(MutationElementController *mec, mecs)
        mec->setEnabled(checked);
}

void StructuralMutationController::addProbabilityChanged(int value){
    ui->lAddProbabilty->setText(QString::number(value / PROBABILITY_PRECISION * 100.0).append("%"));
}

void StructuralMutationController::removeProbabilityChanged(int value){
    ui->lRemoveProbabilty->setText(QString::number(value / PROBABILITY_PRECISION * 100.0).append("%"));
}

void StructuralMutationController::replaceProbabilityChanged(int value){
    ui->lReplaceProbabilty->setText(QString::number(value / PROBABILITY_PRECISION * 100.0).append("%"));
}
