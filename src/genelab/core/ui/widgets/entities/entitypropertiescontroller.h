#ifndef CREATUREPROPERTIESCONTROLLER_H
#define CREATUREPROPERTIESCONTROLLER_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "genelabcoreclasses.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

namespace Ui {
    class EntityPropertiesController;
}

using namespace GeneLabCore;

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
    }

    BoneTreeWidgetItem(QTreeWidgetItem * parent, Bone * bone) : QTreeWidgetItem(parent)
    {
        this->bone = bone;
    }

    Bone *bone;
};


class EntityPropertiesController : public QWidget
{
    Q_OBJECT

public:

    explicit EntityPropertiesController(QWidget *parent = 0);
    ~EntityPropertiesController();

    // GETTERS / SETTERS
    void setEntity(Entity *entity, btRigidBody * selectedBody = 0);

signals:

    void rigidBodySelected(btRigidBody *rigidBody);

public slots:

    void setRandomBonesProperties();
    void resetBonesProperties();
    void itemClicked(QTreeWidgetItem *,int);

private:

    Ui::EntityPropertiesController *ui;

    void setupBodyTree(Fixation * fixation, btRigidBody * selectedBody, QTreeWidgetItem *rootItem = 0);

    Entity *entity;

};

#endif // CREATUREPROPERTIESCONTROLLER_H
