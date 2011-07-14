#include "floatmutationcontroller.h"
#include "ui_floatmutationcontroller.h"

#include "mutation/floatmutation.h"

#define FACTOR_PRECISION 100.0
#define PROBABILITY_PRECISION 10.0

using namespace GeneLabCore;

FloatMutationController::FloatMutationController(FloatMutation *mutation, QString name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FloatMutationController)
{
    this->mutation = mutation;

    createForm(name);

    ui->sProbability->setValue(mutation->probability * PROBABILITY_PRECISION);
    ui->sMinFactor->setValue(mutation->minFact * FACTOR_PRECISION);
    ui->sMaxFactor->setValue(mutation->maxFact * FACTOR_PRECISION);
    ui->cbName->setChecked(mutation->enable);
}

void FloatMutationController::createForm(QString name){
    ui->setupUi(this);

    ui->cbName->setText(name);

    connect(ui->cbName,SIGNAL(toggled(bool)),this,SLOT(nameToggled(bool)));
    connect(ui->sProbability,SIGNAL(valueChanged(int)),this,SLOT(probabilityChanged(int)));
    connect(ui->sMinFactor,SIGNAL(valueChanged(int)),this,SLOT(minFactorChanged(int)));
    connect(ui->sMaxFactor,SIGNAL(valueChanged(int)),this,SLOT(maxFactorChanged(int)));
//    connect(ui->sMinValue,SIGNAL(valueChanged(int)),this,SLOT(minValueChanged(int)));
//    connect(ui->sMaxValue,SIGNAL(valueChanged(int)),this,SLOT(maxValueChanged(int)));
}

FloatMutationController::~FloatMutationController()
{
    delete ui;
}

void FloatMutationController::save() {

    if(mutation != NULL) {
        mutation->enable = ui->cbName->isChecked();
        mutation->probability = ui->sProbability->value() / PROBABILITY_PRECISION;
        mutation->minFact = ui->sMinFactor->value() / FACTOR_PRECISION;
        mutation->maxFact = ui->sMaxFactor->value() / FACTOR_PRECISION;
    }
}

//void FloatMutationController::setMinFactor(float minFactor){
//    ui->sMinFactor->setValue(minFactor * FACTOR_PRECISION);
//}
//float FloatMutationController::getMinFactor(){
//    return ui->sMinFactor->value() / FACTOR_PRECISION;
//}
//void FloatMutationController::setMaxFactor(float maxFactor){
//    ui->sMaxFactor->setValue(maxFactor * FACTOR_PRECISION);
//}
//float FloatMutationController::getMaxFactor(){
//    return ui->sMaxFactor->value() / FACTOR_PRECISION;
//}

void FloatMutationController::nameToggled(bool checked){
    ui->sProbability->setEnabled(checked);
    ui->sMinFactor->setEnabled(checked);
    ui->sMaxFactor->setEnabled(checked);
}

void FloatMutationController::probabilityChanged(int value){
    ui->lProbabilty->setText(QString::number(value / 10.0).append("%"));
}

void FloatMutationController::minFactorChanged(int value){
    ui->lMinFactor->setText(QString::number(value / FACTOR_PRECISION));
}
void FloatMutationController::maxFactorChanged(int value){
    ui->lMaxFactor->setText(QString::number(value / FACTOR_PRECISION));
}
//void FloatMutationController::minValueChanged(int value){
//    ui->lMinValue->setText(QString::number(value));
//}
//void FloatMutationController::maxValueChanged(int value){
//    ui->lMaxValue->setText(QString::number(value));
//}
