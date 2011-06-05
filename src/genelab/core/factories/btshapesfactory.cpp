#include "btshapesfactory.h"

#include "bullet/shapes/btbox.h"
#include "bullet/shapes/btsphere.h"
#include "bullet/shapes/btcylinder.h"
#include "bullet/shapes/btbone.h"

namespace GeneLabCore {

btShapesFactory::btShapesFactory(BulletEngine *btEngine)
{
    this->btEngine = btEngine;
}

btBox *btShapesFactory::createBox(btVector3 size, const btTransform &transform)
{
    return new btBox(btEngine,size, transform);
}

btSphere *btShapesFactory::createSphere(btScalar radius, const btTransform &transform)
{
    return new btSphere(btEngine,radius, transform);
}

btCylinder *btShapesFactory::createCylinder(btScalar radius, btScalar height, const btTransform &transform)
{
    return new btCylinder(btEngine,radius,height, transform);
}

btBone* btShapesFactory::createBone(btScalar length, btScalar radius, btScalar radiusArticulation, const btTransform &transform) {
    return new btBone(btEngine, length, radius, radiusArticulation, transform);
}

}
