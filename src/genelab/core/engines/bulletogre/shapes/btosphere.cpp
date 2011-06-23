#include "btosphere.h"

#include "world/btoworld.h"

#include <QDebug>
#include "ogre/ogreengine.h"
#include "OgreSceneManager.h"
#include "bulletogre/bulletogreengine.h"


namespace GeneLabCore {

using namespace Ogre;

int btoSphere::mNumSpheresInstanced = 0;

btoSphere::btoSphere(btoWorld *world, BulletOgreEngine *btoEngine, btScalar radius, const btTransform &transform)
    :btSphere(world, radius, transform)
{
    this->btoEngine = btoEngine;
    OgreEngine *ogreEngine = btoEngine->getOgreEngine();

    fixationMaterial = "GeneLab/Fixation";
    fixationSelectedMaterial = "GeneLab/Fixation_Selected";

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
    entity->setMaterialName(fixationMaterial.toStdString());
    entity->setCastShadows(true);

    node = ogreEngine->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode();

    // Scale
    originalSphereBB = entity->getBoundingBox(); // we need the bounding box of the box to be able to set the size of the Bullet-box
    Vector3 sizeBB = originalSphereBB.getSize();
    sizeBB /= 2.0f;     // only the half needed
    sizeBB *= 0.95f;    // Bullet margin is a bit bigger so we need a smaller size (Bullet 2.76 Physics SDK Manual page 18)
    Vector3 scale = size / originalSphereBB.getSize();
    node->scale(scale);	// the cube is too big for us
    sizeBB *= scale;	// don't forget to scale down the Bullet-box too
}

void btoSphere::setup()
{
    btSphere::setup();

    node->attachObject(entity);
    btoEngine->addBody(rigidBody,entity,node);
}

void btoSphere::setSelected(bool selected)
{
    if(selected)
        entity->setMaterialName(fixationSelectedMaterial.toStdString());
    else
        entity->setMaterialName(fixationMaterial.toStdString());
}

void btoSphere::setRadius(btScalar radius)
{
    // set Bullet properties
    btSphere::setRadius(radius);

    // Set relative positions
    Vector3 ogreSize(radius*2,radius*2,radius*2);
    Vector3 scale = ogreSize / originalSphereBB.getSize();
    node->setScale(scale);
    node->setPosition(Vector3(0,0,0));
}

}
