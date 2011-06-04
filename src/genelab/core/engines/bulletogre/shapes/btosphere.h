#ifndef BTOSPHERE_H
#define BTOSPHERE_H

#include "genelabcoreclasses.h"
#include "btsphere.h"
#include "OGRE/Ogre.h" // AHAHAHAHAHAHAHAHAHAAHAH mettre la classe dans genelabcoreclasses.h

namespace GeneLabCore {

class btoSphere : public btSphere
{
public:
    btoSphere(BulletOgreEngine *btoEngine, btScalar radius, const btTransform &transform);
    void setup();
    void setSelected(bool selected);

protected:

    BulletOgreEngine *btoEngine;
    Ogre::Entity *entity;
    Ogre::SceneNode *node;

private:
    static int mNumSpheresInstanced;
};

}

#endif // BTOSPHERE_H
