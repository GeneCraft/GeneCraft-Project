#include "fixationproperties.h"

// Qt
#include <QDebug>
#include "ui_fixationproperties.h"

// Entity
#include "body/fixation.h"
#include "body/bone.h"
#include "entity.h"
#include "body/treeshape.h"

// Sensors
#include "sensors/positionsensor.h"
#include "sensors/gyroscopicsensor.h"
#include "sensors/accelerometersensor.h"

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
    connect(this->ui->pbSelectBone,SIGNAL(pressed()),this,SLOT(selectBone()));

    connect(this->ui->sRadius,SIGNAL(valueChanged(int)),this,SLOT(changeRadiusFromSlider(int)));
    connect(this->ui->pbResizeRadius,SIGNAL(pressed()),this,SLOT(changeRadiusFromButton()));
    connect(this->ui->pbRemoveBone,SIGNAL(pressed()),this,SLOT(removeSelectedBone()));

    connect(this->ui->pbDeleteSensor,SIGNAL(pressed()),this,SLOT(removeSelectedSensor()));
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

    // Radius
    disconnect(this->ui->sRadius,SIGNAL(valueChanged(int)),this,SLOT(changeRadiusFromSlider(int)));
    this->ui->sRadius->setValue(fixation->getRadius()*1000);
    connect(this->ui->sRadius,SIGNAL(valueChanged(int)),this,SLOT(changeRadiusFromSlider(int)));
    this->ui->leRadius->setText(QString::number(fixation->getRadius()));

    // Bones
    this->ui->lwBones->clear();
    foreach(Bone *b, fixation->getBones())
        this->ui->lwBones->addItem(new BoneListWidgetItem(b));

    // Sensors
    this->ui->lwSensors->clear();
    foreach(Sensor *s, fixation->getSensors())
        this->ui->lwSensors->addItem(new SensorListWidgetItem(s));
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
            fixation->fixeInTheAir(/*btVector3(ui->leX->text().toFloat(),
                                             ui->leY->text().toFloat(),
                                             ui->leZ->text().toFloat())*/);
    }
}

void FixationProperties::setPosition()
{
    if(fixation != 0)
        fixation->getRigidBody()->getWorldTransform().setOrigin(btVector3(ui->leX->text().toFloat(),
                                                            ui->leY->text().toFloat(),
                                                            ui->leZ->text().toFloat()));
}

void FixationProperties::selectBone()
{
    if(this->ui->lwBones->selectedItems().size() > 0)
    {
        BoneListWidgetItem * boneItem = dynamic_cast<BoneListWidgetItem*>(this->ui->lwBones->selectedItems().at(0));

        if (boneItem)
            emit rigidBodySelected(boneItem->bone->getRigidBody());
    }
}

void FixationProperties::addSensor()
{
    Sensor *sensor = NULL;

    switch(this->ui->cbSensors->currentIndex())
    {
    case 0 : // Egocentric position sensor

        if(fixation->getEntity())
            sensor = new PositionSensor(fixation->getEntity()->getShape()->getRoot(),fixation);
        break;

    case 1 : // Gyroscopic sensor

        if(fixation->getEntity())
            sensor = new GyroscopicSensor(fixation);
        break;

    case 2 : // Accelerometer sensor

        if(fixation->getEntity())
            // TODO get step time from sulation manager !!!
            sensor = new AccelerometerSensor(fixation);
        break;
    }

    if(sensor != NULL)
    {
        fixation->addSensor(sensor);
        setFixation(fixation); // refresh widget
    }
}

void FixationProperties::changeRadiusFromSlider(int value)
{
    fixation->setRadius(value/1000.0);
    this->ui->leRadius->setText(QString::number(value / 1000.0));
}

void FixationProperties::changeRadiusFromButton()
{
    fixation->setRadius(ui->leRadius->text().toDouble());
    setFixation(fixation); // update
}

void FixationProperties::removeSelectedBone()
{
    if(this->ui->lwBones->selectedItems().size() > 0)
    {
        BoneListWidgetItem * boneItem = dynamic_cast<BoneListWidgetItem*>(this->ui->lwBones->selectedItems().at(0));

        if (boneItem)
        {
            // update ui
            emit rigidBodySelected(NULL);

            // delete the bone
            delete boneItem->bone;
        }
    }
}

void FixationProperties::removeSelectedSensor()
{
    if(fixation)
    {
        if(this->ui->lwSensors->selectedItems().size() > 0)
        {
            SensorListWidgetItem * sensorItem = dynamic_cast<SensorListWidgetItem*>(this->ui->lwSensors->selectedItems().at(0));

            if (sensorItem)
            {
                // remove the sensor in the fixation
                fixation->removeSensor(sensorItem->sensor);

                // delete sensor
                delete sensorItem->sensor;

                // update ui TODO emit
                setFixation(fixation);

                // FIXME update entityPropertiesController !!!!!!!!!!!!!!!!!!!!!!!!!
                // because user could edit a deleted sensor !
            }
        }
    }
}
