#ifndef BTOSHAPESFACTORY_H
#define BTOSHAPESFACTORY_H

#include "genelabcoreclasses.h"
#include "btshapesfactory.h"
#include "world/btoworld.h"

namespace GeneLabCore {

class btoShapesFactory : public btShapesFactory
{
public:
    btoShapesFactory(BulletOgreEngine *btoEngine);

    virtual void setWorld(btoWorld* world) { this->world = world; }

    virtual btBox *createBox(btVector3 size, const btTransform &transform, const btScalar density, QVariant params = QVariant());
    virtual btSphere *createSphere(btScalar radius, const btTransform &transform, QVariant params = QVariant());
    virtual btCylinder *createCylinder(btScalar radius, btScalar height, const btTransform &transform, QVariant params = QVariant());
    virtual btBone *createBone(btScalar length, btScalar radius, btScalar radiusArticulation, const btTransform &transform, QVariant params = QVariant());
protected:
    BulletOgreEngine *btoEngine;
};

}

#endif // BTOSHAPESFACTORY_H
