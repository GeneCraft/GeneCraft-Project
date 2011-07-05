#include "entitypropertiescontroller.h"
#include "ui_entitypropertiescontroller.h"

#include <QVariant>
#include <QMetaType>
#include <QLayout>

#include "entity.h"
#include "body/fixation.h"
#include "body/treeshape.h"
#include "body/bone.h"
#include "pluggridvisualizer.h"
#include "pluggriddesignvisualizer.h"
#include "effectors/effector.h"
#include "brain/brainpluggrid.h"
#include "effectors/rotationalmotorseffector.h"

EntityPropertiesController::EntityPropertiesController(QWidget *parent) :
    QWidget(parent), ui(new Ui::EntityPropertiesController), entity(NULL)
{
    ui->setupUi(this);

    // Bones
    connect(ui->twBodyTree,SIGNAL(itemClicked(QTreeWidgetItem *,int)),this,SLOT(itemClicked(QTreeWidgetItem *,int)));

    // Motors outputs
    connect(this->ui->rbOutFrom_Random,SIGNAL(clicked()),this,SLOT(setOutFrom()));
    connect(this->ui->rbOutFrom_Brain,SIGNAL(clicked()),this,SLOT(setOutFrom()));
    connect(this->ui->rbOutFrom_Disable,SIGNAL(clicked()),this,SLOT(setOutFrom()));
    connect(this->ui->rbOutFrom_NormalPosition,SIGNAL(clicked()),this,SLOT(setOutFrom()));

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

    // Statistics headers
    connect(this->ui->pbResetAllStats,SIGNAL(clicked()),this,SLOT(resetAllStats()));
    connect(this->ui->pbResetSelectedStat,SIGNAL(clicked()),this,SLOT(resetSelectedStat()));

    ui->twStats->setColumnWidth(0,200);
    ui->twStats->setColumnWidth(1,70);
    ui->twStats->setColumnWidth(2,60);

    // Statistics refresh timer
    statsTimer = new QTimer();
    statsTimer->setInterval(1000/5); // by ms
    connect(statsTimer, SIGNAL(timeout()), this, SLOT(updateStats()));
    statsTimer->start();
}

EntityPropertiesController::~EntityPropertiesController()
{
    delete ui;
}

void setupBonesProperties(Fixation *fixation, int action)
{
    QList<Bone *> bones = fixation->getBones();
    for(int i=0;i<bones.size();++i)
    {
        Bone *bone = bones.at(i);

        switch(action)
        {
            case 0:
                bone->disableMotors();
            break;
            case 1:
                bone->setBrainMotors();
            break;
            case 2:
                bone->setRandomMotors();
            break;
            case 3:
                bone->setNormalPositionMotors();
            break;
        }

        setupBonesProperties(bone->getEndFixation(),action);
    }
}

void EntityPropertiesController::setOutFrom()
{
    if(entity && entity->getShape() != 0 && entity->getShape()->getRoot() != 0)
    {
        if(ui->rbOutFrom_Random->isChecked())
            setupBonesProperties(entity->getShape()->getRoot(),2);
        else if(ui->rbOutFrom_Brain->isChecked())
            setupBonesProperties(entity->getShape()->getRoot(),1);
        else if(ui->rbOutFrom_Disable->isChecked())
            setupBonesProperties(entity->getShape()->getRoot(),0);
        else if(ui->rbOutFrom_NormalPosition->isChecked())
            setupBonesProperties(entity->getShape()->getRoot(),3);

    }
}

void recurciveResetBonesProperties(Fixation *fixation)
{
    QList<Bone *> bones = fixation->getBones();
    for(int i=0;i<bones.size();++i)
    {
        Bone *bone = bones.at(i);
        bone->disableMotors();
        recurciveResetBonesProperties(bone->getEndFixation());
    }
}

void EntityPropertiesController::resetBonesProperties()
{
    if(entity && entity->getShape() != 0 && entity->getShape()->getRoot() != 0)
       recurciveResetBonesProperties(entity->getShape()->getRoot());
}

// Used to clear a recurcively QTreeWidgetItem
void clearTreeWidgetItem(QTreeWidgetItem * item)
{
    QTreeWidgetItem * child;
    while(item->childCount()) {
        child = item->child(0);
        clearTreeWidgetItem(child);
        item->removeChild(child);
        delete child;
    }
}

// Used to clear a QTreeWidget
void clearTreeWidget(QTreeWidget * tree)
{
    QTreeWidgetItem * topItem;
    while(tree->topLevelItemCount()) {

        topItem = tree->topLevelItem(0);

        clearTreeWidgetItem(topItem);
        tree->removeItemWidget(topItem,0);

        delete topItem;
    }
}

void EntityPropertiesController::setEntity(Entity *entity, btRigidBody * selectedBody)
{
    this->entity = entity;

    if(entity)
    {
        // Origins
        ui->lName->setText(entity->getName());
        ui->lFamily->setText(entity->getFamily());
        ui->lGeneration->setText(QString::number(entity->getGeneration()));

        // Statistics
        clearTreeWidget(ui->twStats);
        QMapIterator<QString, Statistic *> iStats(entity->getStatistics());
        iStats.toBack();
        while (iStats.hasPrevious()) {
            Statistic * stat = iStats.previous().value();
            ui->twStats->insertTopLevelItem(0,new StatisticTreeWidgetItem(stat));
        }
        updateStats();

        // -- Bones --

        // clear recucively
        clearTreeWidget(this->ui->twBodyTree);

        //  fill list
        if(entity->getShape() != 0 && entity->getShape()->getRoot() != 0)
            setupBodyTree(entity->getShape()->getRoot(),selectedBody);

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
        this->brainViz->setBrain(entity->getBrain());
        this->brainDezViz->setBrain(entity->getBrain());
    }
}

