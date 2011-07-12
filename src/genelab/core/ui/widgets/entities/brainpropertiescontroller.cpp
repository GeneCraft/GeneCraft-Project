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

BrainPropertiesController::BrainPropertiesController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BrainPropertiesController), entity(NULL)
{
    ui->setupUi(this);

    // Brain
    connect(this->ui->sBrainPluggridSize,SIGNAL(valueChanged(int)),this,SLOT(setBrainSize()));
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
}

BrainPropertiesController::~BrainPropertiesController()
{
    delete ui;
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
        ui->sBrainPluggridSize->setValue(entity->getBrain()->getPlugGrid()->getSize());
        ui->lBrainPluggridSize->setText(QString::number(entity->getBrain()->getPlugGrid()->getSize()));
        //this->brainViz->setBrain(entity->getBrain());
        this->brainDezViz->setBrain(entity->getBrain());
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
    if(ui->lwSensors->selectedItems().size() > 0)
    {
        SensorListWidgetItem * sensorItem = dynamic_cast<SensorListWidgetItem*>(ui->lwSensors->selectedItems()[0]);

        if (sensorItem)
        {
            // TODO A REMETTRE !
            //emit rigidBodySelected(sensorItem->sensor->getFixation()->getRigidBody());
        }
    }
}

void BrainPropertiesController::setBrainSize()
{
    qDebug() << entity;

    if(entity){
        //int size = pow(2,ui->cbBrainSize->currentIndex() + 1);
        int size = ui->sBrainPluggridSize->value();
        ui->lBrainPluggridSize->setText(QString::number(ui->sBrainPluggridSize->value()));
        entity->getBrain()->getPlugGrid()->setSize(size);

        // update brain in inspectors (important to refresh neurons (QGraphicsRectItem))
        this->brainViz->setBrain(entity->getBrain());
        this->brainDezViz->setBrain(entity->getBrain());
    }
}

void BrainPropertiesController::clearSensors()
{
    while(ui->lwSensors->count() != 0)
    {
        SensorListWidgetItem * sensorItem = dynamic_cast<SensorListWidgetItem*>(ui->lwSensors->itemAt(0,0));

        if (sensorItem)
        {
            // remove the sensor in the fixation
            sensorItem->sensor->getFixation()->removeSensor(sensorItem->sensor);

            // delete sensor
            delete sensorItem->sensor;

            // delete list item
            ui->lwSensors->removeItemWidget(sensorItem);
            delete sensorItem;
        }
        else
            break;

    }

    // update ui TODO emit
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

    // update ui TODO emit
    setEntity(entity);
}

void BrainPropertiesController::computeMinimalOuts() {

    if(entity){
        entity->setToMinimalOuts();
    }
}
