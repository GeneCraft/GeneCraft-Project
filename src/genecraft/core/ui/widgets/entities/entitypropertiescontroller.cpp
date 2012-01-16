/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

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
#include "statistics/statisticsstorage.h"
#include "uitools.h"
#include "events/inspectorsinputmanager.h"
#include "ressources/ressource.h"

EntityPropertiesController::EntityPropertiesController(QWidget *parent) :
    QWidget(parent), ui(new Ui::EntityPropertiesController), entity(NULL)
{
    ui->setupUi(this);

    // Bones
    connect(ui->twBodyTree,SIGNAL(itemClicked(QTreeWidgetItem *,int)),this,SLOT(itemClicked(QTreeWidgetItem *,int)));

    // Motors outputs
    connect(this->ui->pbOutsFromNormalPosition,SIGNAL(clicked()),this,SLOT(setOutFromNormalPosition()));
    connect(this->ui->pbOutsFromNone,SIGNAL(clicked()),this,SLOT(setOutFromNone()));
    connect(this->ui->pbOutsFromBrain,SIGNAL(clicked()),this,SLOT(setOutFromBrain()));
    connect(this->ui->pbOutsFromRandom,SIGNAL(clicked()),this,SLOT(setOutFromRandom()));
    connect(this->ui->pbViewGenotype,SIGNAL(clicked()),this,SLOT(viewGenotype()));

    connect(this->ui->leName,SIGNAL(textChanged(QString)),this,SLOT(saveOrigins()));
    connect(this->ui->leFamily,SIGNAL(textChanged(QString)),this,SLOT(saveOrigins()));

    this->setEnabled(false);
}

EntityPropertiesController::~EntityPropertiesController()
{
    delete ui;
}

void EntityPropertiesController::saveOrigins() {
    if(entity) {
        entity->setName(ui->leName->text());
        entity->setFamily(ui->leFamily->text());
    }
}

void EntityPropertiesController::connectToInspectorInputManager(InspectorsInputManager *iim)
{
    // notifications
    //connect(iim,SIGNAL(sEntitySelected(Entity*)),this,SLOT(setEntity(Entity *)));
    connect(iim,SIGNAL(sEntityUpdated(Entity*)),this,SLOT(entityUpdated(Entity *)));
    connect(iim,SIGNAL(sEntityDeleted(Entity *)),this,SLOT(entityDeleted(Entity *)),Qt::DirectConnection);

    // fixation
    connect(iim,SIGNAL(sFixationSelected(Fixation*)),this,SLOT(fixationSelected(Fixation *)));
    connect(iim,SIGNAL(sFixationDeleted(Fixation*)),this,SLOT(shapeUpdated()));

    // bone
    connect(iim,SIGNAL(sBoneSelected(Bone*)),this,SLOT(boneSelected(Bone *)));
    connect(iim,SIGNAL(sBoneAdded(Bone*)),this,SLOT(shapeUpdated()));
    connect(iim,SIGNAL(sBoneDeleted(Bone*)),this,SLOT(shapeUpdated()));

    // emissions
    connect(this,SIGNAL(sSensorsSelected(QList<Sensor*>)),iim,SLOT(sensorsSelected(QList<Sensor*>)));
    connect(this,SIGNAL(sFixationSelected(Fixation*)),iim,SLOT(fixationSelected(Fixation*)));
    connect(this,SIGNAL(sBoneSelected(Bone *)),iim,SLOT(boneSelected(Bone *)));
    //connect(this,SIGNAL(sBoneAdded(Bone *)),iim,SLOT(boneAdded(Bone*)));
    //connect(this,SIGNAL(sBoneDeleted(Bone*)),iim,SLOT(boneDeleted(Bone*)));
}

void EntityPropertiesController::entityUpdated(Entity *entity){

    if(this->entity == entity)
        setEntity(entity);
}

void EntityPropertiesController::entityDeleted(Entity *entity){

    if(this->entity == entity)
        setEntity(NULL);
}

void EntityPropertiesController::shapeUpdated(){

    if(entity) // refresh only if necessary...
        setEntity(entity);
}

void EntityPropertiesController::boneSelected(Bone *bone)
{
    setEntity(bone->getEntity(),bone);
}

