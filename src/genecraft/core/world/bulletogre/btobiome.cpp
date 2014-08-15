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

#include <QVariant>
#include <QVariantMap>
#include <QVariantList>
#include "btofactory.h"

#include <QDebug>

namespace GeneCraftCore {

    btoBiome::btoBiome(btoWorld* world, QVariant biomeData, QObject *parent) :
        btBiome(world, biomeData, parent), world(world)
    {
        this->world = world;

        QVariantMap biomeDataMap = biomeData.toMap();
        lightsData = biomeDataMap["lights"].toList();
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
        foreach(QVariant lightData, lightsData) {

           QVariantMap lightMap = lightData.toMap();

           // TODO diffuse and specular !!! dr, dg, db, sr, sg, sb
           btScalar r = lightMap["r"].toFloat();
           btScalar g = lightMap["g"].toFloat();
           btScalar b = lightMap["b"].toFloat();

           QString type = lightMap["type"].toString();
           if(type.compare("ambient") == 0) {

                sceneManager->setAmbientLight(Ogre::ColourValue(r, g, b));
           }
           else if(type.compare("point") == 0) {

               nbPointLights++;

               btScalar x = lightMap["posX"].toFloat();
               btScalar y = lightMap["posY"].toFloat();
               btScalar z = lightMap["posZ"].toFloat();

               Ogre::Light* pointLight = sceneManager->createLight();
               pointLight->setType(Ogre::Light::LT_POINT);
               pointLight->setPosition(Ogre::Vector3(x, y, z));
               pointLight->setDiffuseColour(r, g, b);
               pointLight->setSpecularColour(r, g, b);
           }
           else if(type.compare("directional") == 0) {

               nbDirectionalLights++;

               btScalar dirX = lightMap["dirX"].toFloat();
               btScalar dirY = lightMap["dirY"].toFloat();
               btScalar dirZ = lightMap["dirZ"].toFloat();

               Ogre::Light* directionalLight = sceneManager->createLight();
               directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
               directionalLight->setDiffuseColour(Ogre::ColourValue(r, g, b));
               directionalLight->setSpecularColour(Ogre::ColourValue(r, g, b));
               directionalLight->setDirection(Ogre::Vector3( dirX, dirY, dirZ));

           }
           else if(type.compare("spot") == 0) {

               nbSpotLights++;

               btScalar dirX = lightMap["dirX"].toFloat();
               btScalar dirY = lightMap["dirY"].toFloat();
               btScalar dirZ = lightMap["dirZ"].toFloat();

               btScalar posX = lightMap["posX"].toFloat();
               btScalar posY = lightMap["posY"].toFloat();
               btScalar posZ = lightMap["posZ"].toFloat();

               btScalar innerAngle = lightMap["innerAngle"].toFloat();
               btScalar outerAngle = lightMap["outerAngle"].toFloat();
               //btScalar falloff = lightMap["falloff"].toFloat();

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
