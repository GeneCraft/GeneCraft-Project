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

#ifndef CREATUREVIEWER_H
#define CREATUREVIEWER_H

#include <QMainWindow>
#include "genecraftcoreclasses.h"
#include "btBulletDynamicsCommon.h"
#include "ressources/dbrecord.h"

#include "ui/widgets/entities/brainpropertiescontroller.h"
#include "ui/widgets/entities/statisticspropertiescontroller.h"
#include "ui/widgets/entities/entitypropertiescontroller.h"
#include "widgets/experiments/experimentspropertiescontroller.h"
#include "widgets/experiments/ressourcesbrowser.h"
#include "widgets/experiments/experimentctrl.h"
#include "widgets/experiments/workerctrl.h"

#include "Ogre.h"

#include <QDoubleSpinBox>

// Listeners
#include "creatureviewerinputmanager.h"

namespace Ui {
    class CreatureViewer;
}

/**
 * (c) GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
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

    btVector3 getCameraPosition();
signals:

    void sLoadExperiment(Experiment*);

public slots:

    void init();
    //void setEntity(Entity *entity, btRigidBody *selectedBody);
    // void rigidBodySelected(btRigidBody *rigidBody);
    void showAbout();

    // new / load / save entity
    void addEntity(QVariantMap entityData, Ressource *ressource);
    Entity *createNewEntity();
    Entity *createCreature(QVariant genotype, btVector3 position, Ressource *ressource);
    void loadEntityFromFile();
    void saveEntityToFile();
    void saveEntityToDb();
    void removeEntity();
    void removeAllEntities();
    void removeAllEntitiesExceptSelected();
    void addRandomEntity();
    void createMutationSample();
    /*** REAL SPIDER ***/
    void addRealSpider();
    /*** END ***/

    // experiment and world
    void setExperiment(Experiment* experiment);
    void setWorld(QVariantMap worldMap);
    void loadResult(Result*);
    //void addResult(QVariantMap resultData, Ressource *ressource);

    // notifications
    void entitySelected(Entity *entity);
    void entityDeleted(Entity*);
    void boneDeleted(Bone* bone);
    void fixationDeleted(Fixation* fix);
    void boneSelected(Bone* bone);
    void fixationSelected(Fixation* fix);

    // utils
    void togglePhysics();
    void enterInWhatsThisMode();
    void followSelectedEntity();
    void unfollowEntity();
    void toggleShadows();
    void setGravity();

    // Modes
    void switchToWelcomeMode();
    void switchToDesignerMode();
    void switchToExperimentMode();
    void switchToTheaterMode();
    void hideAllDocks();

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
    RessourcesBrowser *ressourcesBrowser;
    ExperimentCtrl* expCtrl;
    WorkerCtrl* workerCtrl;

    Experiment *experiment;

    CreatureViewerInputManager *cvim;

    QAction *aFollowCreature;
    QAction *aShowShadows;
    QAction *aSetGravity;

    // Toolbar mode
    QAction *aWelcomeMode;
    QAction *aDesignerMode;
    QAction *aExperimentMode;
    QAction *aTheaterMode;

    QDoubleSpinBox *sbxAxeX;
    QDoubleSpinBox *sbxAxeY;
    QDoubleSpinBox *sbxAxeZ;

    Ogre::Radian angleSurAxe(Ogre::Vector3 vect1, Ogre::Vector3 vect2, Ogre::Vector3 axe);

private slots:

    void spawnNew();
    void spawnRandomEntities(int nbEntities);
    void spawnMutationSample(Entity *originEntity, int nbCreatures);
};

#endif // CREATUREVIEWER_H
