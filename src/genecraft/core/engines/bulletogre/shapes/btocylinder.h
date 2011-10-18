#ifndef BTOCYLINDER_H
#define BTOCYLINDER_H

#include "genecraftcoreclasses.h"
#include "bullet/shapes/btcylinder.h"
#include "Ogre.h"

namespace GeneCraftCore {

class btoCylinder : public btCylinder
{
public:

    btoCylinder(btoWorld *world, BulletOgreEngine *btoEngine, btScalar radius, btScalar height, const btTransform &transform, const btScalar density);
    void setup();
    void setSize(btScalar radius, btScalar height);

protected:

    BulletOgreEngine *btoEngine;
    Ogre::Entity *entity;
    Ogre::SceneNode *node;

private:
    static int mNumEntitiesInstanced;
};

}

#endif // BTOCYLINDER_H
