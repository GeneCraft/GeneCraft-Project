#include "floatmutationcontroller.h"
#include "ui_floatmutationcontroller.h"

#include "mutation/floatmutation.h"
#include <QDebug>

#define FACTOR_PRECISION 100.0f
#define PROBABILITY_PRECISION 1000.0f

using namespace GeneCraftCore;

FloatMutationController::FloatMutationController(FloatMutation *mutation, QString name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FloatMutationController)
{
    this->mutation = mutation;

    createForm(name);

    // WTF without qRound, values are false !
    ui->sProbability->setValue(qRound(mutation->probability * PROBABILITY_PRECISION));
    ui->sMean->setValue(qRound(mutation->mean * FACTOR_PRECISION)); // WTF doesn't work for -1 without qRound ?!?
    ui->sSigma->setValue(qRound(mutation->sigma * FACTOR_PRECISION)); // WTF doesn't work for -1 without qRound ?!?
    ui->cbName->setChecked(mutation->enable);
    nameToggled(mutation->enable);
}

void FloatMutationController::createForm(QString name){
    ui->setupUi(this);

    ui->cbName->setText(name);

    connect(ui->cbName,SIGNAL(toggled(bool)),this,SLOT(nameToggled(bool)));
    connect(ui->sProbability,SIGNAL(valueChanged(int)),this,SLOT(probabilityChanged(int)));
    connect(ui->sMean,SIGNAL(valueChanged(int)),this,SLOT(meanChanged(int)));
    connect(ui->sSigma,SIGNAL(valueChanged(int)),this,SLOT(sigmaChanged(int)));
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
        mutation->mean = ui->sMean->value() / FACTOR_PRECISION;
        mutation->sigma = ui->sSigma->value() / FACTOR_PRECISION;
    }
}

//void FloatMutationController::setMinFactor(btScalar minFactor){
//    ui->sMinFactor->setValue(minFactor * FACTOR_PRECISION);
//}
//btScalar FloatMutationController::getMinFactor(){
//    return ui->sMinFactor->value() / FACTOR_PRECISION;
//}
//void FloatMutationController::setMaxFactor(btScalar maxFactor){
//    ui->sMaxFactor->setValue(maxFactor * FACTOR_PRECISION);
//}
//btScalar FloatMutationController::getMaxFactor(){
//    return ui->sMaxFactor->value() / FACTOR_PRECISION;
//}

void FloatMutationController::nameToggled(bool checked){

    ui->fForm->setEnabled(checked);

    QFont f(ui->cbName->font());
    f.setBold(checked);
    ui->cbName->setFont(f);
}

void FloatMutationController::probabilityChanged(int value){
    ui->lProbabilty->setText(QString::number(value / PROBABILITY_PRECISION * 100.0).append("%"));
}

void FloatMutationController::meanChanged(int value){
    ui->lMean->setText(QString::number(value / FACTOR_PRECISION));
}
void FloatMutationController::sigmaChanged(int value){
    ui->lSigma->setText(QString::number(value / FACTOR_PRECISION));
}
//void FloatMutationController::minValueChanged(int value){
//    ui->lMinValue->setText(QString::number(value));
//}
//void FloatMutationController::maxValueChanged(int value){
//    ui->lMaxValue->setText(QString::number(value));
//}
