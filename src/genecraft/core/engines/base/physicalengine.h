#ifndef OGREBULLETMANAGER_H
#define OGREBULLETMANAGER_H

#include <QObject>
#include <deque>
#include "genecraftcoreclasses.h"
#include "engine.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"

namespace GeneCraftCore {
    /**
     * @brief The engine that take care to manage the bullet worlds
     *
     */
    class BulletEngine : public Engine
    {
    public:

        /**
         * @brief Create the engine, will be empty and ready to manage bullet worlds
         *
         * @param parent
         */
        explicit BulletEngine(QObject *parent = 0);

        /**
         * @brief Add a world in the engine, the world will be stepped each
         time the engine is.
         *
         * @param world the world to add to the simulation
         */
        void addWorld(btDynamicsWorld* world) {
            this->worldList.append(world);
        }

        /**
         * @brief Remove a world from the simulation, it will not be stepped anymore
         *
         * @param world the world to remove from the simulation
         */
        void removeWorld(btDynamicsWorld* world) {
            this->worldList.removeAll(world);
        }

        /**
         * @brief disable or activate the step of the worlds, should use the
         SimulationManager toggle if available
         *
         * @param physicsEnable
         */
        inline void setPhysicsEnable(bool physicsEnable){
            this->physicsEnable = physicsEnable;
        }

        /**
         * @brief is the physical step enabled?
         *
         * @return bool
         */
        inline bool getPhysicsEnable(){
            return physicsEnable;
        }

        /**
         * @brief step all worlds
         *
         */
        void step();

    protected:

        QList<btDynamicsWorld*> worldList; /**< the list of active worlds */
        bool physicsEnable; /**< are the world stepped? */
    };
}
#endif // OGREBULLETMANAGER_H
