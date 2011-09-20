#include "btoscene.h"

// Qt
#include <QVariantMap>
#include <QVariantList>

// ogre
#include "Ogre.h"

#include "bulletogre/bulletogreengine.h"
#include "ogre/ogreengine.h"

// factory
#include "btofactory.h"
#include "bulletogre/shapes/btobox.h"

// world
#include "btoworld.h"

// Terrain
#include "Terrain/OgreTerrain.h"
#include "Terrain/OgreTerrainGroup.h"


// Debug
#include <QDebug>
namespace GeneCraftCore {

    float terrain[129*129];
    btoScene::btoScene(btoWorld* world, QVariant sceneData, QObject *parent) :
        btScene(world, sceneData, parent)
    {
        mGlobals = NULL;
        mTerrain = NULL;
    }

    btoScene::~btoScene() {
        //delete mTerrainGroup;
        //delete mGlobals;
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
                    qDebug() << "first";
                    /*mGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();
                    mGlobals->setMaxPixelError(0);

                    Ogre::Vector3 lightdir(0.55, -0.3, 0.75);
                    lightdir.normalise();

                    Ogre::Light* light = btoEngine->getOgreEngine()->getOgreSceneManager()->createLight();
                    light->setType(Ogre::Light::LT_DIRECTIONAL);
                    light->setDirection(lightdir);
                    light->setDiffuseColour(Ogre::ColourValue::White);
                    light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));

                    btoEngine->getOgreEngine()->getOgreSceneManager()->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));

                    //mGlobals->setCompositeMapDistance(3000);

                    mGlobals->setLightMapDirection(light->getDerivedDirection());
                    mGlobals->setCompositeMapAmbient(Ogre::ColourValue(1,1,1));
                    mGlobals->setCompositeMapDiffuse(Ogre::ColourValue(1,1,1));

                    mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(btoEngine->getOgreEngine()->getOgreSceneManager(), Ogre::Terrain::ALIGN_X_Z, 129, 1000.0f);
                    //mTerrainGroup->setFilenameConvention(Ogre::String("BasicTutorial3Terrain"), Ogre::String("dat"));
                    mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);

                    for(int i = 0; i < 129; i++) {
                        for (int j = 0; j < 129; j++) {
                            terrain[j+i*129] = 20-sin(i/129.*M_PI)*20 + 20-sin(j/129.*M_PI)*20;
                        }
                    }



                    Ogre::Terrain::ImportData* imp = new Ogre::Terrain::ImportData();
                    imp->terrainSize = 129;
                    imp->worldSize = 1000.0;
                    imp->inputScale = 100.0;
                    imp->inputFloat = terrain;
                    imp->layerList.resize(3);

                    imp->layerList[0].worldSize = 100;
                    imp->layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
                    imp->layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds");

                    imp->layerList[1].worldSize = 30;
                    imp->layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
                    imp->layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");

                    imp->layerList[2].worldSize = 200;
                    imp->layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
                    imp->layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");

                    mTerrainGroup->defineTerrain(0, 0, imp);

                    Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
                    Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(8);
                    mTerrainGroup->loadAllTerrains(true);

                    if (true)
                    {
                        Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();
                        while(ti.hasMoreElements())
                        {
                            Ogre::Terrain* t = ti.getNext()->instance;
                            Ogre::TerrainLayerBlendMap* blendMap0 = t->getLayerBlendMap(1);
                            Ogre::TerrainLayerBlendMap* blendMap1 = t->getLayerBlendMap(2);
                            Ogre::Real minHeight0 = 70;
                            Ogre::Real fadeDist0 = 40;
                            Ogre::Real minHeight1 = 70;
                            Ogre::Real fadeDist1 = 15;
                            float* pBlend1 = blendMap1->getBlendPointer();
                            for (Ogre::uint16 y = 0; y < t->getLayerBlendMapSize(); ++y)
                            {
                                for (Ogre::uint16 x = 0; x < t->getLayerBlendMapSize(); ++x)
                                {
                                    Ogre::Real tx, ty;

                                    blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
                                    Ogre::Real height = t->getHeightAtTerrainPosition(tx, ty);
                                    Ogre::Real val = (height - minHeight0) / fadeDist0;
                                    val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);

                                    val = (height - minHeight1) / fadeDist1;
                                    val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
                                    *pBlend1++ = val;
                                }
                            }
                            blendMap0->dirty();
                            blendMap1->dirty();
                            blendMap0->update();
                            blendMap1->update();
                        }
                    }


                    mTerrainGroup->freeTemporaryResources();*/

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

           Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
           node->attachObject(ent);
           //node->rotate(Ogre::Vector3(1, 0, 0), Ogre::Radian(M_PI/10.));
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
