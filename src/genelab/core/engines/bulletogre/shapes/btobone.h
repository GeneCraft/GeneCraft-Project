#ifndef BTOBONE_H
#define BTOBONE_H

#include "genelabcoreclasses.h"
#include "bullet/shapes/btbone.h"
#include "Ogre.h"


namespace GeneLabCore {

class btoBone : public btBone
{
    Q_OBJECT
public:
    explicit btoBone(btoWorld *world, BulletOgreEngine *btoEngine, btScalar length, btScalar radius,
                     btScalar radiusArticulation, const btTransform &transform);
    void setup();
    void setSize(btScalar radius, btScalar height);
    void setSelected(bool selected);

    protected:

        BulletOgreEngine *btoEngine;
        Ogre::SceneNode *parentNode;
        Ogre::Entity *entityC;
        Ogre::SceneNode *nodeC;
        Ogre::Entity *entityS;
        Ogre::SceneNode *nodeS;

    private:

        static int mNumEntitiesInstanced;
        Ogre::AxisAlignedBox originalCylinderBB;
};
}

#endif // BTOBONE_H
