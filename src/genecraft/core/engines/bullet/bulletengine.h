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

#ifndef OGREBULLETMANAGER_H
#define OGREBULLETMANAGER_H

#include "genecraftcoreclasses.h"
#include "engine.h"

class btDynamicsWorld;

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
