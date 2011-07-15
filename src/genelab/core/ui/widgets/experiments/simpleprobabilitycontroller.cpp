#include "simpleprobabilitycontroller.h"
#include "ui_simpleprobabilitycontroller.h"

#include "mutation/simpleprobabilitymutation.h"

#define PROBABILITY_PRECISION 10.0

using namespace GeneLabCore;

SimpleProbabilityController::SimpleProbabilityController(SimpleProbabilityMutation * mutation, QString name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimpleProbabilityController)
{
    ui->setupUi(this);

    this->mutation = mutation;

    ui->cbName->setText(name);

    connect(ui->cbName,SIGNAL(toggled(bool)),this,SLOT(nameToggled(bool)));
    connect(ui->sProbability,SIGNAL(valueChanged(int)),this,SLOT(probabilityChanged(int)));

    ui->sProbability->setValue(mutation->probability * PROBABILITY_PRECISION);
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
    ui->lProbabilty->setText(QString::number(value / PROBABILITY_PRECISION).append("%"));
}


