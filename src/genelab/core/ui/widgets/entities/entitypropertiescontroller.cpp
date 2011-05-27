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

    connect(ui->pbRandomBonesProperties,SIGNAL(pressed()),this,SLOT(setRandomBonesProperties()));
    connect(ui->pbResetBonesProperties,SIGNAL(pressed()),this,SLOT(resetBonesProperties()));
    connect(ui->twBodyTree,SIGNAL(itemClicked(QTreeWidgetItem *,int)),this,SLOT(itemClicked(QTreeWidgetItem *,int)));
}

EntityPropertiesController::~EntityPropertiesController()
{
    delete ui;
}

void setupRandomBonesProperties(Fixation *fixation)
{
    QList<Bone *> bones = fixation->getBones();
    for(int i=0;i<bones.size();++i)
    {
        Bone *bone = bones.at(i);
        bone->setRandomMotors();
        setupRandomBonesProperties(bone->getEndFixation());
    }
}

void EntityPropertiesController::setRandomBonesProperties()
{
    if(entity != 0 && entity->getShape() != 0 && entity->getShape()->getRoot() != 0)
       setupRandomBonesProperties(entity->getShape()->getRoot());
}

void recurciveResetBonesProperties(Fixation *fixation)
{
    QList<Bone *> bones = fixation->getBones();
    for(int i=0;i<bones.size();++i)
    {
        Bone *bone = bones.at(i);
        bone->resetMotors();
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
        rootItem->setText(0,QString("root fixation : ").append(QString().setNum(bones.size()).append(" bone(s)")));
        rootItem->setIcon(0,QIcon(":/img/icons/fixation"));
        ui->twBodyTree->addTopLevelItem(rootItem);
    }
    else
    {
        rootItem->setText(0,QString("fixation : ").append(QString().setNum(bones.size()).append(" bone(s)")));
        rootItem->setIcon(0,QIcon(":/img/icons/fixation"));
    }

    Bone *bone;
    for(int i=0;i<bones.size();++i)
    {
        bone = bones.at(i);

        QTreeWidgetItem *boneItem = new BoneTreeWidgetItem(rootItem,bone);
        boneItem->setText(0,QString("bone ").append(QString().setNum(i)));
        boneItem->setIcon(0,QIcon(":/img/icons/bone"));

        qDebug() << "1";
        if(bone->getRigidBody() == selectedBody)
             ui->twBodyTree->setCurrentItem(boneItem);

        QTreeWidgetItem *fixItem = new FixationTreeWidgetItem(boneItem,bone->getEndFixation());
        if(bone->getEndFixation()->getRigidBody() == selectedBody)
             ui->twBodyTree->setCurrentItem(fixItem);

        setupBodyTree(bones.at(i)->getEndFixation(),selectedBody,fixItem);
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
