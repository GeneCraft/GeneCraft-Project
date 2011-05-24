#include "btoshapesfactory.h"

#include "bulletogreengine.h"
#include "btobox.h"
#include "btosphere.h"
#include "btocylinder.h"

namespace GeneLabCore {

btoShapesFactory::btoShapesFactory(BulletOgreEngine *btoEngine) : btShapesFactory(btoEngine->getBulletEngine())
{
    this->btoEngine = btoEngine;
}

btBox *btoShapesFactory::createBox(btVector3 size, btVector3 position, btVector3 rotation)
{
    return new btoBox(btoEngine,size,position,rotation);
}

btSphere *btoShapesFactory::createSphere(btScalar radius, btVector3 position, btVector3 rotation)
{
    return new btoSphere(btoEngine,radius,position,rotation);
}

btCylinder *btoShapesFactory::createCylinder(btScalar radius, btScalar height, btVector3 position, btVector3 rotation)
{
    return new btoCylinder(btoEngine,radius,height,position,rotation);
}

}
