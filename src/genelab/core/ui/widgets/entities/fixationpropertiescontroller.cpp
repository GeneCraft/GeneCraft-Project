#include "fixationpropertiescontroller.h"

// Qt
#include <QDebug>
#include "ui_fixationpropertiescontroller.h"

// Events
#include "events/inspectorsinputmanager.h"

// Entity
#include "body/fixation.h"
#include "body/bone.h"
#include "entity.h"
#include "body/treeshape.h"

// Sensors
#include "sensors/positionsensor.h"
#include "sensors/gyroscopicsensor.h"
#include "sensors/accelerometersensor.h"
#include "sensors/contactsensor.h"
#include "sensors/boxsmellsensor.h"
#include "sensors/distancesensor.h"

// Effectors
#include "effectors/grippereffector.h"
#include "effectors/flyingeffector.h"
#include "tools.h"
#include "bodyitems.h"

FixationPropertiesController::FixationPropertiesController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FixationPropertiesController), fixation(NULL)
{
    ui->setupUi(this);

    connect(this->ui->pbAddBone,SIGNAL(pressed()),this,SLOT(addBone()));
    connect(this->ui->pbFixInTheAir,SIGNAL(pressed()),this,SLOT(fixInTheAir()));
    connect(this->ui->pbAddSensor,SIGNAL(pressed()),this,SLOT(addSensor()));
    connect(this->ui->pbAddEffector,SIGNAL(pressed()),this,SLOT(addEffector()));

    connect(this->ui->pbSelectBone,SIGNAL(pressed()),this,SLOT(selectBone()));

    connect(this->ui->sRadius,SIGNAL(valueChanged(int)),this,SLOT(changeRadiusFromSlider(int)));
    connect(this->ui->pbResizeRadius,SIGNAL(pressed()),this,SLOT(changeRadiusFromButton()));

    connect(this->ui->pbRemoveBone,SIGNAL(pressed()),this,SLOT(removeSelectedBone()));
    connect(this->ui->pbDeleteSensor,SIGNAL(pressed()),this,SLOT(removeSelectedSensor()));
    connect(this->ui->pbDeleteEffector,SIGNAL(pressed()),this,SLOT(removeSelectedEffector()));

    this->setEnabled(false);
}

FixationPropertiesController::~FixationPropertiesController()
{
    delete ui;
}

void FixationPropertiesController::connectToInspectorInputManager(InspectorsInputManager *iim)
{
    // notifications
    connect(iim,SIGNAL(sFixationSelected(Fixation *)),this,SLOT(setFixation(Fixation *)));
    connect(iim,SIGNAL(sFixationDeleted(Fixation *)),this,SLOT(fixationDeleted(Fixation *)),Qt::DirectConnection);

    connect(iim,SIGNAL(sBoneSelected(Bone *)),this,SLOT(boneSelected(Bone *)));
    connect(iim,SIGNAL(sEntityDeleted(Entity *)),this,SLOT(entityDeleted(Entity *)),Qt::DirectConnection);

    // emission
    connect(this,SIGNAL(sBoneDeleted(Bone *)),iim,SLOT(boneDeleted(Bone *)),Qt::DirectConnection);
    connect(this,SIGNAL(sBoneSelected(Bone *)),iim,SLOT(boneSelected(Bone *)));
    connect(this,SIGNAL(sFixationUpdated(Fixation*)),iim,SLOT(fixationUpdated(Fixation*)));
//    //connect(this,SIGNAL(sBoneUpdated(Bone *)),iim,SLOT(boneUpdated(Bone*)));
}

void FixationPropertiesController::fixationDeleted(Fixation * fixation){
    if(fixation == this->fixation)
        setFixation(NULL);
}

void FixationPropertiesController::entityDeleted(Entity *) {

    setFixation(NULL);
}

void FixationPropertiesController::boneSelected(Bone *bone)
{
    setFixation(bone->getEndFixation());
}


void FixationPropertiesController::setFixation(Fixation *fixation)
{
    this->fixation = fixation;

    if(fixation){

        // Radius
        disconnect(this->ui->sRadius,SIGNAL(valueChanged(int)),this,SLOT(changeRadiusFromSlider(int)));
        this->ui->sRadius->setValue(fixation->getRadius()*1000);
        connect(this->ui->sRadius,SIGNAL(valueChanged(int)),this,SLOT(changeRadiusFromSlider(int)));
        this->ui->leRadius->setText(QString::number(fixation->getRadius()));

        // Bones
        this->ui->lwBones->clear(); // TODO delete because of new !
        foreach(Bone *b, fixation->getBones())
            this->ui->lwBones->addItem(new BoneListWidgetItem(b));

        // Sensors
        this->ui->lwSensors->clear(); // TODO delete because of new !
        foreach(Sensor *s, fixation->getSensors())
            this->ui->lwSensors->addItem(new SensorListWidgetItem(s));

        // Sensors
        this->ui->lwEffectors->clear(); // TODO delete because of new !
        foreach(Effector *f, fixation->getEffectors())
            this->ui->lwEffectors->addItem(new EffectorListWidgetItem(f));

        this->setEnabled(true);
    }
    else {
        this->setEnabled(false);
    }

}

