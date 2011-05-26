#include "btoshapesfactory.h"

#include "bulletogreengine.h"
#include "btobox.h"
#include "btosphere.h"
#include "btocylinder.h"
#include "btobone.h"

namespace GeneLabCore {

btoShapesFactory::btoShapesFactory(BulletOgreEngine *btoEngine) : btShapesFactory(btoEngine->getBulletEngine())
{
    this->btoEngine = btoEngine;
}

btBox *btoShapesFactory::createBox(btVector3 size, const btTransform &transform)
{
    return new btoBox(btoEngine,size,transform);
}

btSphere *btoShapesFactory::createSphere(btScalar radius, const btTransform &transform)
{
    return new btoSphere(btoEngine,radius,transform);
}

btCylinder *btoShapesFactory::createCylinder(btScalar radius, btScalar height, const btTransform &transform)
{
    return new btoCylinder(btoEngine,radius,height,transform);
}

btBone* btoShapesFactory::createBone(btScalar length, btScalar radius, btScalar radiusArticulation, const btTransform &transform) {
    return new btoBone(btoEngine, length, radius, radiusArticulation, transform);
}

}
