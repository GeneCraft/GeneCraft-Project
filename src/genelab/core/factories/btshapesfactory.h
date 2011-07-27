#ifndef BTSHAPESFACTORY_H
#define BTSHAPESFACTORY_H

#include "genecraftcoreclasses.h"
#include "LinearMath/btTransform.h"
#include "QVariant"

namespace GeneCraftCore {

class btShapesFactory
{
public:

    btShapesFactory();

    virtual btWorld* getWorld() {
        return world;
    }


    virtual void setWorld(btWorld* world) { this->world = world; }

    virtual btBox *createBox(btVector3 size, const btTransform &transform, const btScalar density, QVariant params = QVariant());
    virtual btSphere *createSphere(btScalar radius, const btTransform &transform, const btScalar density, QVariant params = QVariant());
    virtual btCylinder *createCylinder(btScalar radius, btScalar height, const btTransform &transform, const btScalar density, QVariant params = QVariant());
    virtual btBone  *createBone(btScalar length, btScalar radius, btScalar radiusArticulation, const btTransform &transform, QVariant params = QVariant());

protected:
    btWorld* world;
};

}

#endif // BTSHAPESFACTORY_H
