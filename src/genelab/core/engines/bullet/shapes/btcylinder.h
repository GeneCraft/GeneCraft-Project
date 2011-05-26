#ifndef BTCYLINDER_H
#define BTCYLINDER_H

#include "genelabcoreclasses.h"
#include "btshape.h"
#include "BulletCollision/CollisionShapes/btCylinderShape.h"
#include "LinearMath/btDefaultMotionState.h"

namespace GeneLabCore {

class btCylinder : public btShape
{
public:
    btCylinder(BulletEngine *btEngine, btScalar radius, btScalar height, const btTransform &transform);
    virtual void setup();

private:

    void init(btScalar radius, btScalar height, btScalar density, const btTransform &transform);

protected:

    btScalar radius;
    btScalar height;
    btCylinderShape* shape;
    btDefaultMotionState* motionState;
};

}

#endif // BTCYLINDER_H
