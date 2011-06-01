#include "entitypropertiescontroller.h"
#include "ui_entitypropertiescontroller.h"
#include "entity.h"
#include "fixation.h"
#include "treeshape.h"
#include "bone.h"
#include <QVariant>
#include <QMetaType>

EntityPropertiesController::EntityPropertiesController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntityPropertiesController)
{
    ui->setupUi(this);

    connect(ui->twBodyTree,SIGNAL(itemClicked(QTreeWidgetItem *,int)),this,SLOT(itemClicked(QTreeWidgetItem *,int)));

    connect(this->ui->rbOutFrom_Random,SIGNAL(clicked()),this,SLOT(setOutFrom()));
    connect(this->ui->rbOutFrom_Brain,SIGNAL(clicked()),this,SLOT(setOutFrom()));
    connect(this->ui->rbOutFrom_Disable,SIGNAL(clicked()),this,SLOT(setOutFrom()));
    connect(this->ui->rbOutFrom_NormalPosition,SIGNAL(clicked()),this,SLOT(setOutFrom()));
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
    if(entity != 0 && entity->getShape() != 0 && entity->getShape()->getRoot() != 0)
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
    if(entity != 0 && entity->getShape() != 0 && entity->getShape()->getRoot() != 0)
       recurciveResetBonesProperties(entity->getShape()->getRoot());
}


void EntityPropertiesController::setEntity(Entity *entity, btRigidBody * selectedBody)
{
    this->entity = entity;

    ui->twBodyTree->clear();

    if(entity != 0)
    {
        ui->lName->setText(entity->getName());
        ui->lFamily->setText(entity->getFamily());

        if(entity->getShape() != 0 && entity->getShape()->getRoot() != 0)
            setupBodyTree(entity->getShape()->getRoot(),selectedBody);
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
        boneItem->setIcon(0,QIcon(":/img/icons/bone_and_fixation"));

        if(bone->getRigidBody() == selectedBody)
             ui->twBodyTree->setCurrentItem(boneItem);

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
        emit rigidBodySelected(fixItem->fixation->getRigidBody());
        return;
    }

    BoneTreeWidgetItem * boneItem = dynamic_cast<BoneTreeWidgetItem*>(item);
    if (boneItem )
    {
        emit rigidBodySelected(boneItem->bone->getRigidBody());
        return;
    }
}
