#ifndef CREATUREVIEWER_H
#define CREATUREVIEWER_H

#include <QMainWindow>
#include "genelabcoreclasses.h"
#include "btBulletDynamicsCommon.h"
#include "ressources/dbrecord.h"

#include "ui/widgets/entities/brainpropertiescontroller.h"
#include "ui/widgets/entities/statisticspropertiescontroller.h"
#include "ui/widgets/entities/entitypropertiescontroller.h"
#include "widgets/experiments/experimentspropertiescontroller.h"

// Listeners
#include "creatureviewerinputmanager.h"

namespace Ui {
    class CreatureViewer;
}

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
    //void setEntity(Entity *entity, btRigidBody *selectedBody);
    // void rigidBodySelected(btRigidBody *rigidBody);
    void showAbout();

    // new / load / save entity
    void createNewEntity();
    void loadEntityFromFile();
    void loadEntityFromDb();
    void saveEntityToFile();
    void saveEntityToDb();
    void removeEntity();
    void removeAllEntities();
    void removeAllEntitiesExceptSelected();
    void enterInWhatsThisMode();

    void followSelectedEntity();
    void unfollowEntity();

    // notifications
    void entitySelected(Entity *entity);
    void entityDeleted(Entity*);
    void boneDeleted(Bone* bone);
    void fixationDeleted(Fixation* fix);
    void boneSelected(Bone* bone);
    void fixationSelected(Fixation* fix);

    void addRandomEntity();
    void createMutationSample();
    void openExperimentPropertiesController();

    // physics
    void togglePhysics();
    void setExperiment(GeneLabCore::Experiment* experiment);

signals:

    void sEntityDeleted(Entity *);

private:
    Ui::CreatureViewer *ui;

    // To create
    btoFactory* factory;
    SimulationManager* simulationManager;
    btoShapesFactory* shapesFactory;
    CreatureFactory* creatureFactory;
    btoWorldFactory* worldFactory;
    btoWorld *world;

    // components
    QAction *aTogglePhysics;

    // Spawned entity
    QList<Entity*> ents;
    QTimer* entitySpawner;

    // Operation on entities
    Entity *selectedEntity;
    DataBase base;
    Bone *selectedBone;
    Fixation *selectedFix;

    // Docks inspectors
    EntityPropertiesController *entityPropertiesController;
    FixationPropertiesController *fixationPropertiesController;
    BonePropertiesController *bonePropertiesController;
    StatisticsPropertiesController *statsPropertiesController;
    BrainPropertiesController *brainPropertiesController;

    Experiment *experiment;
    ExperimentsPropertiesController *epc;

    CreatureViewerInputManager *cvim;

private slots:

    void spawnNew();
    void spawnRandomEntities(int nbEntities);
    void spawnMutationSample(Entity *originEntity, int nbCreatures);
};

#endif // CREATUREVIEWER_H
