#include "btoworld.h"

#include "mainfactory.h"
#include "bulletogre/bulletogreengine.h"
#include "Ogre.h"

#include "ogre/ogreengine.h"

namespace GeneLabCore {

btoWorld::btoWorld(MainFactory* factory, QObject *parent) :
    btWorld(factory, parent)
{
    btoEngine = static_cast<BulletOgreEngine*>(factory->getEngines().find("BulletOgre").value());

    // BTO BIOME
    Ogre::SceneManager* sceneManager = btoEngine->getOgreEngine()->getOgreSceneManager();

    // camera
    // BTO SCENE
    Ogre::Camera * cam = sceneManager->getCamera("firstCamera");
    cam->setPosition(Ogre::Vector3(-20,10,0));
    cam->setDirection(Ogre::Vector3(20,-5,0));

    // skybox
    // BTO BIOME
    sceneManager->setSkyDome(true, "Examples/CloudySky", 10, 8, 1000);

    // lights
    sceneManager->setAmbientLight(Ogre::ColourValue(0.4, 0.4, 0.4));
    //sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_NONE);



    Ogre::Light* pointLight = sceneManager->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(0, 150, 250));
    pointLight->setDiffuseColour(0.8, 0.8, 1.0);
    pointLight->setSpecularColour(0.8, 0.8, 1.0);

    Ogre::Light* directionalLight = sceneManager->createLight("directionalLight");
    directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour(Ogre::ColourValue(.25, .25, .25));
    directionalLight->setSpecularColour(Ogre::ColourValue(.25, .25, .25));
    directionalLight->setDirection(Ogre::Vector3( 0, -1, 1 ));


    Ogre::Light* spotLight = sceneManager->createLight("spotLight");
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight->setDiffuseColour(.9,.9,.9);
    spotLight->setSpecularColour(.9,.9,.9);
    spotLight->setDirection(-1, -1, 0);
    spotLight->setPosition(Ogre::Vector3(300, 300, 0));
    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

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

    // --------------------------
    // -- Content of the scene --
    // --------------------------

    // Static Floor
    // BTO SCENE
    Ogre::Entity *ent;
    Ogre::Plane p;
    p.normal = Ogre::Vector3(0,1,0); p.d = 0;
    Ogre::MeshManager::getSingleton().createPlane("FloorPlane",
                                            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                            p, 200000, 200000, 20, 20, true, 1, 9000, 9000,
                                            Ogre::Vector3::UNIT_Z);

    ent = sceneManager->createEntity("floor", "FloorPlane");
    ent->setMaterialName("Examples/GrassFloor");
    sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(ent);


}

}
