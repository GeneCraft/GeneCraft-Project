#include "btoscene.h"

// Qt
#include <QVariantMap>
#include <QVariantList>

// ogre
#include "Ogre.h"
#include "Terrain/OgreTerrain.h"

#include "bulletogre/bulletogreengine.h"
#include "ogre/ogreengine.h"

// factory
#include "btofactory.h"
#include "bulletogre/shapes/btobox.h"

// world
#include "btoworld.h"

namespace GeneCraftCore {

    btoScene::btoScene(btoWorld* world, QVariant sceneData, QObject *parent) :
        btScene(world, sceneData, parent)
    {
    }

    void btoScene::setup() {
        btScene::setup();

        // ------------
        // -- Camera --
        // ------------
        QVariantMap camData = data["camera"].toMap();

        Ogre::Vector3 position(camData["posX"].toFloat(), camData["posY"].toFloat(), camData["posZ"].toFloat());
        Ogre::Vector3 target(camData["targetX"].toFloat(), camData["targetY"].toFloat(), camData["targetZ"].toFloat());

        BulletOgreEngine* btoEngine = static_cast<BulletOgreEngine*>(world->getFactory()->getEngineByName("BulletOgre"));
        Ogre::SceneManager* sceneManager = btoEngine->getOgreEngine()->getOgreSceneManager();
        Ogre::Camera * cam = sceneManager->getCamera("firstCamera");
        cam->setPosition(position);
        cam->setDirection(target - position);


        // -----------
        // -- Floor --
        // -----------

        QVariantMap floor = data["floor"].toMap();


        // flatland
        if(floor["type"].toString() == "flatland") {

            Ogre::Entity *ent;
            Ogre::Plane p;
            p.normal = Ogre::Vector3(0,1,0); p.d = 0;
            Ogre::MeshManager::getSingleton().createPlane("FloorPlane",
                                           Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                            p, 200000, 200000, 20, 20, true, 1, 9000, 9000,
                                                Ogre::Vector3::UNIT_Z);

           ent = sceneManager->createEntity("floorWorld", "FloorPlane");

           if(floor.contains("material")) {
                ent->setMaterialName(floor["material"].toString().toStdString());
           }

           sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
        }
        // else {
        // terrain


//        Ogre::Terrain *mTerrain;
//        Ogre::TerrainGlobalOptions *mGlobals;

//        mGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();
//        mGlobals->setMaxPixelError(8);

//        //mGlobals->setLightMapDirection(mLight->getDerivedDirection());
//        mGlobals->setCompositeMapDistance(3000);
//        mGlobals->setCompositeMapAmbient(sceneManager->getAmbientLight());
//        //mGlobals->setCompositeMapDiffuse(mLight->getDiffuseColour());

//        mTerrain = OGRE_NEW Ogre::Terrain(sceneManager);

//        Ogre::Image img;
//        img.load("heightmap.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

//        //Ogre::Terrain::ImportData imp;
//        Ogre::Terrain::ImportData& imp = mTerrainGroup->getDefaultImportSettings();
//        //imp.inputImage = &img;
//        imp.terrainSize = 513;
//        imp.worldSize = 8000;
//        imp.inputScale = 600;
//        imp.minBatchSize = 33;
//        imp.maxBatchSize = 65;

////        imp.layerList.resize(1);
////        imp.layerList[0].worldSize = 100;
////        imp.layerList[0].textureNames.push_back("grass_green-01_diffusespecular.dds");
////        imp.layerList[0].textureNames.push_back("grass_green-01_normalheight.dds");

//        Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
//        Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(8);

//        mTerrain->prepare(imp);
//        mTerrain->load();

//        mTerrain->freeTemporaryResources();

        // }



        // ------------
        // -- Spawns --
        // ------------

        foreach(Spawn* sp, this->spawns) {

            QString type = sp->getType();


            if(type == "position") {

                // Create Ogre Entity
                Ogre::Entity* entity = btoEngine->getOgreEngine()->getOgreSceneManager()->createEntity("cube.mesh");

                // Material
                entity->setMaterialName("GeneCraft/Spawn");

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
            else if(type == "minMaxArea" || type == "boxArea") {

                // Create Ogre Entity
                Ogre::Entity* entity = btoEngine->getOgreEngine()->getOgreSceneManager()->createEntity("cube.mesh");

                // Material
                entity->setMaterialName("GeneCraft/Spawn");

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
        }
    }
}
