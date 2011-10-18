#include "btobox.h"

#include "world/btoworld.h"

#include "bulletogre/bulletogreengine.h"
#include "ogre/ogreengine.h"

namespace GeneCraftCore {

using namespace Ogre;

int btoBox::mNumEntitiesInstanced = 0;

btoBox::btoBox(btoWorld *world, BulletOgreEngine* btoEngine, btVector3 size, const btTransform &transform, const btScalar density)
    : btBox(world, size, transform, density)
{
    this->btoEngine = btoEngine;
    OgreEngine *ogreEngine = btoEngine->getOgreEngine();

    // New entity
    btoBox::mNumEntitiesInstanced++;

    // Create Ogre Entity
    entity = ogreEngine->getOgreSceneManager()->createEntity(
            "BoxEntity_" + StringConverter::toString(btoBox::mNumEntitiesInstanced),
            SceneManager::PT_CUBE);

    // Material
    entity->setMaterialName("GeneCraft/RockWall");
    entity->setCastShadows(true);

    // Attach
    node = ogreEngine->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode();

    // Scale
    AxisAlignedBox boundingB = entity->getBoundingBox(); // we need the bounding box of the box to be able to set the size of the Bullet-box
    Vector3 sizeBB = boundingB.getSize();
    sizeBB /= 2.0f;     // only the half needed
    //sizeBB *= 0.95f;    // Bullet margin is a bit bigger so we need a smaller size (Bullet 2.76 Physics SDK Manual page 18)
    Vector3 ogreSize(size.x(),size.y(),size.z());
    Vector3 scale = ogreSize  / boundingB.getSize();
    node->scale(scale);	// the cube is too big for us
    sizeBB *= scale;	// don't forget to scale down the Bullet-box too
}

btoBox::~btoBox() {
    this->btoEngine->removeBody(rigidBody, entity, node);
    this->node->removeAndDestroyAllChildren();
    this->btoEngine->getOgreEngine()->getOgreSceneManager()->destroyEntity(entity);
    this->btoEngine->getOgreEngine()->getOgreSceneManager()->destroySceneNode(node);
}

void btoBox::setup()
{
    btBox::setup();

    node->attachObject(entity);
    btoEngine->addBody(rigidBody,entity,node);
}

}