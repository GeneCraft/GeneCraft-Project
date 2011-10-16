#include "brainpropertiescontroller.h"
#include "ui_brainpropertiescontroller.h"

#include "entity.h"
#include "body/fixation.h"
#include "body/bone.h"
#include "sensors/sensor.h"
#include "effectors/effector.h"
#include "effectors/rotationalmotorseffector.h"
#include "brain/brainpluggrid.h"
#include "ui/widgets/entities/pluggridvisualizer.h"
#include "ui/widgets/entities/pluggriddesignvisualizer.h"
#include "events/inspectorsinputmanager.h"

BrainPropertiesController::BrainPropertiesController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BrainPropertiesController), entity(NULL)
{
    ui->setupUi(this);

    // Brain
    connect(this->ui->sBrainFrequency,SIGNAL(valueChanged(int)),this,SLOT(setBrainFrequency()));
    QLayout* layoutBrain = new QBoxLayout(QBoxLayout::TopToBottom);
    this->ui->tabBrain->setLayout(layoutBrain);
    QLayout* layoutBrainD = new QBoxLayout(QBoxLayout::TopToBottom);
    this->ui->tabBrainStruct->setLayout(layoutBrainD);

    // Sensors
    connect(this->ui->pbSelectFixation,SIGNAL(clicked()),this,SLOT(selectSensorFixation()));
    connect(this->ui->pbClearSensors,SIGNAL(clicked()),this,SLOT(clearSensors()));

    // Effectors
    connect(this->ui->pbClearEffectors,SIGNAL(clicked()),this,SLOT(clearEffectors()));
    connect(this->ui->pbMinimalOuts,SIGNAL(clicked()),this,SLOT(computeMinimalOuts()));

    this->setEnabled(false);
}

BrainPropertiesController::~BrainPropertiesController()
{
    delete ui;
}

void BrainPropertiesController::connectToInspectorInputManager(InspectorsInputManager *iim)
{
    // notifications
    connect(iim,SIGNAL(sEntitySelected(Entity*)),this,SLOT(setEntity(Entity *)));
    connect(iim,SIGNAL(sEntityUpdated(Entity*)),this,SLOT(entityUpdated(Entity *)));
    connect(iim,SIGNAL(sEntityDeleted(Entity *)),this,SLOT(entityDeleted(Entity *)),Qt::DirectConnection);
    connect(iim,SIGNAL(sFixationUpdated(Fixation*)),this,SLOT(refresh()));
    connect(iim,SIGNAL(sFixationDeleted(Fixation*)),this,SLOT(refresh()),Qt::DirectConnection);
    connect(iim,SIGNAL(sBoneDeleted(Bone*)),this,SLOT(refresh()),Qt::DirectConnection);
    connect(iim,SIGNAL(sSensorsSelected(QList<Sensor*>)),this,SLOT(sensorsSelected(QList<Sensor*>)));

    // emissions
    connect(this,SIGNAL(sEntityUpdated(Entity *)),iim,SLOT(entityUpdated(Entity *)));
    connect(this,SIGNAL(sFixationUpdated(Fixation*)),iim,SLOT(fixationUpdated(Fixation*)));
    connect(this,SIGNAL(sFixationSelected(Fixation*)),iim,SLOT(fixationSelected(Fixation*)));
    connect(this,SIGNAL(sBoneSelected(Bone*)),iim,SLOT(boneSelected(Bone*)));
}

void BrainPropertiesController::entityUpdated(Entity *entity){

    if(this->entity == entity)
        setEntity(entity);
}

void BrainPropertiesController::entityDeleted(Entity *entity){

    if(this->entity == entity)
        setEntity(NULL);
}

void BrainPropertiesController::refresh()
{
    setEntity(entity);
}

void BrainPropertiesController::sensorsSelected(QList<Sensor *> sensors){
    brainDezViz->setSelectedSensors(sensors);
}

