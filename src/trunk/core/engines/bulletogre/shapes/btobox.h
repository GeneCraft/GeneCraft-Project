#ifndef BTOBOX_H
#define BTOBOX_H

#include "genecraftcoreclasses.h"
#include "bullet/shapes/btbox.h"
#include "Ogre.h"

namespace GeneCraftCore {

class btoBox : public btBox
{
public:

    btoBox(btoWorld *world, BulletOgreEngine *btoEngine, btVector3 size, const btTransform &transform, const btScalar density);
    void setup();

protected:

    BulletOgreEngine *btoEngine;
    Ogre::Entity *entity;
    Ogre::SceneNode *node;

private:
    static int mNumEntitiesInstanced;
};

}
#endif // BTOBOX_H
