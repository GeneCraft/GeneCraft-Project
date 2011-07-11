#ifndef BTOBONE_H
#define BTOBONE_H

#include "genelabcoreclasses.h"
#include "bullet/shapes/btbone.h"
#include "Ogre.h"


namespace GeneLabCore {

class btoBone : public btBone
{

public:
    explicit btoBone(btoWorld *world, BulletOgreEngine *btoEngine, btScalar length, btScalar radius,
                     btScalar radiusArticulation, const btTransform &transform);
    ~btoBone();
    void setup();
    void setSize(btScalar radius, btScalar height);
    void setSelected(bool selected);
    void setEndFixationRadius(btScalar radius);

    protected:

        BulletOgreEngine *btoEngine;
        Ogre::SceneNode *parentNode;
        Ogre::Entity *entityC;
        Ogre::SceneNode *nodeC;
        Ogre::Entity *entityS;
        Ogre::Entity *debugEntity;
        Ogre::SceneNode *nodeS;
        Ogre::SceneNode *debugNode;
        Ogre::SceneNode *getDebugAxes();

    private:

        static int mNumEntitiesInstanced;
        Ogre::AxisAlignedBox originalCylinderBB;


        QString boneMaterial;
        QString fixationMaterial;

        QString boneSelectedMaterial;
        QString fixationSelectedMaterial;

        Ogre::AxisAlignedBox originalSphereBB;

};
}

#endif // BTOBONE_H
