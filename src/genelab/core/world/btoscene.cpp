#include "btoscene.h"

#include "bulletogre/bulletogreengine.h"
#include "ogre/ogreengine.h"

#include "mainfactory.h"

#include "Ogre.h"

namespace GeneLabCore {

    btoScene::btoScene(MainFactory* factory, QVariant sceneData, QObject *parent) :
        btScene(factory, sceneData, parent)
    {
    }

    void btoScene::setup() {
        btScene::setup();

        float camX, camY, camZ, lookX, lookY, lookZ;
        QVariantMap camData = data["cam"].toMap();
        camX = camData["cX"].toFloat();
        camY = camData["cY"].toFloat();
        camZ = camData["cZ"].toFloat();
        lookX = camData["lX"].toFloat();
        lookY = camData["lY"].toFloat();
        lookZ = camData["lZ"].toFloat();

        BulletOgreEngine* btoEngine = static_cast<BulletOgreEngine*>(factory->getEngines().find("BulletOgre").value());

        Ogre::SceneManager* sceneManager = btoEngine->getOgreEngine()->getOgreSceneManager();

        Ogre::Camera * cam = sceneManager->getCamera("firstCamera");
        cam->setPosition(Ogre::Vector3(camX, camY, camZ)); // -20, 10, 0
        cam->setDirection(Ogre::Vector3(lookX, lookY, lookZ)); // -20, 5, 0


        // --------------------------
        // -- Content of the scene --
        // --------------------------

        // Static Floor ?

        if(data["type"].toString() == "flatland") {
            QString textureName = data["floor"].toString();

            Ogre::Entity *ent;
            Ogre::Plane p;
            p.normal = Ogre::Vector3(0,1,0); p.d = 0;
            Ogre::MeshManager::getSingleton().createPlane("FloorPlane",
                                           Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                            p, 200000, 200000, 20, 20, true, 1, 9000, 9000,
                                                Ogre::Vector3::UNIT_Z);

           ent = sceneManager->createEntity("floorWorld", "FloorPlane");
           ent->setMaterialName(textureName.toStdString());
           sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
        }

    }

}
