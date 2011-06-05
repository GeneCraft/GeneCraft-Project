#ifndef BODYITEMS_H
#define BODYITEMS_H

#include <QTreeWidgetItem>
#include <QListWidgetItem>

#include "genelabcoreclasses.h"
#include "sensors/sensor.h"

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

}

#endif // BODYITEMS_H
