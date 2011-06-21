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

        /*btDynamicsWorld *getBulletDynamicsWorld()
        {
            return bulletDynamicsWorld;
        }*/

        void addWorld(btDynamicsWorld* world) {
            this->worldList.append(world);
        }

        void removeWorld(btDynamicsWorld* world) {
            this->worldList.removeAll(world);
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

    protected:

        QList<btDynamicsWorld*> worldList;
        bool physicsEnable;
    };
}
#endif // OGREBULLETMANAGER_H
