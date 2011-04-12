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
        sceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
        sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);


        sceneManager->setSkyBox(true, "Examples/SpaceSkyBox");
        //sceneManager->setSkyDome(true, "Examples/CloudySky", 5, 8);

//        Ogre::Light* pointLight = sceneManager->createLight("pointLight");
//        pointLight->setType(Ogre::Light::LT_POINT);
//        pointLight->setPosition(Ogre::Vector3(0, 0, 0));
//        pointLight->setDiffuseColour(1.0, 0.0, 0.0);
//        pointLight->setSpecularColour(1.0, 0.0, 0.0);

        // directional
        Ogre::Light* directionalLight = sceneManager->createLight("directionalLight");
        directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
        directionalLight->setDiffuseColour(Ogre::ColourValue(.1,.1,.1));
        directionalLight->setSpecularColour(Ogre::ColourValue(.1,.1,.1));
        directionalLight->setDirection(Ogre::Vector3( 0, -1, 1 ));

        // spot light
//        Ogre::Light* spotLight = sceneManager->createLight("spotLight");
//        spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
//        spotLight->setDiffuseColour(0, 0, 1.0);
//        spotLight->setSpecularColour(0, 0, 1.0);
//        spotLight->setDirection(-1, -1, 0);
//        spotLight->setPosition(Ogre::Vector3(0, 200, 200));
//        spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));



        /*
        Ogre::Entity* entNinja = sceneManager->createEntity("Ninja", "ninja.mesh");
        entNinja->setCastShadows(true);
        sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(entNinja);*/
    }
}
