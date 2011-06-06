#ifndef BTOCYLINDER_H
#define BTOCYLINDER_H

#include "genelabcoreclasses.h"
#include "bullet/shapes/btcylinder.h"
#include "OGRE/Ogre.h"

namespace GeneLabCore {

class btoCylinder : public btCylinder
{
public:

    btoCylinder(BulletOgreEngine *btoEngine, btScalar radius, btScalar height, const btTransform &transform);
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