void BrainPropertiesController::setEntity(Entity *entity)
{
    this->entity = entity;

    if(entity){

        // -- Sensors --

        // clear list
        while(this->ui->lwSensors->count())
            delete this->ui->lwSensors->itemAt(0,0);

        // fill list
        int nbrBrainIn = 0;
        foreach(Sensor *s, entity->getSensors()) {
            this->ui->lwSensors->addItem(new SensorListWidgetItem(s));
            nbrBrainIn += s->getInputs().size();
        }
        this->ui->lNbrBrainInputs->setText(QString::number(nbrBrainIn));
        this->ui->lNbrSensors->setText(QString::number(entity->getSensors().size()));

        // -- Effectors --

        // clear list
        while(this->ui->lwEffectors->count())
            delete this->ui->lwEffectors->itemAt(0,0);

        // fill list
        int nbrBrainOut = 0;
        foreach(Effector *e, entity->getEffectors()) {
            this->ui->lwEffectors->addItem(new EffectorListWidgetItem(e));
            nbrBrainOut += e->getOutputs().size();
        }
        this->ui->lNbrBrainOutputs->setText(QString::number(nbrBrainOut));
        this->ui->lNbrEffectors->setText(QString::number(entity->getEffectors().size()));

        // Brain
        ui->sBrainFrequency->setValue(entity->getBrain()->getFrequency());
        ui->lBrainFrequency->setText(QString::number(entity->getBrain()->getFrequency()));
        this->brainViz->setBrain(entity->getBrain());
        this->brainDezViz->setBrain(entity->getBrain());

        this->setEnabled(true);
    }
    else {

        this->brainViz->setBrain(NULL);
        this->brainDezViz->setBrain(NULL);

        this->setEnabled(false);
    }
}

// TODO MOUAIS... ON PEUT FAIRE MIEUX, NON ?
void BrainPropertiesController::setBrainViz(PlugGridVisualizer *brainViz) {
       this->brainViz = brainViz;
       this->ui->tabBrain->layout()->addWidget(brainViz);
}

// TODO MOUAIS... ON PEUT FAIRE MIEUX, NON ?
void BrainPropertiesController::setBrainDesignViz(PlugGridDesignVisualizer *brainDezViz) {
       this->brainDezViz = brainDezViz;
       this->ui->tabBrainStruct->layout()->addWidget(brainDezViz);
}

void BrainPropertiesController::selectSensorFixation()
{
    if(ui->lwSensors->currentItem()) {
        SensorListWidgetItem * sensorItem = (SensorListWidgetItem*) ui->lwSensors->currentItem();

        // root fixation
        if(sensorItem->sensor->getFixation()->getParentBone())
            emit sBoneSelected(sensorItem->sensor->getFixation()->getParentBone());
        else
            emit sFixationSelected(sensorItem->sensor->getFixation());
    }
}

void BrainPropertiesController::setBrainFrequency()
{
    if(entity){
        entity->getBrain()->setFrequency(ui->sBrainFrequency->value());
        ui->lBrainFrequency->setText(QString::number(entity->getBrain()->getFrequency()));
    }
}

void BrainPropertiesController::clearSensors()
{
    while(ui->lwSensors->count() != 0)
    {
        SensorListWidgetItem * sensorItem = dynamic_cast<SensorListWidgetItem*>(ui->lwSensors->itemAt(0,0));

        if (sensorItem)
        {
            Fixation *fix = sensorItem->sensor->getFixation();

            // remove the sensor in the fixation
            fix->removeSensor(sensorItem->sensor);

            // delete sensor
            delete sensorItem->sensor;

            // delete list item
            ui->lwSensors->removeItemWidget(sensorItem);
            delete sensorItem;

            emit sFixationUpdated(fix);
        }
        else
            break;

    }

    // update
    setEntity(entity);
}


void BrainPropertiesController::clearEffectors()
{
    EffectorListWidgetItem * effectorItem;
    RotationalMotorsEffector * motorEffector;
    for(int iEffectors=0; iEffectors < ui->lwEffectors->count(); ++iEffectors)
    {
        effectorItem = dynamic_cast<EffectorListWidgetItem*>(ui->lwEffectors->item(iEffectors));

        if(effectorItem)
        {
            // TODO if type == RotationalMotorsEffector
            motorEffector = dynamic_cast<RotationalMotorsEffector*>(effectorItem->effector);

            if(motorEffector){
                for(int i=0;i<3;++i)
                    motorEffector->getBone()->disconnectMotor(i);
            }
            else
                break;
        }
        else
            break;
    }

    // update
    setEntity(entity);
}

void BrainPropertiesController::computeMinimalOuts() {

    if(entity){
        entity->setToMinimalOuts();

        // update
        setEntity(entity);
    }
}
