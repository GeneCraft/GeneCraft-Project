#ifndef BTSHAPESFACTORY_H
#define BTSHAPESFACTORY_H

#include "genelabcoreclasses.h"
#include "LinearMath/btVector3.h"

namespace GeneLabCore {

class btShapesFactory
{
public:

    btShapesFactory(BulletEngine *btEngine);

    inline BulletEngine *getBulletEngine()
    {
        return btEngine;
    }

    virtual btBox *createBox(btVector3 size, btVector3 position, btVector3 rotation = btVector3(0,0,0));
    virtual btSphere *createSphere(btScalar radius, btVector3 position, btVector3 rotation = btVector3(0,0,0));
    virtual btCylinder *createCylinder(btScalar radius, btScalar height, btVector3 position, btVector3 rotation = btVector3(0,0,0));

protected:
    BulletEngine *btEngine;
};

}

#endif // BTSHAPESFACTORY_H
