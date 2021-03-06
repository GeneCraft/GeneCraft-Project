#include "btshapesfactory.h"

#include "bullet/shapes/btbox.h"
#include "bullet/shapes/btsphere.h"
#include "bullet/shapes/btcylinder.h"
#include "bullet/shapes/btbone.h"

namespace GeneCraftCore {

btShapesFactory::btShapesFactory()
{
}

btBox *btShapesFactory::createBox(btVector3 size, const btTransform &transform, const btScalar density, QVariant)
{
    return new btBox(world, size, transform, density);
}

btSphere *btShapesFactory::createSphere(btScalar radius, const btTransform &transform, const btScalar density, QVariant)
{
    return new btSphere(world, radius, transform, density);
}

btCylinder *btShapesFactory::createCylinder(btScalar radius, btScalar height, const btTransform &transform, const btScalar density, QVariant)
{
    return new btCylinder(world, radius, height, transform, density);
}

btBone* btShapesFactory::createBone(btScalar length, btScalar radius, btScalar radiusArticulation, const btTransform &transform, QVariant) {
    return new btBone(world, length, radius, radiusArticulation, transform);
}

}
