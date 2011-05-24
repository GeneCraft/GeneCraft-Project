#ifndef BTSPHERE_H
#define BTSPHERE_H

#include "genelabcoreclasses.h"
#include "btshape.h"
#include "BulletCollision/CollisionShapes/btSphereShape.h"
#include "LinearMath/btDefaultMotionState.h"

namespace GeneLabCore {

class btSphere : public btShape
{
public:
    btSphere(BulletEngine *btEngine, btScalar radius, btVector3 position, btVector3 rotation = btVector3(0,0,0));
    virtual void setup();

private:

    void init(btScalar radius, btVector3 position, btScalar density, btVector3 EulerRotation);

protected:

    btSphereShape* shape;
    btDefaultMotionState* motionState;
};

}

#endif // BTSPHERE_H
