#include "integermutationcontroller.h"
#include "ui_integermutationcontroller.h"

#include "mutation/integermutation.h"

#define PROBABILITY_PRECISION 10.0

using namespace GeneLabCore;

IntegerMutationController::IntegerMutationController(QString name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntegerMutationController)
{
    createForm(name);
}

IntegerMutationController::IntegerMutationController(IntegerMutation *mutation, QString name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntegerMutationController)
{
    this->mutation = mutation;

    createForm(name);

    ui->sProbability->setValue(mutation->probability * PROBABILITY_PRECISION);
    ui->sMinIncr->setValue(mutation->minIncr);
    ui->sMaxIncr->setValue(mutation->maxIncr);
    ui->cbName->setChecked(mutation->enable);
    nameToggled(mutation->enable);
}

void IntegerMutationController::createForm(QString name){
    ui->setupUi(this);

    ui->cbName->setText(name);

    connect(ui->cbName,SIGNAL(toggled(bool)),this,SLOT(nameToggled(bool)));
    connect(ui->sProbability,SIGNAL(valueChanged(int)),this,SLOT(probabilityChanged(int)));
    connect(ui->sMinIncr,SIGNAL(valueChanged(int)),this,SLOT(minFactorChanged(int)));
    connect(ui->sMaxIncr,SIGNAL(valueChanged(int)),this,SLOT(maxFactorChanged(int)));
//    connect(ui->sMinValue,SIGNAL(valueChanged(int)),this,SLOT(minValueChanged(int)));
//    connect(ui->sMaxValue,SIGNAL(valueChanged(int)),this,SLOT(maxValueChanged(int)));
}

IntegerMutationController::~IntegerMutationController()
{
    delete ui;
}

void IntegerMutationController::save() {

    if(mutation != NULL) {

        mutation->enable = ui->cbName->isChecked();
        mutation->probability = ui->sProbability->value() / PROBABILITY_PRECISION;
        mutation->minIncr = ui->sMinIncr->value();
        mutation->maxIncr = ui->sMaxIncr->value();
    }
}

void IntegerMutationController::nameToggled(bool checked){
    ui->fForm->setEnabled(checked);

    QFont f(ui->cbName->font());
    f.setBold(checked);
    ui->cbName->setFont(f);
}

void IntegerMutationController::probabilityChanged(int value){
    ui->lProbabilty->setText(QString::number(value / 10.0).append("%"));
}

void IntegerMutationController::minFactorChanged(int value){
    ui->lMinIncr->setText(QString::number(value));
}
void IntegerMutationController::maxFactorChanged(int value){
    ui->lMaxIncr->setText(QString::number(value));
}
//void IntegerMutationController::minValueChanged(int value){
//    ui->lMinValue->setText(QString::number(value));
//}
//void IntegerMutationController::maxValueChanged(int value){
//    ui->lMaxValue->setText(QString::number(value));
//}