void EntityPropertiesController::setupBodyTree(Fixation * fixation, btRigidBody * selectedBody, QTreeWidgetItem *rootItem)
{
    QList<Bone *> bones = fixation->getBones();

    if(rootItem == 0)
    {
        rootItem = new FixationTreeWidgetItem(fixation);
        rootItem->setText(0,QString("Root fixation : ").append(QString().setNum(bones.size()).append(" bone(s)")));
        rootItem->setIcon(0,QIcon(":/img/icons/fixation"));
        ui->twBodyTree->addTopLevelItem(rootItem);
    }
    else
    {
//        rootItem->setText(0,QString("Fixation : ").append(QString().setNum(bones.size()).append(" bone(s)")));
//        rootItem->setIcon(0,QIcon(":/img/icons/fixation"));
    }

    Bone *bone;
    for(int i=0;i<bones.size();++i)
    {
        bone = bones.at(i);

        QTreeWidgetItem *boneItem = new BoneTreeWidgetItem(rootItem,bone);
        boneItem->setText(0,QString("Bone + Fix")); //.append(QString().setNum(i)));

        if(bone->getRigidBody() == selectedBody) {
             this->brainDezViz->setSelectedSensors(bone->getEndFixation()->getSensors());
             ui->twBodyTree->setCurrentItem(boneItem);
        }

//        QTreeWidgetItem *fixItem = new FixationTreeWidgetItem(boneItem,bone->getEndFixation());
//        if(bone->getEndFixation()->getRigidBody() == selectedBody)
//             ui->twBodyTree->setCurrentItem(fixItem);

        setupBodyTree(bones.at(i)->getEndFixation(),selectedBody,boneItem);
    }
}

void EntityPropertiesController::itemClicked(QTreeWidgetItem * item, int column)
{
    FixationTreeWidgetItem * fixItem = dynamic_cast<FixationTreeWidgetItem*>(item);
    if (fixItem)
    {
        this->brainDezViz->setSelectedSensors(fixItem->fixation->getSensors());
        emit rigidBodySelected(fixItem->fixation->getRigidBody());
        return;
    }

    BoneTreeWidgetItem * boneItem = dynamic_cast<BoneTreeWidgetItem*>(item);
    if (boneItem )
    {
        this->brainDezViz->setSelectedSensors(boneItem->bone->getEndFixation()->getSensors());
        emit rigidBodySelected(boneItem->bone->getRigidBody());
        return;
    }
}

void EntityPropertiesController::setBrainViz(PlugGridVisualizer *brainViz) {
       this->brainViz = brainViz;
       this->ui->tabBrain->layout()->addWidget(brainViz);
}

void EntityPropertiesController::setBrainDesignViz(PlugGridDesignVisualizer *brainDezViz) {
       this->brainDezViz = brainDezViz;
       this->ui->tabBrainStruct->layout()->addWidget(brainDezViz);
}

void EntityPropertiesController::selectSensorFixation()
{
    if(ui->lwSensors->selectedItems().size() > 0)
    {
        SensorListWidgetItem * sensorItem = dynamic_cast<SensorListWidgetItem*>(ui->lwSensors->selectedItems()[0]);

        if (sensorItem)
        {
            emit rigidBodySelected(sensorItem->sensor->getFixation()->getRigidBody());
        }
    }
}

void EntityPropertiesController::setBrainSize()
{
    //int size = pow(2,ui->cbBrainSize->currentIndex() + 1);
    int size = ui->sBrainPluggridSize->value();
    ui->lBrainPluggridSize->setText(QString::number(ui->sBrainPluggridSize->value()));
    entity->getBrain()->getPlugGrid()->setSize(size);

    // update brain in inspectors (important to refresh neurons (QGraphicsRectItem))
    this->brainViz->setBrain(entity->getBrain());
    this->brainDezViz->setBrain(entity->getBrain());
}

void EntityPropertiesController::clearSensors()
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


void EntityPropertiesController::clearEffectors()
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

void EntityPropertiesController::computeMinimalOuts() {

    if(entity){

        entity->setToMinimalOuts();
    }

}

void EntityPropertiesController::updateStats(){

    if(entity){
        for(int i=0; i<ui->twStats->topLevelItemCount(); ++i) {
            ((StatisticTreeWidgetItem *) ui->twStats->topLevelItem(i))->update();
        }
    }
}

void EntityPropertiesController::resetAllStats(){
    if(entity){
        for(int i=0; i<ui->twStats->topLevelItemCount(); ++i) {
            ((StatisticTreeWidgetItem *) ui->twStats->topLevelItem(i))->stat->reset();
        }
    }
}

void EntityPropertiesController::resetSelectedStat(){
    if(entity){
        if(ui->twStats->currentItem())
            ((StatisticTreeWidgetItem *) ui->twStats->currentItem())->stat->reset();
    }
}
