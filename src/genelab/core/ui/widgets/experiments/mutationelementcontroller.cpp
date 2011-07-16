#include "mutationelementcontroller.h"
#include "ui_mutationelementcontroller.h"

#include "mutation/structurallist.h"

#define WEIGHT_PRECISION 10.0f

using namespace GeneLabCore;

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
