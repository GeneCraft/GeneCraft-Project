#include "fixationproperties.h"

// Qt
#include <QDebug>
#include "ui_fixationproperties.h"

// Entity
#include "fixation.h"
#include "bone.h"
#include "entity.h"
#include "treeshape.h"

// Sensors
#include "positionsensor.h"
#include "gyroscopicsensor.h"
#include "accelerometersensor.h"

FixationProperties::FixationProperties(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FixationProperties)
{
    ui->setupUi(this);
    fixation = 0;

    connect(this->ui->pbAddBone,SIGNAL(pressed()),this,SLOT(addBone()));
    connect(this->ui->pbFixInTheAir,SIGNAL(pressed()),this,SLOT(fixInTheAir()));
    connect(this->ui->pbSetPosition,SIGNAL(pressed()),this,SLOT(setPosition()));
    connect(this->ui->pbAddSensor,SIGNAL(pressed()),this,SLOT(addSensor()));
}

FixationProperties::~FixationProperties()
{
    delete ui;
}

void FixationProperties::setFormTitle(QString title)
{
    this->ui->lFormTitle->setText(title);
}

void FixationProperties::setFixation(Fixation *fixation)
{
    this->fixation = fixation;

    // Bones
    this->ui->lwBones->clear();
    foreach(Bone *b, fixation->getBones())
        this->ui->lwBones->addItem(new BoneListWidgetItem(b));

    // Sensors
    this->ui->listSensors->clear();
    foreach(Sensor *s, fixation->getSensors())
        this->ui->listSensors->addItem(new SensorListWidgetItem(s));
}

void FixationProperties::addBone()
{
    if(fixation != 0)
    {
        btTransform local; local.setIdentity();

        Bone *bone = fixation->addBone(0,0,ui->leAddBoneRadius->text().toFloat(),
                                        ui->leAddBoneLenght->text().toFloat(),
                                        ui->leAddBoneEndFixRadius->text().toFloat(),
                                        btVector3(0,0,0),
                                        btVector3(0,0,0));

        bone->setup();

        emit rigidBodySelected(bone->getRigidBody());
    }

    setFixation(fixation);
}

void FixationProperties::fixInTheAir()
{
    if(fixation != 0)
    {
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

void FixationProperties::addSensor()
{
    Sensor *sensor = NULL;

    switch(this->ui->cbSensors->currentIndex())
    {
    case 0 : // Egocentric position sensor

        if(fixation->getEntity())
        {
            qDebug() << "BonePropertiesController::addSensor : Egocentric position sensor";
            sensor = new PositionSensor(fixation->getEntity()->getShape()->getRoot(),fixation);
        }
        break;

    case 1 : // Gyroscopic sensor

        if(fixation->getEntity())
        {
            qDebug() << "BonePropertiesController::addSensor : Gyroscopic sensor";
            sensor = new GyroscopicSensor(fixation);
        }
        break;

    case 2 : // Accelerometer sensor

        if(fixation->getEntity())
        {
            qDebug() << "BonePropertiesController::addSensor : Accelerometer sensor";
            // TODO get step time from sulation manager !!!
            sensor = new AccelerometerSensor(1000/60.0,fixation);
        }
        break;
    }

    if(sensor != NULL)
    {
        fixation->addSensor(sensor);
        setFixation(fixation); // refresh widget
    }
}
