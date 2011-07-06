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

        // To create the engine
        explicit BulletEngine(QObject *parent = 0);

        // To add a world
        void addWorld(btDynamicsWorld* world) {
            this->worldList.append(world);
        }

        // To remove a world
        void removeWorld(btDynamicsWorld* world) {
            this->worldList.removeAll(world);
        }

        // To activate or disable physics of all worlds
        inline void setPhysicsEnable(bool physicsEnable){
            this->physicsEnable = physicsEnable;
        }

        // To know if physics is activated
        inline bool getPhysicsEnable(){
            return physicsEnable;
        }

    signals:

    public slots:

        void step();

    protected:

        QList<btDynamicsWorld*> worldList;
        bool physicsEnable;
    };
}
#endif // OGREBULLETMANAGER_H
