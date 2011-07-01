#include "btoshapesfactory.h"

#include "world/btoworld.h"

#include "bulletogre/bulletogreengine.h"
#include "bulletogre/shapes/btobox.h"
#include "bulletogre/shapes/btosphere.h"
#include "bulletogre/shapes/btocylinder.h"
#include "bulletogre/shapes/btobone.h"

namespace GeneLabCore {

btoShapesFactory::btoShapesFactory(btoWorld *world, BulletOgreEngine *btoEngine) : btShapesFactory(world)
{
    this->btoEngine = btoEngine;
}

btBox *btoShapesFactory::createBox(btVector3 size, const btTransform &transform, const btScalar density)
{
    return new btoBox((btoWorld*)world, btoEngine, size, transform, density);
}

btSphere *btoShapesFactory::createSphere(btScalar radius, const btTransform &transform)
{
    return new btoSphere((btoWorld*)world, btoEngine, radius, transform);
}

btCylinder *btoShapesFactory::createCylinder(btScalar radius, btScalar height, const btTransform &transform)
{
    return new btoCylinder((btoWorld*)world, btoEngine, radius, height, transform);
}

btBone* btoShapesFactory::createBone(btScalar length, btScalar radius, btScalar radiusArticulation, const btTransform &transform) {
    return new btoBone((btoWorld*)world, btoEngine, length, radius, radiusArticulation, transform);
}

}
