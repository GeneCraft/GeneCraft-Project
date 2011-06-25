#include "btoscene.h"

#include "bulletogre/bulletogreengine.h"
#include "ogre/ogreengine.h"

#include "btofactory.h"

#include "Ogre.h"

namespace GeneLabCore {

    btoScene::btoScene(btoFactory* factory, QVariant sceneData, QObject *parent) :
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


        // Spawns zones and point
        foreach(Spawn* sp, this->spawns) {
            switch(sp->getType()) {
            case Spawn::Position:

                {
                // Create Ogre Entity
                Ogre::Entity* entity = btoEngine->getOgreEngine()->getOgreSceneManager()->createEntity("cube.mesh");

                // Material
                entity->setMaterialName("GeneLab/Spawn");

                // Attach
                Ogre::SceneNode* node = btoEngine->getOgreEngine()->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode();

                // Scale
                Ogre::AxisAlignedBox boundingB = entity->getBoundingBox(); // we need the bounding box of the box to be able to set the size of the Bullet-box
                Ogre::Vector3 ogreSize(1, 1, 1);
                Ogre::Vector3 scale = ogreSize  / boundingB.getSize();
                node->scale(scale);	// the cube is too big for us

                node->attachObject(entity);
                node->setPosition(sp->getSpawnPosition().x(),
                                  sp->getSpawnPosition().y(),
                                  sp->getSpawnPosition().z());
            }

                break;
            case Spawn::Zone:
                {
                // Create Ogre Entity
                Ogre::Entity* entity = btoEngine->getOgreEngine()->getOgreSceneManager()->createEntity("cube.mesh");

                // Material
                entity->setMaterialName("GeneLab/Spawn");

                // Attach
                Ogre::SceneNode* node = btoEngine->getOgreEngine()->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode();



                node->attachObject(entity);
                btVector3 minPos = sp->getMinPos();
                btVector3 maxPos = sp->getMaxPos();
                btVector3 center = ( minPos + maxPos ) / 2.0f;

                node->setPosition(center.x(), center.y(), center.z());

                // Scale
                Ogre::AxisAlignedBox boundingB = entity->getBoundingBox();
                Ogre::Vector3 ogreSize(maxPos.x() - minPos.x(),
                                       maxPos.y() - minPos.y(),
                                       maxPos.z() - minPos.z());
                Ogre::Vector3 scale = ogreSize  / boundingB.getSize();
                node->scale(scale);
            }
                break;
            }
        }

    }

}
