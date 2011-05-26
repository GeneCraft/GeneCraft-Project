#include "fixationproperties.h"
#include <QDebug>
#include "ui_fixationproperties.h"
#include "fixation.h"
#include "bone.h"

FixationProperties::FixationProperties(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FixationProperties)
{
    ui->setupUi(this);
    fixation = 0;

    connect(this->ui->pbAddBone,SIGNAL(pressed()),this,SLOT(addBone()));
    connect(this->ui->pbFixInTheAir,SIGNAL(pressed()),this,SLOT(fixInTheAir()));
    connect(this->ui->pbSetPosition,SIGNAL(pressed()),this,SLOT(setPosition()));
}

FixationProperties::~FixationProperties()
{
    delete ui;
}

void FixationProperties::setFixation(Fixation *fixation)
{
    this->fixation = fixation;
}

void FixationProperties::addBone()
{
    if(fixation != 0)
    {
        btTransform local; local.setIdentity();

        Bone *bone = fixation->addBone(local.getRotation(),ui->leAddBoneRadius->text().toFloat(),
                                        ui->leAddBoneLenght->text().toFloat(),
                                        ui->leAddBoneEndFixRadius->text().toFloat(),
                                        btVector3(0,0,0),
                                        btVector3(0,0,0));

        bone->setup();
    }

    setFixation(fixation);
}

void FixationProperties::fixInTheAir()
{
    if(fixation != 0)
    {
        qDebug() << fixation->isFixedInTheAir();


        if(fixation->isFixedInTheAir())
            fixation->unfixInTheAir();
        else
            fixation->fixeInTheAir(btVector3(ui->leX->text().toFloat(),
                                             ui->leY->text().toFloat(),
                                             ui->leZ->text().toFloat()));
    }
}

void FixationProperties::setPosition()
{
    if(fixation != 0)
        fixation->getRigidBody()->getWorldTransform().setOrigin(btVector3(ui->leX->text().toFloat(),
                                                            ui->leY->text().toFloat(),
                                                            ui->leZ->text().toFloat()));
}

