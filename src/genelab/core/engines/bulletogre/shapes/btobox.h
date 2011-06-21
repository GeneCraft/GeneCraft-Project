#ifndef BTOBOX_H
#define BTOBOX_H

#include "genelabcoreclasses.h"
#include "bullet/shapes/btbox.h"
#include "OGRE/Ogre.h"

namespace GeneLabCore {

class btoBox : public btBox
{
public:

    btoBox(btoWorld *world, BulletOgreEngine *btoEngine, btVector3 size, const btTransform &transform);
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
