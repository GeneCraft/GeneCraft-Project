#ifndef OGREBULLETMANAGER_H
#define OGREBULLETMANAGER_H

#include <QObject>
#include <deque>
#include "genelabcoreclasses.h"
#include "engine.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"

namespace GeneLabCore {
    class BulletEngine : public GeneLabCore::Engine
    {
        Q_OBJECT
    public:

        explicit BulletEngine(QObject *parent = 0);

        //OgreBulletDynamics::DynamicsWorld *getDynamicsWorld();

        btDynamicsWorld *getBulletDynamicsWorld()
        {
            return bulletDynamicsWorld;
        }

        inline void setPhysicsEnable(bool physicsEnable){
            this->physicsEnable = physicsEnable;
        }

        inline bool getPhysicsEnable(){
            return physicsEnable;
        }

    signals:

    public slots:

        void step();
        void init(/*OgreEngine* ogreRoot*/);

    protected:

        btDynamicsWorld *bulletDynamicsWorld;

        // OgreBullet World
        //OgreBulletDynamics::DynamicsWorld *mWorld;
        //OgreBulletCollisions::DebugDrawer *debugDrawer;

        bool physicsEnable;
    };
}
#endif // OGREBULLETMANAGER_H
