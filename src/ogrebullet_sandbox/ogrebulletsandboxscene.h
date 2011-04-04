#ifndef OGREBULLETSANDBOXSCENE_H
#define OGREBULLETSANDBOXSCENE_H

#include <QObject>
#include <QDebug>
#include <deque>
#include "OGRE/Ogre.h"
#include <classes.h>
#include "world/ogrebulletscene.h"
#include "graphic/ogremanager.h"
#include "physics/bulletmanager.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h"
#include "Shapes/OgreBulletCollisionsBoxShape.h"
#include "OGRE/Ogre.h"
#include "graphic/ogremanager.h"
#include "engine/engine.h"

using namespace GeneLabOgreBullet;

class OgreBulletSandBoxScene : public OgreBulletScene
{
    Q_OBJECT
public:
    OgreBulletSandBoxScene(GeneLabOgreBullet::BulletManager* bulletManager, GeneLabOgreBullet::OgreManager* ogreManager, QObject *parent);

signals:

public slots:

private:

    // OgreBullet World
    OgreBulletDynamics::DynamicsWorld *mWorld;
    OgreBulletCollisions::DebugDrawer *debugDrawer;

    int mNumEntitiesInstanced;
    int mMoveSpeed;

    std::deque<OgreBulletDynamics::RigidBody *>         mBodies;
    std::deque<OgreBulletCollisions::CollisionShape *>  mShapes;

};

#endif // OGREBULLETSANDBOXSCENE_H
