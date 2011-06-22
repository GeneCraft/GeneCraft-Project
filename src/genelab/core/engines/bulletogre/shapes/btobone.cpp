#include "btobone.h"
#include "world/btoworld.h"

#include <QDebug>
#include "ogre/ogreengine.h"
#include "OgreSceneManager.h"
#include "bulletogre/bulletogreengine.h"

using namespace Ogre;

namespace GeneLabCore {
int btoBone::mNumEntitiesInstanced = 0;

btoBone::btoBone(btoWorld* world, BulletOgreEngine *btoEngine, btScalar length, btScalar radius,
                 btScalar radiusArticulation, const btTransform &transform) :
    btBone(world, length, radius, radiusArticulation, transform)
{
    this->btoEngine = btoEngine;
    OgreEngine *ogreEngine = btoEngine->getOgreEngine();

    boneMaterial = "GeneLab/Bone";
    fixationMaterial = "GeneLab/Fixation";

    boneSelectedMaterial = "GeneLab/Bone_Selected";
    fixationSelectedMaterial = "GeneLab/Fixation_Selected";

    // New entity
    btoBone::mNumEntitiesInstanced++;

    // Create Ogre Entity
    entityC = ogreEngine->getOgreSceneManager()->createEntity(
            "BoneCylinderEntity_" + StringConverter::toString(btoBone::mNumEntitiesInstanced),
            "Barrel.mesh");

    // Material
    entityC->setMaterialName(boneMaterial.toStdString());
    entityC->setCastShadows(true);

    // Attach
    parentNode = ogreEngine->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode();
    nodeC = parentNode->createChildSceneNode();

    // Scale
    originalCylinderBB = entityC->getBoundingBox();
    AxisAlignedBox boundingB = entityC->getBoundingBox(); // we need the bounding box of the box to be able to set the size of the Bullet-box
    Vector3 ogreSize(radius*2,length,radius*2);
    Vector3 scale = ogreSize  / boundingB.getSize();
    nodeC->scale(scale);	// the cube is too big for us

     // Create Ogre Entity
    entityS = ogreEngine->getOgreSceneManager()->createEntity(
            "BoneSphereEntity_" + StringConverter::toString(btoBone::mNumEntitiesInstanced),
            "sphere.mesh");

    // Material
    entityS->setMaterialName(fixationMaterial.toStdString());
    entityS->setCastShadows(true);

    nodeS = parentNode->createChildSceneNode(Vector3(0, length/2+radiusArticulation, 0));

    Ogre::Vector3 size(radiusArticulation*2,radiusArticulation*2,radiusArticulation*2);

    // Scale
    boundingB = entityS->getBoundingBox(); // we need the bounding box of the box to be able to set the size of the Bullet-box
    scale = size / boundingB.getSize();
    nodeS->scale(scale);	// the cube is too big for us
    debugNode = getDebugAxes();
    debugNode->setVisible(false);

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
    btBone::setSize(radius,length);

    //qDebug()<< getArticulationRadius() ;

    // Set relative position
    nodeS->setPosition(Vector3(0, length/2+getArticulationRadius(),0));


    Vector3 ogreSize(radius*2,length,radius*2);
    Vector3 scale = ogreSize / originalCylinderBB.getSize();
    nodeC->setScale(scale);
    nodeC->setPosition(Vector3(0,0,0));

    debugNode->setScale(nodeC->getScale()*8);
}

#include "OgreNode.h"
#include "OgreSceneNode.h"

void btoBone::setSelected(bool selected)
{
    if(selected) {

        entityC->setMaterialName(boneSelectedMaterial.toStdString());
        entityS->setMaterialName(fixationSelectedMaterial.toStdString());
        debugNode->setVisible(true, true);

        /*
        materialName - material i am wanting to fade
        fade - float holding the fade value, 0 being completey transparent 1 being solid
        */

//        MaterialPtr tempMat = MaterialManager::getSingleton().getByName("Sinbad/Teeth");
//        TextureUnitState *tempTex = tempMat.get()->getTechnique(0)->getPass(0)->createTextureUnitState();
//        float fade = 0.0;
//        tempTex->setAlphaOperation(LBX_MODULATE, LBS_TEXTURE, LBS_MANUAL, 1.0f, fade);

//        entityC->setMaterial(tempMat);
//        entityS->setMaterial(tempMat);

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
    Ogre::Entity* entityDebug = btoEngine->getOgreEngine()->getOgreSceneManager()->createEntity(meshName);

   // Material
   entityDebug->setMaterial(mMat);
   entityDebug->setCastShadows(false);

   Ogre::SceneNode* nodeS = parentNode->createChildSceneNode(Vector3(0, 0, 0));
   nodeS->attachObject(entityDebug);
   nodeS->setScale(nodeC->getScale()*8);

    return nodeS;
}
}

