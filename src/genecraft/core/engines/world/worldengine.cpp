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

#include "worldengine.h"

#ifndef WORKER
#include "Ogre.h"
#include "btofactory.h"
#include "bulletogre/bulletogreengine.h"
#include "bullet/bulletengine.h"
#include "ogre/ogreengine.h"
#endif

namespace GeneCraftCore {

WorldEngine::WorldEngine()
{
    nbSteps = 0;
    isNotWorker = false;
}

void WorldEngine::setWorld(btoWorld *w)
{
    this->world = w;
}

void WorldEngine::beforeStep()
{
    if(exp->getWaitBeforeSetGravity())
    {
        // If right number of steps has passed change gravity
        if(exp->getStepsBeforeSetGravity()==nbSteps)
        {
            QVariant data = exp->getWorldDataMap()["biome"];
            QVariantMap gravityMap = data.toMap()["gravities"].toMap();
            world->setGravity(exp->getWorldDataMap(), gravityMap["axeX"].toDouble(),gravityMap["axeY"].toDouble(),gravityMap["axeZ"].toDouble());

            if(isNotWorker)
            {
                // Switch upside down if needed
                if(gravityMap["axeY"].toDouble() > 0)
                {
#ifndef WORKER
                    BulletOgreEngine* btoEngine = static_cast<BulletOgreEngine*>(world->getFactory()->getEngineByName("BulletOgre"));
                    Ogre::SceneManager* sceneManager = btoEngine->getOgreEngine()->getOgreSceneManager();
                    Ogre::Camera * cam = sceneManager->getCamera("firstCamera");
                    cam->roll(Ogre::Degree(180));
#endif
                }
            }

        }
    }
    nbSteps++;
}

void WorldEngine::setExperiment(Experiment *exp)
{
    this->exp = exp;
    nbSteps = 0;
}

void WorldEngine::setNotWorker(bool val)
{
    this->isNotWorker = val;
}

}
