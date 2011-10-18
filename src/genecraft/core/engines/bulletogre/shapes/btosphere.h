#ifndef BTOSPHERE_H
#define BTOSPHERE_H

#include "genecraftcoreclasses.h"
#include "bullet/shapes/btsphere.h"
#include "Ogre.h"
#include <QVariant>

namespace GeneCraftCore {

class btoSphere : public btSphere
{
public:
    btoSphere(btoWorld *world, BulletOgreEngine *btoEngine, btScalar radius, const btTransform &transform, const btScalar density, QVariant params = QVariant());
    ~btoSphere();
    void setup();
    void setSelected(bool selected);
    void setRadius(btScalar radius);

protected:

    BulletOgreEngine *btoEngine;
    Ogre::Entity *entity;
    Ogre::SceneNode *node;

    QString fixationMaterial;
    QString fixationSelectedMaterial;
    Ogre::AxisAlignedBox originalSphereBB;

private:
    static int mNumSpheresInstanced;
};

}

#endif // BTOSPHERE_H