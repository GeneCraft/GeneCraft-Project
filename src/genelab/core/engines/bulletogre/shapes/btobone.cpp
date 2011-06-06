#include "btobone.h"

#include <QDebug>
#include "ogre/ogreengine.h"
#include "OgreSceneManager.h"
#include "bulletogre/bulletogreengine.h"

using namespace Ogre;

namespace GeneLabCore {
int btoBone::mNumEntitiesInstanced = 0;

btoBone::btoBone(BulletOgreEngine *btoEngine, btScalar length, btScalar radius,
                 btScalar radiusArticulation, const btTransform &transform) :
    btBone(btoEngine->getBulletEngine(), length, radius, radiusArticulation, transform)
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

    // Scale
    Vector3 ogreSize(radius*2,length,radius*2);
    Vector3 scale = ogreSize  / originalCylinderBB.getSize();
    nodeC->setScale(scale);	// the cube is too big for us
}


void btoBone::setSelected(bool selected)
{
    if(selected) {
        entityC->setMaterialName("BaseWhite");
        entityS->setMaterialName("BaseWhite");
    }
    else {
        entityC->setMaterialName("Sinbad/Teeth");
        entityS->setMaterialName("Sinbad/Teeth");
    }
}
}

