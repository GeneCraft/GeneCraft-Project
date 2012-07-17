/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud, Zéni David

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
 * @brief Engine to manage entities.
 * 1) During before step, sensors will stepped.
 * 2) During step, brains will stepped.
 * 3) During after step, modifiers will stepped.
 *
 *
 */
class WorldEngine : public Engine
{
public:
    WorldEngine();

    void setWorld(btoWorld* w);

    void setExperiment(Experiment* exp);

    void beforeStep();
private:
    btoWorld* world;
    Experiment* exp;
    int nbSteps;
};

}

#endif // WORLDENGINE_H
