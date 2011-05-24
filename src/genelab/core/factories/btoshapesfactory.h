#ifndef BTOSHAPESFACTORY_H
#define BTOSHAPESFACTORY_H

#include "genelabcoreclasses.h"
#include "btshapesfactory.h"

namespace GeneLabCore {

class btoShapesFactory : public btShapesFactory
{
public:
    btoShapesFactory(BulletOgreEngine *btoEngine);

    virtual btBox *createBox(btVector3 size, btVector3 position, btVector3 rotation = btVector3(0,0,0));
    virtual btSphere *createSphere(btScalar radius, btVector3 position, btVector3 rotation = btVector3(0,0,0));
    virtual btCylinder *createCylinder(btScalar radius, btScalar height, btVector3 position, btVector3 rotation = btVector3(0,0,0));
protected:
    BulletOgreEngine *btoEngine;
};

}

#endif // BTOSHAPESFACTORY_H
