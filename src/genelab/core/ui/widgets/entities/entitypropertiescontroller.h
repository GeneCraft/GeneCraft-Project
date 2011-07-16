#ifndef CREATUREPROPERTIESCONTROLLER_H
#define CREATUREPROPERTIESCONTROLLER_H

#include <QWidget>
#include "bodyitems.h"
#include "genelabcoreclasses.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include <QTimer>

namespace Ui {
    class EntityPropertiesController;
}

using namespace GeneLabCore;

class EntityPropertiesController : public QWidget
{
    Q_OBJECT

public:

    explicit EntityPropertiesController(QWidget *parent = 0);
    ~EntityPropertiesController();
    void connectToInspectorInputManager(InspectorsInputManager *iim);

    // GETTERS / SETTERS
    void setBrainViz(PlugGridVisualizer* brainViz);
    void setBrainDesignViz(PlugGridDesignVisualizer* brainViz);

signals:

    void sSensorsSelected(QList<Sensor*> s);
    void sFixationSelected(Fixation*);
    void sBoneSelected(Bone *);

public slots:

    void setEntity(Entity *entity, Bone *selectedBone = NULL);
    void setOutFromNormalPosition();
    void setOutFromNone();
    void setOutFromBrain();
    void setOutFromRandom();
    void setOutFrom(int outsFrom);
    void viewGenotype();
    void followSelectedEntity();

    void fixationSelected(Fixation *fixation);
    void boneSelected(Bone *bone);
    void shapeUpdated();
    void entityUpdated(Entity *entity);
    void entityDeleted(Entity *entity);

    void resetBonesProperties();
    void itemClicked(QTreeWidgetItem *,int);

private:

    Ui::EntityPropertiesController *ui;

    void setupBodyTree(Fixation * fixation, Bone *selectedBone, QTreeWidgetItem *rootItem = 0);

    Entity *entity;
};

#endif // CREATUREPROPERTIESCONTROLLER_H
