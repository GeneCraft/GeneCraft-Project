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
    btSphere(BulletEngine *btEngine, btScalar radius, const btTransform &transform);
    virtual void setup();

private:

    void init(btScalar radius, btScalar density, const btTransform &transform);

protected:

    btSphereShape* shape;
    btDefaultMotionState* motionState;
};

}

#endif // BTSPHERE_H
