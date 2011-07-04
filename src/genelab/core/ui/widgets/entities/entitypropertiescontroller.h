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

    // GETTERS / SETTERS
    void setEntity(Entity *entity, btRigidBody * selectedBody = 0);
    void setBrainViz(PlugGridVisualizer* brainViz);
    void setBrainDesignViz(PlugGridDesignVisualizer* brainViz);

signals:

    void rigidBodySelected(btRigidBody *rigidBody);

public slots:

    void setOutFrom();
    void resetBonesProperties();
    void itemClicked(QTreeWidgetItem *,int);
    void selectSensorFixation();
    void setBrainSize();
    void clearSensors();
    void clearEffectors();
    void computeMinimalOuts();
    void updateStats();

private:

    Ui::EntityPropertiesController *ui;

    PlugGridVisualizer* brainViz;
    PlugGridDesignVisualizer* brainDezViz;

    void setupBodyTree(Fixation * fixation, btRigidBody * selectedBody, QTreeWidgetItem *rootItem = 0);

    Entity *entity;

    QTimer *statsTimer;

};

#endif // CREATUREPROPERTIESCONTROLLER_H
