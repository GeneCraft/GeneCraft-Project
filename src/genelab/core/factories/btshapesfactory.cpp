#include "btshapesfactory.h"

#include "bullet/shapes/btbox.h"
#include "bullet/shapes/btsphere.h"
#include "bullet/shapes/btcylinder.h"
#include "bullet/shapes/btbone.h"

namespace GeneLabCore {

btShapesFactory::btShapesFactory(btWorld *world)
{
    this->world = world;
}

btBox *btShapesFactory::createBox(btVector3 size, const btTransform &transform, const btScalar density)
{
    return new btBox(world, size, transform, density);
}

btSphere *btShapesFactory::createSphere(btScalar radius, const btTransform &transform)
{
    return new btSphere(world, radius, transform);
}

btCylinder *btShapesFactory::createCylinder(btScalar radius, btScalar height, const btTransform &transform)
{
    return new btCylinder(world, radius, height, transform);
}

btBone* btShapesFactory::createBone(btScalar length, btScalar radius, btScalar radiusArticulation, const btTransform &transform) {
    return new btBone(world, length, radius, radiusArticulation, transform);
}

}
