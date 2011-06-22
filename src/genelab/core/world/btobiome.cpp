#include "btobiome.h"
#include "Ogre.h"


#include "bulletogre/bulletogreengine.h"
#include "ogre/ogreengine.h"

#include <QVariant>
#include <QVariantMap>
#include <QVariantList>

namespace GeneLabCore {

    btoBiome::btoBiome(MainFactory* factory, QVariant biomeData, QObject *parent) :
    btBiome(factory, biomeData, parent)
    {
    }

    void btoBiome::setup() {
        btBiome::setup();

        // camera
        QString skyDomeName = data["sky"].toString();
        float ambiantR = data["aR"].toFloat();
        float ambiantG = data["aG"].toFloat();
        float ambiantB = data["aB"].toFloat();

        float lightR   = data["lR"].toFloat();
        float lightG   = data["lG"].toFloat();
        float lightB   = data["lB"].toFloat();

        BulletOgreEngine* btoEngine = static_cast<BulletOgreEngine*>(factory->getEngines().find("BulletOgre").value());

        Ogre::SceneManager* sceneManager = btoEngine->getOgreEngine()->getOgreSceneManager();

        sceneManager->setSkyDome(true, skyDomeName.toStdString(), 10, 8, 1000);

        // lights
        sceneManager->setAmbientLight(Ogre::ColourValue(ambiantR, ambiantG, ambiantB));
        //sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_NONE);

        Ogre::Light* pointLight = sceneManager->createLight("pointLight");
        pointLight->setType(Ogre::Light::LT_POINT);
        pointLight->setPosition(Ogre::Vector3(0, 150, 250));
        pointLight->setDiffuseColour(lightR, lightG, lightB);
        pointLight->setSpecularColour(lightR, lightG, lightB);

        Ogre::Light* directionalLight = sceneManager->createLight("directionalLight");
        directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
        directionalLight->setDiffuseColour(Ogre::ColourValue(lightR, lightG, lightB));
        directionalLight->setSpecularColour(Ogre::ColourValue(lightR, lightG, lightB));
        directionalLight->setDirection(Ogre::Vector3( 0, -1, 1 ));


//        Ogre::Light* spotLight = sceneManager->createLight("spotLight");
//        spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
//        spotLight->setDiffuseColour(.9,.9,.9);
//        spotLight->setSpecularColour(.9,.9,.9);
//        spotLight->setDirection(-1, -1, 0);
//        spotLight->setPosition(Ogre::Vector3(300, 300, 0));
//        spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

        // -------------------------
        // -- List of Material :) --
        // -------------------------
        //Ogre::ResourceManager::ResourceMapIterator materialIterator = Ogre::MaterialManager::getSingleton().getResourceIterator();
        /*while (materialIterator.hasMoreElements())
        {
            QString matName = QString((static_cast<Ogre::MaterialPtr>(materialIterator.peekNextValue())).getPointer()->getName().c_str());

            if(matName.contains("Grass"))
                qDebug() << "****************************************************" ;

            qDebug() << matName;

            materialIterator.moveNext();
        }*/

    }
}
