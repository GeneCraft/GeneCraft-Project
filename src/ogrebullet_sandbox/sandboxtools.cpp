#include "sandboxtools.h"

using namespace Ogre;

int SandboxTools::mNumEntitiesInstanced = 0;

SandboxTools::SandboxTools(QObject *parent) :
    QObject(parent)
{
}

OgreBulletDynamics::RigidBody *SandboxTools::addBox(GeneLabOgreBullet::OgreManager* ogre, GeneLabOgreBullet::BulletManager *bulletMgr,
                                                    Ogre::Vector3 position, Ogre::Vector3 size)
{
    // New entity
    SandboxTools::mNumEntitiesInstanced++;

    // Create Ogre Entity
    Entity *entity = ogre->getOgreSceneManager()->createEntity(
            "SandboxToolsBox" + StringConverter::toString(SandboxTools::mNumEntitiesInstanced),
            "cube.mesh");

    // Material
    entity->setMaterialName("Examples/Rockwall");
    entity->setCastShadows(true);

    // Attach
    SceneNode *node = ogre->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode();
    node->attachObject(entity);

    // Scale
    AxisAlignedBox boundingB = entity->getBoundingBox(); // we need the bounding box of the box to be able to set the size of the Bullet-box
    Vector3 sizeBB = boundingB.getSize();
    sizeBB /= 2.0f;     // only the half needed
    sizeBB *= 0.95f;    // Bullet margin is a bit bigger so we need a smaller size (Bullet 2.76 Physics SDK Manual page 18)
    Vector3 scale = size / boundingB.getSize();
    node->scale(scale);	// the cube is too big for us
    sizeBB *= scale;	// don't forget to scale down the Bullet-box too

    // Create Bullet collision shape and dynamic body
    OgreBulletCollisions::BoxCollisionShape *sceneBoxShape = new OgreBulletCollisions::BoxCollisionShape(sizeBB);
    OgreBulletDynamics::RigidBody *defaultBody = new OgreBulletDynamics::RigidBody(
            "SandboxToolsRigidBodyBox" + StringConverter::toString(SandboxTools::mNumEntitiesInstanced),
            bulletMgr->getWorld());

    // Finally create OgreBullet entity
    defaultBody->setShape(	node,
                                sceneBoxShape,
                                0.6f,			// dynamic body restitution
                                100.6f,			// dynamic body friction
                                1.0f, 			// dynamic bodymass
                                position,		// starting position of the box
                                Quaternion(0,0,0,1));   // orientation of the box

    return defaultBody;
}

OgreBulletDynamics::RigidBody *SandboxTools::addSphere(GeneLabOgreBullet::OgreManager* ogre, GeneLabOgreBullet::BulletManager *bulletMgr,
                                                    Ogre::Vector3 position, double rayon)
{

    // TODO: FIXME, IT'S ONLY A BOX WITH A SPHERE MESH !!!

    Ogre::Vector3 size(rayon,rayon,rayon);

    // New entity
    SandboxTools::mNumEntitiesInstanced++;

    // Create Ogre Entity
    Entity *entity = ogre->getOgreSceneManager()->createEntity(
            "SandboxToolsBox" + StringConverter::toString(SandboxTools::mNumEntitiesInstanced),
            "sphere.mesh");

    // Material
    entity->setMaterialName("Examples/Rockwall");
    entity->setCastShadows(true);

    // Attach
    SceneNode *node = ogre->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode();
    node->attachObject(entity);

    // Scale
    AxisAlignedBox boundingB = entity->getBoundingBox(); // we need the bounding box of the box to be able to set the size of the Bullet-box
    Vector3 sizeBB = boundingB.getSize();
    sizeBB /= 2.0f;     // only the half needed
    sizeBB *= 0.95f;    // Bullet margin is a bit bigger so we need a smaller size (Bullet 2.76 Physics SDK Manual page 18)
    Vector3 scale = size / boundingB.getSize();
    node->scale(scale);	// the cube is too big for us
    sizeBB *= scale;	// don't forget to scale down the Bullet-box too

    // Create Bullet collision shape and dynamic body
    OgreBulletCollisions::BoxCollisionShape *sceneBoxShape = new OgreBulletCollisions::BoxCollisionShape(sizeBB);
    OgreBulletDynamics::RigidBody *defaultBody = new OgreBulletDynamics::RigidBody(
            "SandboxToolsRigidBodyBox" + StringConverter::toString(SandboxTools::mNumEntitiesInstanced),
            bulletMgr->getWorld());

    // Finally create OgreBullet entity
    defaultBody->setShape(	node,
                                sceneBoxShape,
                                0.6f,			// dynamic body restitution
                                100.6f,			// dynamic body friction
                                0.1f, 			// dynamic bodymass
                                position,		// starting position of the box
                                Quaternion(0,0,0,1));   // orientation of the box

    return defaultBody;
}
