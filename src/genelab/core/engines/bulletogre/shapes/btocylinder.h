#ifndef BTOCYLINDER_H
#define BTOCYLINDER_H

#include "genelabcoreclasses.h"
#include "btcylinder.h"
#include "OGRE/Ogre.h"

class btoCylinder : public btCylinder
{
public:

    btoCylinder(BulletOgreEngine *btoEngine, btScalar radius, btScalar height, btVector3 position, btVector3 rotation = btVector3(0,0,0));
    void setup();

protected:

    BulletOgreEngine *btoEngine;
    Ogre::Entity *entity;
    Ogre::SceneNode *node;

private:
    static int mNumEntitiesInstanced;
};

#endif // BTOCYLINDER_H
