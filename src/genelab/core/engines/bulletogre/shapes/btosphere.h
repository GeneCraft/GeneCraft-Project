#ifndef BTOSPHERE_H
#define BTOSPHERE_H

#include "genelabcoreclasses.h"
#include "bullet/shapes/btsphere.h"
#include "Ogre.h"

namespace GeneLabCore {

class btoSphere : public btSphere
{
public:
    btoSphere(btoWorld *world, BulletOgreEngine *btoEngine, btScalar radius, const btTransform &transform);
    void setup();
    void setSelected(bool selected);

protected:

    BulletOgreEngine *btoEngine;
    Ogre::Entity *entity;
    Ogre::SceneNode *node;

    QString fixationMaterial;
    QString fixationSelectedMaterial;

private:
    static int mNumSpheresInstanced;
};

}

#endif // BTOSPHERE_H
