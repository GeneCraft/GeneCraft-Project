#ifndef DEFAULTEVENTMANAGER_H
#define DEFAULTEVENTMANAGER_H

#include <QObject>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QEvent>
#include <QQueue>
#include <QDebug>
#include "classes.h"
#include "physics/bulletmanager.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h"
#include "Shapes/OgreBulletCollisionsBoxShape.h"
#include "OGRE/Ogre.h"
#include "graphic/ogremanager.h"
#include "ogremanager.h"
#include "engine/engine.h"

class DefaultEventManager : public GeneLabCore::Engine
{
    Q_OBJECT

public:

    // Constructor
    DefaultEventManager(GeneLabOgreBullet::OgreManager *ogre, OgreBulletDynamics::DynamicsWorld *mWorld, QObject *parent = 0);

private:

    // Events will be managed during steps calls and not directly when they are detected
    QQueue<QEvent*> eventsQueue;

    // Specific actions
    void throwCube();
    GeneLabOgreBullet::OgreManager*        ogre;
    Ogre::Root*         mOgreRoot;
    Ogre::SceneManager* mSceneMgr;
    OgreBulletDynamics::DynamicsWorld *mWorld;
    int mNumEntitiesInstanced;

signals:

public slots:

    // Events (only used to save event into eventsQueue)
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void enterViewPortEvent(QEvent *e);
    void leaveViewPortEvent(QEvent *e);

    // Engine
    void beforeStep();
    void step();
    void afterStep();

};

#endif // DEFAULTEVENTMANAGER_H
