#ifndef BTOSHAPESFACTORY_H
#define BTOSHAPESFACTORY_H

#include "genelabcoreclasses.h"
#include "btshapesfactory.h"

namespace GeneLabCore {

class btoShapesFactory : public btShapesFactory
{
public:
    btoShapesFactory(BulletOgreEngine *btoEngine);

    virtual btBox *createBox(btVector3 size, const btTransform &transform);
    virtual btSphere *createSphere(btScalar radius, const btTransform &transform);
    virtual btCylinder *createCylinder(btScalar radius, btScalar height, const btTransform &transform);
    virtual btBone *createBone(btScalar length, btScalar radius, btScalar radiusArticulation, const btTransform &transform);
protected:
    BulletOgreEngine *btoEngine;
};

}

#endif // BTOSHAPESFACTORY_H
