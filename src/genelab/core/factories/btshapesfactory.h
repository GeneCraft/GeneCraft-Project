#ifndef BTSHAPESFACTORY_H
#define BTSHAPESFACTORY_H

#include "genelabcoreclasses.h"
#include "LinearMath/btTransform.h"

namespace GeneLabCore {

class btShapesFactory
{
public:

    btShapesFactory(BulletEngine *btEngine);

    BulletEngine *getBulletEngine()
    {
        return btEngine;
    }

    virtual btBox *createBox(btVector3 size, const btTransform &transform);
    virtual btSphere *createSphere(btScalar radius, const btTransform &transform);
    virtual btCylinder *createCylinder(btScalar radius, btScalar height, const btTransform &transform);
    virtual btBone  *createBone(btScalar length, btScalar radius, btScalar radiusArticulation, const btTransform &transform);
protected:
    BulletEngine *btEngine;
};

}

#endif // BTSHAPESFACTORY_H
