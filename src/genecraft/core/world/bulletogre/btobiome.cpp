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

#include "btobiome.h"
#include "Ogre.h"

#include "btoworld.h"


#include "bulletogre/bulletogreengine.h"
#include "ogre/ogreengine.h"

#include <QJsonObject>
#include <QJsonArray>
#include "btofactory.h"

#include <QDebug>

namespace GeneCraftCore {

    btoBiome::btoBiome(btoWorld* world, QJsonObject biomeDataMap, QObject *parent) :
        btBiome(world, biomeDataMap, parent), world(world)
    {
        this->world = world;

        lightsData = biomeDataMap["lights"].toArray();
    }

    void btoBiome::setup() {
        btBiome::setup();

        // Essential objects
        BulletOgreEngine* btoEngine = world->getBulletOgreEngine();
        Ogre::SceneManager* sceneManager = btoEngine->getOgreEngine()->getOgreSceneManager();

        // ---------
        // -- Sky --
        // ---------
        if(data.contains("skyMaterial")) {

            QString skyMaterial = data["skyMaterial"].toString();

            if(skyMaterial.contains("box", Qt::CaseInsensitive))
                sceneManager->setSkyBox(true, skyMaterial.toStdString(), 1000);
            else
                sceneManager->setSkyDome(true, skyMaterial.toStdString(), 10, 8, 1000);
        }

        // -------------
        // -- Shadows --
        // -------------
        sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_NONE);

        sceneManager->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3, 0.3));

        // ------------
        // -- Lights --
        // ------------
        int nbPointLights = 0; // for id
        int nbDirectionalLights = 0; // for id
        int nbSpotLights = 0; // for id
        foreach(QJsonValue lightData, lightsData) {

           QJsonObject lightMap = lightData.toObject();

           // TODO diffuse and specular !!! dr, dg, db, sr, sg, sb
           btScalar r = lightMap["r"].toDouble();
           btScalar g = lightMap["g"].toDouble();
           btScalar b = lightMap["b"].toDouble();

           QString type = lightMap["type"].toString();
           if(type.compare("ambient") == 0) {

                sceneManager->setAmbientLight(Ogre::ColourValue(r, g, b));
           }
           else if(type.compare("point") == 0) {

               nbPointLights++;

               btScalar x = lightMap["posX"].toDouble();
               btScalar y = lightMap["posY"].toDouble();
               btScalar z = lightMap["posZ"].toDouble();

               Ogre::Light* pointLight = sceneManager->createLight();
               pointLight->setType(Ogre::Light::LT_POINT);
               pointLight->setPosition(Ogre::Vector3(x, y, z));
               pointLight->setDiffuseColour(r, g, b);
               pointLight->setSpecularColour(r, g, b);
           }
           else if(type.compare("directional") == 0) {

               nbDirectionalLights++;

               btScalar dirX = lightMap["dirX"].toDouble();
               btScalar dirY = lightMap["dirY"].toDouble();
               btScalar dirZ = lightMap["dirZ"].toDouble();

               Ogre::Light* directionalLight = sceneManager->createLight();
               directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
               directionalLight->setDiffuseColour(Ogre::ColourValue(r, g, b));
               directionalLight->setSpecularColour(Ogre::ColourValue(r, g, b));
               directionalLight->setDirection(Ogre::Vector3( dirX, dirY, dirZ));

           }
           else if(type.compare("spot") == 0) {

               nbSpotLights++;

               btScalar dirX = lightMap["dirX"].toDouble();
               btScalar dirY = lightMap["dirY"].toDouble();
               btScalar dirZ = lightMap["dirZ"].toDouble();

               btScalar posX = lightMap["posX"].toDouble();
               btScalar posY = lightMap["posY"].toDouble();
               btScalar posZ = lightMap["posZ"].toDouble();

               btScalar innerAngle = lightMap["innerAngle"].toDouble();
               btScalar outerAngle = lightMap["outerAngle"].toDouble();
               //btScalar falloff = lightMap["falloff"].toDouble();

               Ogre::Light* spotLight = sceneManager->createLight();
               spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
               spotLight->setDiffuseColour(r,g,b);
               spotLight->setSpecularColour(r,g,b);
               spotLight->setDirection(dirX, dirY, dirZ);
               spotLight->setPosition(posX, posY, posZ);
               spotLight->setSpotlightRange(Ogre::Radian(innerAngle), Ogre::Radian(outerAngle));
           }
        }

    }
}
