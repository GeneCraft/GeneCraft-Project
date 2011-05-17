#ifndef OGREBULLETMANAGER_H
#define OGREBULLETMANAGER_H

#include <QObject>
#include <deque>
#include "genelabcoreclasses.h"
#include "engine.h"

namespace GeneLabCore {
    class BulletManager : public GeneLabCore::Engine
    {
        Q_OBJECT
    public:

        explicit BulletManager(QObject *parent = 0);

        OgreBulletDynamics::DynamicsWorld *getDynamicsWorld();

        void setPhysicsEnable(bool physicsEnable);
        bool getPhysicsEnable();

    signals:

    public slots:

        void beforeStep();
        void step();
        void afterStep();
        void init(OgreManager* ogreRoot);

    protected:

        OgreManager* ogreEngine;

        // OgreBullet World
        OgreBulletDynamics::DynamicsWorld *mWorld;
        OgreBulletCollisions::DebugDrawer *debugDrawer;

        bool physicsEnable;
    };
}
#endif // OGREBULLETMANAGER_H