void FixationPropertiesController::addBone()
{
    if(fixation != 0)
    {
        btTransform local; local.setIdentity();

        Bone *bone = fixation->addBone(0,0,0.2,
                                        0.8,
                                        0.2,
                                        btVector3(0,0,0),
                                        btVector3(0,0,0));

        bone->setup();

        emit rigidBodySelected(bone->getRigidBody());
    }

    setFixation(fixation);
}

void FixationPropertiesController::fixInTheAir()
{
    if(fixation)
    {
        if(fixation->isFixedInTheAir())
            fixation->unfixInTheAir();
        else
            fixation->fixeInTheAir(/*btVector3(ui->leX->text().toFloat(),
                                             ui->leY->text().toFloat(),
                                             ui->leZ->text().toFloat())*/);
    }
}

void FixationPropertiesController::selectBone()
{
    if(this->ui->lwBones->selectedItems().size() > 0)
    {
        BoneListWidgetItem * boneItem = dynamic_cast<BoneListWidgetItem*>(this->ui->lwBones->selectedItems().at(0));

        if (boneItem)
            emit sBoneSelected(boneItem->bone);
    }
}

void FixationPropertiesController::addSensor()
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
            sensor = new AccelerometerSensor(fixation);
        break;

    case 3 : // Accelerometer sensor

        if(fixation->getEntity())
            sensor = new ContactSensor(fixation);
        break;

    case 4 : // Box smell sensor

        if(fixation->getEntity())
            sensor = new BoxSmellSensor(fixation);
        break;

    case 5 : // Distance sensor

        if(fixation->getEntity())
            sensor = new DistanceSensor(fixation, Tools::random(-SIMD_PI,SIMD_PI), Tools::random(-SIMD_PI,SIMD_PI));
        break;
    }


    if(sensor != NULL)
    {
        fixation->addSensor(sensor);

        // refresh ui
        setFixation(fixation);
        emit sFixationUpdated(fixation);
    }
}

void FixationPropertiesController::addEffector()
{
    Effector *effector = NULL;

    switch(this->ui->cbEffectors->currentIndex())
    {
    case 0 : // Gripper

        if(fixation->getEntity())
            effector = new GripperEffector(fixation);
        break;
    case 1 : // Flying

        if(fixation->getEntity())
            effector = new FlyingEffector(fixation);
        break;
    }

    if(effector != NULL)
    {
        fixation->addEffector(effector);

        // refresh ui
        setFixation(fixation);
        emit sFixationUpdated(fixation);
    }
}

void FixationPropertiesController::changeRadiusFromSlider(int value)
{
    fixation->setRadius(value/1000.0);
    this->ui->leRadius->setText(QString::number(value / 1000.0));
}

void FixationPropertiesController::changeRadiusFromButton()
{
    fixation->setRadius(ui->leRadius->text().toDouble());
    setFixation(fixation); // update
}

void FixationPropertiesController::removeSelectedBone()
{
    if(this->ui->lwBones->selectedItems().size() > 0)
    {
        BoneListWidgetItem * boneItem = dynamic_cast<BoneListWidgetItem*>(this->ui->lwBones->selectedItems().at(0));

        if (boneItem)
        {
            // delete the bone
            this->fixation->removeBone(boneItem->bone);
            boneItem->bone->remove();

            // update ui
            emit sBoneDeleted(boneItem->bone);
            emit rigidBodySelected(NULL);

            delete boneItem->bone;

            setFixation(fixation);
        }
    }    
}

void FixationPropertiesController::removeSelectedSensor()
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

                // update ui
                setFixation(fixation);
                emit sFixationUpdated(fixation);
            }
        }
    }
}

void FixationPropertiesController::removeSelectedEffector()
{
    if(fixation)
    {
        if(this->ui->lwEffectors->selectedItems().size() > 0)
        {
            EffectorListWidgetItem * effectorItem = dynamic_cast<EffectorListWidgetItem*>(this->ui->lwEffectors->selectedItems().at(0));

            if (effectorItem)
            {
                // remove the effector in the fixation
                fixation->removeEffector(effectorItem->effector);

                // delete sensor
                delete effectorItem->effector;

                // update ui
                setFixation(fixation);
                emit sFixationUpdated(fixation);
            }
        }
    }
}

