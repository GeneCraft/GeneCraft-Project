/*
Copyright 2011, 2012 Zéni David

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

#ifndef WORLDENGINE_H
#define WORLDENGINE_H

#include "bulletogre/btoworld.h"
#include "experiment/experiment.h"

namespace GeneCraftCore {

/**
 * @brief Engine to manage the world.
 * 1) During before step, gravity will be checked.
 *
 *
 */
class WorldEngine : public Engine
{
public:
    /**
     * @brief Create the world engine
     *
     */
    WorldEngine();
    /**
     * @brief Set the world to monitor
     *
     * @param w
     *
     */
    void setWorld(btoWorld* w);
    /**
     * @brief Set the experiment running
     *
     * @param exp
     *
     */
    void setExperiment(Experiment* exp);
    /**
     * @brief Check how much steps has passed
     *          and then change gravity if needed
     *
     */
    virtual void beforeStep();
    /**
     * @brief Set if used by CreatureViewer
     *          or worker
     *
     * @param val
     *
     */
    void setNotWorker(bool val);
private:
    btoWorld* world;
    Experiment* exp;
    int nbSteps;
    bool isNotWorker;
};

}

#endif // WORLDENGINE_H
