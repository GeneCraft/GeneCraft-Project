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

#include "btbiome.h"
#include "btworld.h"
#include "Ogre.h"
#include "bulletogre/bulletogreengine.h"
#include "bullet/bulletengine.h"
#include "ogre/ogreengine.h"
#include "btofactory.h"

namespace GeneCraftCore {
    btBiome::btBiome(btWorld* world, QVariant biomeData, QObject *parent) :
        QObject(parent)
    {
        world->setBiome(this);
        this->data = biomeData.toMap();
        bulletWorld = world;
    }

    btBiome::~btBiome() {

    }

    void btBiome::setup() {

        BulletOgreEngine* btoEngine = static_cast<BulletOgreEngine*>(bulletWorld->getFactory()->getEngineByName("BulletOgre"));
        Ogre::SceneManager* sceneManager = btoEngine->getOgreEngine()->getOgreSceneManager();
        Ogre::Camera * cam = sceneManager->getCamera("firstCamera");

        btScalar gravity = data["gravity"].toFloat();
        QVariantMap gravityMap = data["gravities"].toMap();
        world->setGravity(btVector3(gravity*gravityMap["axeX"].toDouble(),gravity*gravityMap["axeY"].toDouble(),gravity*gravityMap["axeZ"].toDouble()));

        if(gravityMap["axeY"].toDouble() > 0)
            cam->roll(Ogre::Degree(180));
    }

}
