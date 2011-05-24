#include "btosphere.h"

#include <QDebug>
#include "ogreengine.h"
#include "OgreSceneManager.h"
#include "bulletogreengine.h"


namespace GeneLabCore {

using namespace Ogre;

int btoSphere::mNumSpheresInstanced = 0;

btoSphere::btoSphere(BulletOgreEngine *btoEngine, btScalar radius, btVector3 position, btVector3 rotation)
    :btSphere(btoEngine->getBulletEngine(),radius,position,rotation)
{
    this->btoEngine = btoEngine;
    OgreEngine *ogreEngine = btoEngine->getOgreEngine();

    // -------------------
    // -- create sphere --
    // -------------------
    Ogre::Vector3 size(radius*2,radius*2,radius*2);

    // New entity
    btoSphere::mNumSpheresInstanced++;

    // Create Ogre Entity
    entity = ogreEngine->getOgreSceneManager()->createEntity(
            "SphereEntity_" + StringConverter::toString(btoSphere::mNumSpheresInstanced),
            "sphere.mesh");

    // Material
    entity->setMaterialName("Examples/Rockwall");
    entity->setCastShadows(true);

    node = ogreEngine->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode();

    // Scale
    AxisAlignedBox boundingB = entity->getBoundingBox(); // we need the bounding box of the box to be able to set the size of the Bullet-box
    Vector3 sizeBB = boundingB.getSize();
    sizeBB /= 2.0f;     // only the half needed
    sizeBB *= 0.95f;    // Bullet margin is a bit bigger so we need a smaller size (Bullet 2.76 Physics SDK Manual page 18)
    Vector3 scale = size / boundingB.getSize();
    node->scale(scale);	// the cube is too big for us
    sizeBB *= scale;	// don't forget to scale down the Bullet-box too
}

void btoSphere::setup()
{
    btSphere::setup();

    qDebug() << "btoSphere::setup()";

    node->attachObject(entity);
    btoEngine->addBody(rigidBody,entity,node);
}

}
