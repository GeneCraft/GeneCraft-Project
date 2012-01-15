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

#include "mutationelementcontroller.h"
#include "ui_mutationelementcontroller.h"

#include "mutation/structurallist.h"

#define WEIGHT_PRECISION 10.0f

using namespace GeneCraftCore;

MutationElementController::MutationElementController(MutationElement *me, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MutationElementController)
{
    ui->setupUi(this);

    this->me = me;

    ui->lName->setText(me->name);

    connect(ui->sWeight,SIGNAL(valueChanged(int)),this,SLOT(weightChanged(int)));

    ui->sWeight->setValue(me->weight * WEIGHT_PRECISION);
}

MutationElementController::~MutationElementController()
{
    delete ui;
}

void MutationElementController::save() {
    me->weight = ui->sWeight->value() / WEIGHT_PRECISION;
}

void MutationElementController::weightChanged(int value) {
    ui->lWeight->setText(QString::number(value / WEIGHT_PRECISION));
}
