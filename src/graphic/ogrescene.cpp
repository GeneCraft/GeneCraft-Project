#include "OGRE/Ogre.h"
#include <QDebug>

#include "graphic/ogrescene.h"
#include "entity/entity.h"
#include "world/world.h"

namespace GeneLabOgreBullet {

    using namespace GeneLabCore;

    OgreScene::OgreScene(Ogre::Root* ogreRoot,
                         Ogre::SceneManager* sceneManager)
    {
        qDebug() << "Scene creation";
        this->ogreRoot = ogreRoot;
        this->sceneManager = sceneManager;
        sceneManager->setAmbientLight(Ogre::ColourValue(0.4, 0.4, 0.4));
        sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

        Ogre::Light* pointLight = sceneManager->createLight("pointLight");
        pointLight->setType(Ogre::Light::LT_POINT);
        pointLight->setPosition(Ogre::Vector3(0, 150, 250));

        pointLight->setDiffuseColour(1.0, 0.0, 0.0);
        pointLight->setSpecularColour(1.0, 0.0, 0.0);

        Ogre::Light* directionalLight = sceneManager->createLight("directionalLight");
        directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
        directionalLight->setDiffuseColour(Ogre::ColourValue(.25, .25, 0));
        directionalLight->setSpecularColour(Ogre::ColourValue(.25, .25, 0));

        directionalLight->setDirection(Ogre::Vector3( 0, -1, 1 ));

        Ogre::Light* spotLight = sceneManager->createLight("spotLight");
        spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
        spotLight->setDiffuseColour(0, 0, 1.0);
        spotLight->setSpecularColour(0, 0, 1.0);

        spotLight->setDirection(-1, -1, 0);
        spotLight->setPosition(Ogre::Vector3(300, 300, 0));

        spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
        Ogre::Entity* entNinja = sceneManager->createEntity("Ninja", "ninja.mesh");
        entNinja->setCastShadows(true);
        sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(entNinja);
    }
}
