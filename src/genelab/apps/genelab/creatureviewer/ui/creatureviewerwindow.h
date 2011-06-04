#ifndef CREATUREVIEWER_H
#define CREATUREVIEWER_H

#include <QMainWindow>
#include "genelabcoreclasses.h"
#include "btBulletDynamicsCommon.h"

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

    void setInspector(QWidget * inspector);
    void setEntity(Entity *entity, btRigidBody *selectedBody);
    void setOpenGLWidget(QWidget * openGLWidget);
    void rigidBodySelected(btRigidBody *rigidBody);
    void showAbout();

    // new / load / save entity
    void createNewEntity();
    void loadEntityFromFile();
    void saveEntityToFile();
    void removeEntity();

    // physics
    void togglePhysics();

private:

    Bone *boneSelected;
    Fixation *fixSelected;

    Entity *selectedEntity;
    Ui::CreatureViewer *ui;
    QWidget *inspector;
    QWidget *openGLWidget;
    MainFactory* factory;
    SimulationManager* simulationManager;

    // components
    QAction *aTogglePhysics;
};

#endif // CREATUREVIEWER_H
