#include "btobone.h"
#include "world/btoworld.h"

#include "ogre/ogreengine.h"
#include "OgreSceneManager.h"
#include "bulletogre/bulletogreengine.h"

#include <QDebug>

using namespace Ogre;

namespace GeneCraftCore {
int btoBone::mNumEntitiesInstanced = 0;

btoBone::btoBone(btoWorld* world, BulletOgreEngine *btoEngine, btScalar length, btScalar radius,
                 btScalar radiusArticulation, const btTransform &transform) :
    btBone(world, length, radius, radiusArticulation, transform)
{
    this->btoEngine = btoEngine;
    OgreEngine *ogreEngine = btoEngine->getOgreEngine();

    boneMaterial = "GeneCraft/Bone";
    fixationMaterial = "GeneCraft/Fixation";

    boneSelectedMaterial = "GeneCraft/Bone_Selected";
    fixationSelectedMaterial = "GeneCraft/Fixation_Selected";

    // New entity
    btoBone::mNumEntitiesInstanced++;

    // Create Ogre Entity
    entityC = ogreEngine->getOgreSceneManager()->createEntity(
            "BoneCylinderEntity_" + StringConverter::toString(btoBone::mNumEntitiesInstanced),
            "Barrel.mesh");

    // Attach
    parentNode = ogreEngine->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode();
    nodeC = parentNode->createChildSceneNode();

    // Scale
    originalCylinderBB = entityC->getBoundingBox();
    Vector3 ogreSize(radius*2,length,radius*2);
    Vector3 scale = ogreSize  / originalCylinderBB.getSize();
    nodeC->setScale(scale);

    // Material
    entityC->setMaterialName(boneMaterial.toStdString());
    entityC->setCastShadows(true);

     // Create Ogre Entity
    entityS = ogreEngine->getOgreSceneManager()->createEntity(
            "BoneSphereEntity_" + StringConverter::toString(btoBone::mNumEntitiesInstanced),
            SceneManager::PT_SPHERE);



    nodeS = parentNode->createChildSceneNode(Vector3(0, length*0.5 + radiusArticulation, 0));

    // Scale
    Vector3 size(radiusArticulation*2,radiusArticulation*2,radiusArticulation*2);
    originalSphereBB = entityS->getBoundingBox();
    scale = size / originalSphereBB.getSize();
    nodeS->scale(scale);

    // Material
    entityS->setMaterialName(fixationMaterial.toStdString());
    entityS->setCastShadows(true);

    debugNode = getDebugAxes();
    debugNode->setVisible(false);
}

btoBone::~btoBone() {
    btoEngine->removeBody(rigidBody, entityC, parentNode);

    Ogre::SceneManager* scnMan = btoEngine->getOgreEngine()->getOgreSceneManager();

    parentNode->removeAndDestroyAllChildren();

    scnMan->destroySceneNode(parentNode);

    scnMan->destroyEntity(entityC);
    scnMan->destroyEntity(entityS);
    scnMan->destroyEntity(debugEntity);

}

void btoBone::setup()
{
    btBone::setup();

    nodeC->attachObject(entityC);
    nodeS->attachObject(entityS);
    btoEngine->addBody(rigidBody,entityC,parentNode);
}

void btoBone::setSize(btScalar radius, btScalar length)
{
    // set Bullet properties
    btBone::setSize(radius,length);

    nodeS->setPosition(Vector3(0, length*0.5 + getArticulationRadius(),0));
    Vector3 ogreSize(radius*2,length,radius*2);
    Vector3 scale = ogreSize / originalCylinderBB.getSize();
    nodeC->setScale(scale);
    nodeC->setPosition(Vector3(0,0,0));

    // Size of debug node (to show axis)
    debugNode->setScale(nodeC->getScale()*8);
}



void btoBone::setEndFixationRadius(btScalar radius)
{
    btBone::setEndFixationRadius(radius);

    Ogre::Vector3 size(radius*2,radius*2,radius*2);
    nodeS->setScale(size / originalSphereBB.getSize());
    nodeS->setPosition(Vector3(0, getLength()*0.5 + radius,0));
}

#include "OgreNode.h"
#include "OgreSceneNode.h"

void btoBone::setSelected(bool selected)
{
    if(selected) {

        entityC->setMaterialName(boneSelectedMaterial.toStdString());
        entityS->setMaterialName(fixationSelectedMaterial.toStdString());
        debugNode->setVisible(true, true);
    }
    else {
        entityC->setMaterialName(boneMaterial.toStdString());
        entityS->setMaterialName(fixationMaterial.toStdString());
        debugNode->setVisible(false);
    }
}

Ogre::SceneNode* btoBone::getDebugAxes() {
    String matName = "Ogre/Debug/AxesMat";
    Ogre::MaterialPtr mMat = MaterialManager::getSingleton().getByName(matName);
    if (mMat.isNull())
    {
            mMat = MaterialManager::getSingleton().create(matName, ResourceGroupManager::INTERNAL_RESOURCE_GROUP_NAME);
            Pass* p = mMat->getTechnique(0)->getPass(0);
            p->setLightingEnabled(false);
            p->setPolygonModeOverrideable(false);
            p->setVertexColourTracking(TVC_AMBIENT);
            p->setSceneBlending(SBT_TRANSPARENT_ALPHA);
            p->setCullingMode(CULL_NONE);
            p->setDepthWriteEnabled(false);
    }

    String meshName = "Ogre/Debug/AxesMesh";
    Ogre::MeshPtr mMeshPtr = MeshManager::getSingleton().getByName(meshName);
    if (mMeshPtr.isNull())
    {
            ManualObject mo("tmp");
            mo.begin(mMat->getName());
            /* 3 axes, each made up of 2 of these (base plane = XY)
 *   .------------|\
             *   '------------|/
 */
            mo.estimateVertexCount(7 * 2 * 3);
            mo.estimateIndexCount(3 * 2 * 3);
            Quaternion quat[6];
            ColourValue col[3];

            // x-axis
            quat[0] = Quaternion::IDENTITY;
            quat[1].FromAxes(Vector3::UNIT_X, Vector3::NEGATIVE_UNIT_Z, Vector3::UNIT_Y);
            col[0] = ColourValue::Red;
            col[0].a = 0.8;
            // y-axis
            quat[2].FromAxes(Vector3::UNIT_Y, Vector3::NEGATIVE_UNIT_X, Vector3::UNIT_Z);
            quat[3].FromAxes(Vector3::UNIT_Y, Vector3::UNIT_Z, Vector3::UNIT_X);
            col[1] = ColourValue::Green;
            col[1].a = 0.8;
            // z-axis
            quat[4].FromAxes(Vector3::UNIT_Z, Vector3::UNIT_Y, Vector3::NEGATIVE_UNIT_X);
            quat[5].FromAxes(Vector3::UNIT_Z, Vector3::UNIT_X, Vector3::UNIT_Y);
            col[2] = ColourValue::Blue;
            col[2].a = 0.8;

            Vector3 basepos[7] =
            {
                    // stalk
                    Vector3(0, 0.05, 0),
                    Vector3(0, -0.05, 0),
                    Vector3(0.7, -0.05, 0),
                    Vector3(0.7, 0.05, 0),
                    // head
                    Vector3(0.7, -0.15, 0),
                    Vector3(1, 0, 0),
                    Vector3(0.7, 0.15, 0)
            };


            // vertices
            // 6 arrows
            for (size_t i = 0; i < 6; ++i)
            {
                    // 7 points
                    for (size_t p = 0; p < 7; ++p)
                    {
                            Vector3 pos = quat[i] * basepos[p];
                            mo.position(pos);
                            mo.colour(col[i / 2]);
                    }
            }

            // indices
            // 6 arrows
            for (size_t i = 0; i < 6; ++i)
            {
                    size_t base = i * 7;
                    mo.triangle(base + 0, base + 1, base + 2);
                    mo.triangle(base + 0, base + 2, base + 3);
                    mo.triangle(base + 4, base + 5, base + 6);
            }

            mo.end();

            mMeshPtr = mo.convertToMesh(meshName, ResourceGroupManager::INTERNAL_RESOURCE_GROUP_NAME);

    }
    // Create Ogre Entity
    debugEntity = btoEngine->getOgreEngine()->getOgreSceneManager()->createEntity(meshName);

   // Material
   debugEntity->setMaterial(mMat);
   //debugEntity->setCastShadows(false);

   Ogre::SceneNode* nodeS = parentNode->createChildSceneNode(Vector3(0, 0, 0));
   nodeS->attachObject(debugEntity);
   nodeS->setScale(nodeC->getScale()*8);

    return nodeS;
}

}

