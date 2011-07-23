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

namespace GeneLabCore {

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
        //sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_NONE);

        // ------------
        // -- Lights --
        // ------------
        int nbPointLights = 0; // for id
        int nbDirectionalLights = 0; // for id
        int nbSpotLights = 0; // for id
        foreach(QVariant lightData, lightsData) {

           QVariantMap lightMap = lightData.toMap();

           // TODO diffuse and specular !!! dr, dg, db, sr, sg, sb
           float r = lightMap["r"].toFloat();
           float g = lightMap["g"].toFloat();
           float b = lightMap["b"].toFloat();

           QString type = lightMap["type"].toString();
           if(type.compare("ambient") == 0) {

                sceneManager->setAmbientLight(Ogre::ColourValue(r, g, b));
           }
           else if(type.compare("point") == 0) {

               nbPointLights++;

               float x = lightMap["posX"].toFloat();
               float y = lightMap["posY"].toFloat();
               float z = lightMap["posZ"].toFloat();

               Ogre::Light* pointLight = sceneManager->createLight();
               pointLight->setType(Ogre::Light::LT_POINT);
               pointLight->setPosition(Ogre::Vector3(x, y, z));
               pointLight->setDiffuseColour(r, g, b);
               pointLight->setSpecularColour(r, g, b);
           }
           else if(type.compare("directional") == 0) {

               nbDirectionalLights++;

               float dirX = lightMap["dirX"].toFloat();
               float dirY = lightMap["dirY"].toFloat();
               float dirZ = lightMap["dirZ"].toFloat();

               Ogre::Light* directionalLight = sceneManager->createLight();
               directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
               directionalLight->setDiffuseColour(Ogre::ColourValue(r, g, b));
               directionalLight->setSpecularColour(Ogre::ColourValue(r, g, b));
               directionalLight->setDirection(Ogre::Vector3( dirX, dirY, dirZ));

           }
           else if(type.compare("spot") == 0) {

               nbSpotLights++;

               float dirX = lightMap["dirX"].toFloat();
               float dirY = lightMap["dirY"].toFloat();
               float dirZ = lightMap["dirZ"].toFloat();

               float posX = lightMap["posX"].toFloat();
               float posY = lightMap["posY"].toFloat();
               float posZ = lightMap["posZ"].toFloat();

               float innerAngle = lightMap["innerAngle"].toFloat();
               float outerAngle = lightMap["outerAngle"].toFloat();
               //float falloff = lightMap["falloff"].toFloat();

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
