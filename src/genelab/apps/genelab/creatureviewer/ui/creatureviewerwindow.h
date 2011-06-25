#ifndef CREATUREVIEWER_H
#define CREATUREVIEWER_H

#include <QMainWindow>
#include "genelabcoreclasses.h"
#include "btBulletDynamicsCommon.h"
#include "ressources/dbrecord.h"

namespace Ui {
    class CreatureViewer;
}

using namespace GeneLabCore;

/**
 * (c) GeneLab 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * Main window of the creature viewer sub-app.
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo & Cyprien Huissoud
 */
class CreatureViewerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreatureViewerWindow(QWidget *parent = 0);
    ~CreatureViewerWindow();

public slots:

    void init();
    void setInspector(QWidget * inspector);
    void setEntity(Entity *entity, btRigidBody *selectedBody);
    void rigidBodySelected(btRigidBody *rigidBody);
    void showAbout();

    // new / load / save entity
    void createNewEntity();
    void loadEntityFromFile();
    void loadEntityFromDb();
    void saveEntityToFile();
    void saveEntityToDb();
    void removeEntity();

    // physics
    void togglePhysics();

private:
    Ui::CreatureViewer *ui;

    Bone *boneSelected;
    Fixation *fixSelected;

    Entity *selectedEntity;
    QWidget *inspector;
    btoFactory* factory;
    SimulationManager* simulationManager;
    btShapesFactory* shapesFactory;

    // components
    QAction *aTogglePhysics;

    // Spawned entity
    QList<Entity*> ents;
    QTimer* entitySpawner;

    btoWorld* world;

    DataBase base;

private slots:
    void spawnNew();
};

#endif // CREATUREVIEWER_H
