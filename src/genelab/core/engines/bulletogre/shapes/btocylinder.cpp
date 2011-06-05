#include "btocylinder.h"

#include "bulletogre/bulletogreengine.h"
#include "ogre/ogreengine.h"

namespace GeneLabCore {

using namespace Ogre;

int btoCylinder::mNumEntitiesInstanced = 0;

btoCylinder::btoCylinder(BulletOgreEngine *btoEngine, btScalar radius, btScalar height, const btTransform &transform)
    : btCylinder(btoEngine->getBulletEngine(),radius,height,transform)
{
    this->btoEngine = btoEngine;
    OgreEngine *ogreEngine = btoEngine->getOgreEngine();

    // New entity
    btoCylinder::mNumEntitiesInstanced++;

    // Create Ogre Entity
    entity = ogreEngine->getOgreSceneManager()->createEntity(
            "CylinderEntity_" + StringConverter::toString(btoCylinder::mNumEntitiesInstanced),
            "Barrel.mesh");

    // Material
    entity->setMaterialName("Examples/Rockwall");
    entity->setCastShadows(true);

    // Attach
    node = ogreEngine->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode();

    // Scale
    AxisAlignedBox boundingB = entity->getBoundingBox(); // we need the bounding box of the box to be able to set the size of the Bullet-box
    Vector3 sizeBB = boundingB.getSize();
    sizeBB /= 2.0f;     // only the half needed
    sizeBB *= 0.95f;    // Bullet margin is a bit bigger so we need a smaller size (Bullet 2.76 Physics SDK Manual page 18)
    Vector3 ogreSize(radius*2,height,radius*2);
    Vector3 scale = ogreSize  / boundingB.getSize();
    node->scale(scale);	// the cube is too big for us
    sizeBB *= scale;	// don't forget to scale down the Bullet-box too
}

void btoCylinder::setup()
{
    btCylinder::setup();

    node->attachObject(entity);
    btoEngine->addBody(rigidBody,entity,node);
}

}
