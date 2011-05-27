#ifndef BTOBONE_H
#define BTOBONE_H

#include "genelabcoreclasses.h"
#include "btbone.h"
#include "OGRE/Ogre.h"


namespace GeneLabCore {

class btoBone : public btBone
{
    Q_OBJECT
public:
    explicit btoBone(BulletOgreEngine *btoEngine, btScalar length, btScalar radius,
                     btScalar radiusArticulation, const btTransform &transform);
    void setup();

    protected:

        BulletOgreEngine *btoEngine;
        Ogre::SceneNode *parentNode;
        Ogre::Entity *entityC;
        Ogre::SceneNode *nodeC;
        Ogre::Entity *entityS;
        Ogre::SceneNode *nodeS;

    private:
        static int mNumEntitiesInstanced;
};
}

#endif // BTOBONE_H