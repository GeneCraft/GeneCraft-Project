#include "floatmutationcontroller.h"
#include "ui_floatmutationcontroller.h"

FloatMutationController::FloatMutationController(QString name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FloatMutationController)
{
    ui->setupUi(this);

    ui->lName->setText(name);

    connect(ui->sProbability,SIGNAL(valueChanged(int)),this,SLOT(probabilityChanged(int)));
    connect(ui->sMinFactor,SIGNAL(valueChanged(int)),this,SLOT(minFactorChanged(int)));
    connect(ui->sMaxFactor,SIGNAL(valueChanged(int)),this,SLOT(maxFactorChanged(int)));
    connect(ui->sMinValue,SIGNAL(valueChanged(int)),this,SLOT(minValueChanged(int)));
    connect(ui->sMaxValue,SIGNAL(valueChanged(int)),this,SLOT(maxValueChanged(int)));
}

FloatMutationController::~FloatMutationController()
{
    delete ui;
}

void FloatMutationController::probabilityChanged(int value){
    ui->lProbabilty->setText(QString::number(value).append("%"));
}

void FloatMutationController::minFactorChanged(int value){
    ui->lMinFactor->setText(QString::number(value / 100.0));
}
void FloatMutationController::maxFactorChanged(int value){
    ui->lMaxFactor->setText(QString::number(value / 100.0));
}
void FloatMutationController::minValueChanged(int value){
    ui->lMinValue->setText(QString::number(value));
}
void FloatMutationController::maxValueChanged(int value){
    ui->lMaxValue->setText(QString::number(value));
}
