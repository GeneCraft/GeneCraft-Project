#ifndef OGREBULLETMANAGER_H
#define OGREBULLETMANAGER_H

#include <QObject>
#include <deque>

namespace Ogre {
    class Root;
    class SceneManager;
}

namespace OgreBulletDynamics {
    class DynamicsWorld;
    class RigidBody;
}

namespace OgreBulletCollisions {
    class DebugDrawer;
    class CollisionShape;
}

class OgreManager;

class OgreBulletManager : public QObject
{
    Q_OBJECT
public:
    explicit OgreBulletManager(QObject *parent = 0);
    void init(OgreManager* ogreRoot);

    void oneStep();
signals:

public slots:

protected:
    OgreManager* ogre;
    Ogre::Root* mOgreRoot;
    Ogre::SceneManager* mSceneMgr;

    OgreBulletDynamics::DynamicsWorld *mWorld;   // OgreBullet World
    OgreBulletCollisions::DebugDrawer *debugDrawer;
    int mNumEntitiesInstanced;
    int mMoveSpeed;
    std::deque<OgreBulletDynamics::RigidBody *>         mBodies;
    std::deque<OgreBulletCollisions::CollisionShape *>  mShapes;


};

#endif // OGREBULLETMANAGER_H