void EntityPropertiesController::fixationSelected(Fixation *fixation)
{
    setEntity(fixation->getEntity());
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

void EntityPropertiesController::setOutFrom(int outsFrom)
{
    if(entity && entity->getShape() != 0 && entity->getShape()->getRoot() != 0)
        setupBonesProperties(entity->getShape()->getRoot(),outsFrom);
}

void EntityPropertiesController::setOutFromNormalPosition(){
    setOutFrom(3);
}

void EntityPropertiesController::setOutFromNone(){
    setOutFrom(0);
}

void EntityPropertiesController::setOutFromBrain(){
    setOutFrom(1);
}

void EntityPropertiesController::setOutFromRandom(){
    setOutFrom(2);
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

void EntityPropertiesController::setEntity(Entity *entity, Bone *bone)
{
    this->entity = entity;

    if(entity)
    {
        // Origins
        disconnect(this->ui->leName,SIGNAL(textChanged(QString)),this,SLOT(saveOrigins()));
        disconnect(this->ui->leFamily,SIGNAL(textChanged(QString)),this,SLOT(saveOrigins()));

        ui->leName->setText(entity->getName());
        ui->leFamily->setText(entity->getFamily());

        connect(this->ui->leName,SIGNAL(textChanged(QString)),this,SLOT(saveOrigins()));
        connect(this->ui->leFamily,SIGNAL(textChanged(QString)),this,SLOT(saveOrigins()));

        ui->lGeneration->setText(QString::number(entity->getGeneration()));
        ui->pteGenotype->clear();

        // Bones
        UITools::clearTreeWidget(this->ui->twBodyTree);
        if(entity->getShape() != 0 && entity->getShape()->getRoot() != 0)
            setupBodyTree(entity->getShape()->getRoot(),bone);

        this->setEnabled(true);
    }
    else
        this->setEnabled(false);
}

void EntityPropertiesController::setupBodyTree(Fixation * fixation, Bone *selectedBone, QTreeWidgetItem *rootItem)
{
    QList<Bone *> bones = fixation->getBones();

    if(rootItem == 0)
    {
        rootItem = new FixationTreeWidgetItem(fixation);
        rootItem->setText(0,QString("Root fixation [").append(QString().setNum(bones.size()).append("]")));
        rootItem->setIcon(0,QIcon(":/img/icons/fixation"));
        ui->twBodyTree->addTopLevelItem(rootItem);
    }
    else
    {
//        rootItem->setText(0,QString("Fixation : ").append(QString().setNum(bones.size()).append(" bone(s)")));
//        rootItem->setIcon(0,QIcon(":/img/icons/fixation"));
    }

    foreach(Bone *bone, bones) {

        QTreeWidgetItem *boneItem = new BoneTreeWidgetItem(rootItem,bone);
        //boneItem->setText(0,QString("Bone + Fix")); //.append(QString().setNum(i)));

        QString txt = "Bone + Fix";
        if(bone->getEndFixation()->getBones().size() > 0)
            txt.append(" [").append(QString().setNum(bone->getEndFixation()->getBones().size()).append("]"));
        boneItem->setText(0,txt);

        if(bone == selectedBone) {
             //emit sSensorsSelected(bone->getEndFixation()->getSensors());
             ui->twBodyTree->setCurrentItem(boneItem);
        }

        setupBodyTree(bone->getEndFixation(),selectedBone,boneItem);
    }
}

void EntityPropertiesController::itemClicked(QTreeWidgetItem * item, int)
{
    FixationTreeWidgetItem * fixItem = dynamic_cast<FixationTreeWidgetItem*>(item);
    if (fixItem)
    {
        emit sSensorsSelected(fixItem->fixation->getSensors());
        emit sFixationSelected(fixItem->fixation);
        return;
    }

    BoneTreeWidgetItem * boneItem = dynamic_cast<BoneTreeWidgetItem*>(item);
    if (boneItem)
    {
        emit sSensorsSelected(boneItem->bone->getEndFixation()->getSensors());
        emit sBoneSelected(boneItem->bone);
        return;
    }
}

void EntityPropertiesController::viewGenotype() {

    if(entity != NULL)
        ui->pteGenotype->setPlainText(Ressource::beautifullJson(entity->serialize()));
}
