#ifndef BODYITEMS_H
#define BODYITEMS_H

#include <QTreeWidgetItem>
#include <QListWidgetItem>
#include <QTableWidgetItem>

#include "genelabcoreclasses.h"
#include "sensors/sensor.h"
#include "effectors/effector.h"
#include "statistics/statisticsprovider.h"
#include "statistics/statisticsstorage.h"

namespace GeneLabCore{

// TREE

class FixationTreeWidgetItem : public QTreeWidgetItem
{
public:

    FixationTreeWidgetItem(Fixation * fixation)
    {
        this->fixation = fixation;
    }

    FixationTreeWidgetItem(QTreeWidgetItem * parent, Fixation * fixation) : QTreeWidgetItem(parent)
    {
        this->fixation = fixation;
    }

    Fixation *fixation;
};

class BoneTreeWidgetItem : public QTreeWidgetItem
{
public:
    BoneTreeWidgetItem(Bone * bone)
    {
        this->bone = bone;
        this->setIcon(0,QIcon(":/img/icons/bone_and_fixation"));
    }

    BoneTreeWidgetItem(QTreeWidgetItem * parent, Bone * bone) : QTreeWidgetItem(parent)
    {
        this->bone = bone;
        this->setIcon(0,QIcon(":/img/icons/bone_and_fixation"));
    }

    Bone *bone;
};

class StatisticTreeWidgetItem : public QTreeWidgetItem
{
public:
    StatisticTreeWidgetItem(Statistic * stat) {
        this->stat = stat;
        setText(0,stat->getName());
        setText(6,stat->getUnit());
        update();
        //this->setIcon(0,QIcon(":/img/icons/bone_and_fixation"));
    }

    void update() {
        setText(1,QString::number(stat->getValue()));
        setText(2,QString::number(stat->getMinValue()));
        setText(3,QString::number(stat->getMaxValue()));
        setText(4,QString::number(stat->getMean()));
        setText(5,QString::number(stat->getSum()));
    }

    Statistic *stat;
};


// LIST

class BoneListWidgetItem : public QListWidgetItem
{
public:

    BoneListWidgetItem(Bone * bone)
    {
        this->bone = bone;
        this->setIcon(QIcon(":/img/icons/bone_and_fixation"));
        this->setText("Bone");
    }

    Bone *bone;
};

class SensorListWidgetItem : public QListWidgetItem
{
public:

    SensorListWidgetItem(Sensor * sensor)
    {
        this->sensor = sensor;
        this->setIcon(QIcon(":/img/icons/bullet_feed"));
        this->setText(sensor->getTypeName());
    }

    Sensor *sensor;
};

class EffectorListWidgetItem : public QListWidgetItem
{
public:

    EffectorListWidgetItem(Effector * effector)
    {
        this->effector = effector;
        this->setIcon(QIcon(":/img/icons/motor_test"));
        this->setText(effector->getTypeName());
    }

    Effector *effector;
};




}

#endif // BODYITEMS_H
