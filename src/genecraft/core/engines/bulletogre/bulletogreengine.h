#ifndef BULLETOGREENGINE_H
#define BULLETOGREENGINE_H

#include "genecraftcoreclasses.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "engine.h"
#include "Ogre.h"


namespace GeneCraftCore {

/**
 * Class used to links ogre objects to bullet objects
 */
class OgreBody
{
public:

    OgreBody();
    OgreBody(btRigidBody * rigidBody,Ogre::Entity *entity, Ogre::SceneNode *node);

    OgreBody(const OgreBody &b);

    bool operator ==(OgreBody b);

    btRigidBody *rigidBody;
    Ogre::Entity *entity;
    Ogre::SceneNode *node;
};


class BulletOgreEngine : public Engine
{
public:

    BulletOgreEngine(BulletEngine *btEngine, OgreEngine *ogreEngine);
    void addBody(btRigidBody * rigidBody, Ogre::Entity *entity, Ogre::SceneNode *node);
    void removeBody(btRigidBody * rigidBody, Ogre::Entity* entity, Ogre::SceneNode * node);
    OgreEngine *getOgreEngine();
    BulletEngine *getBulletEngine();

    void clearAll();

    void step();

private:

    BulletEngine *btEngine;
    OgreEngine *ogreEngine;
    QList<OgreBody> bodies;

    int nbSteps;
};
}
#endif // BULLETOGREENGINE_H
