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

    // New entity
    btoBone::mNumEntitiesInstanced++;

    // Create Ogre Entity
    entityC = ogreEngine->getOgreSceneManager()->createEntity(
            "BoneCylinderEntity_" + StringConverter::toString(btoBone::mNumEntitiesInstanced),
            "Barrel.mesh");

    // Material
    entityC->setMaterialName("Sinbad/Teeth");
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
    entityS->setMaterialName("Sinbad/Eyes");
    entityS->setCastShadows(true);

    nodeS = parentNode->createChildSceneNode(Vector3(0, length/2+radiusArticulation, 0));

    Ogre::Vector3 size(radiusArticulation*2,radiusArticulation*2,radiusArticulation*2);

    // Scale
    boundingB = entityS->getBoundingBox(); // we need the bounding box of the box to be able to set the size of the Bullet-box
    scale = size / boundingB.getSize();
    nodeS->scale(scale);	// the cube is too big for us

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

    qDebug()<< getArticulationRadius() ;

    // Set relative position
    nodeS->setPosition(Vector3(0, length/2+getArticulationRadius(),0));


    Vector3 ogreSize(radius*2,length,radius*2);
    Vector3 scale = ogreSize / originalCylinderBB.getSize();
    nodeC->setScale(scale);
    nodeC->setPosition(Vector3(0,0,0));
}


void btoBone::setSelected(bool selected)
{
    if(selected) {

        entityC->setMaterialName("BaseWhite");
        entityS->setMaterialName("BaseWhite");

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
        entityC->setMaterialName("Sinbad/Teeth");
        entityS->setMaterialName("Sinbad/Teeth");
    }
}
}

