#include "btshapesfactory.h"

#include "btbox.h"
#include "btsphere.h"
#include "btcylinder.h"

namespace GeneLabCore {

btShapesFactory::btShapesFactory(BulletEngine *btEngine)
{
    this->btEngine = btEngine;
}

btBox *btShapesFactory::createBox(btVector3 size, btVector3 position, btVector3 rotation)
{
    return new btBox(btEngine,size,position,rotation);
}

btSphere *btShapesFactory::createSphere(btScalar radius, btVector3 position, btVector3 rotation)
{
    return new btSphere(btEngine,radius,position,rotation);
}

btCylinder *btShapesFactory::createCylinder(btScalar radius, btScalar height, btVector3 position, btVector3 rotation)
{
    return new btCylinder(btEngine,radius,height,position,rotation);
}

}
