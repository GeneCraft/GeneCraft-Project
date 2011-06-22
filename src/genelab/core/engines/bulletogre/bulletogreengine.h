#ifndef BULLETOGREENGINE_H
#define BULLETOGREENGINE_H

#include "genelabcoreclasses.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "engine.h"
#include "Ogre.h"


namespace GeneLabCore {

/**
 * Class used to links ogre objects to bullet objects
 */
class OgreBody
{
public:

    OgreBody(btRigidBody * rigidBody,Ogre::Entity *entity, Ogre::SceneNode *node)
    {
        this->rigidBody = rigidBody;
        this->entity    = entity;
        this->node      = node;
    }

    btRigidBody *rigidBody;
    Ogre::Entity *entity;
    Ogre::SceneNode *node;
};


class BulletOgreEngine : public Engine
{
public:

    BulletOgreEngine(BulletEngine *btEngine, OgreEngine *ogreEngine);
    void addBody(btRigidBody * rigidBody,Ogre::Entity *entity, Ogre::SceneNode *node);

    OgreEngine *getOgreEngine()     { return this->ogreEngine;  }
    BulletEngine *getBulletEngine() { return this->btEngine;    }

    void step();

private:

    BulletEngine *btEngine;
    OgreEngine *ogreEngine;
    QList<OgreBody *> bodies;
};
}
#endif // BULLETOGREENGINE_H
