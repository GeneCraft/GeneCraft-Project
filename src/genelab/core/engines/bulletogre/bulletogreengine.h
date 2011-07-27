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

    OgreBody() {
        this->rigidBody = NULL;
        this->entity = NULL;
        this->node = NULL;
    }

    OgreBody(btRigidBody * rigidBody,Ogre::Entity *entity, Ogre::SceneNode *node)
    {
        this->rigidBody = rigidBody;
        this->entity    = entity;
        this->node      = node;
    }

    OgreBody(const OgreBody &b) {
        this->rigidBody = b.rigidBody;
        this->entity    = b.entity;
        this->node      = b.node;
    }

    bool operator ==(OgreBody b) {
        return this->rigidBody == b.rigidBody
            && this->entity == b.entity
            && this->node == b.node;
    }

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
    OgreEngine *getOgreEngine()     { return this->ogreEngine;  }
    BulletEngine *getBulletEngine() { return this->btEngine;    }

    void clearAll();

    void step();

private:

    BulletEngine *btEngine;
    OgreEngine *ogreEngine;
    QList<OgreBody> bodies;
};
}
#endif // BULLETOGREENGINE_H
