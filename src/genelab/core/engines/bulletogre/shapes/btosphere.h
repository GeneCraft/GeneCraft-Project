#ifndef BTOSPHERE_H
#define BTOSPHERE_H

#include "genelabcoreclasses.h"
#include "btsphere.h"
#include "OGRE/Ogre.h" // AHAHAHAHAHAHAHAHAHAAHAH mettre la classe dans genelabcoreclasses.h

class btoSphere : public btSphere
{
public:
    btoSphere(BulletOgreEngine *btoEngine, btScalar radius, btVector3 position, btVector3 rotation = btVector3(0,0,0));
    void setup();

protected:

    BulletOgreEngine *btoEngine;
    Ogre::Entity *entity;
    Ogre::SceneNode *node;

private:
    static int mNumSpheresInstanced;
};

#endif // BTOSPHERE_H
