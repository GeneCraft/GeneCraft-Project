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
    btCylinder(BulletEngine *btEngine, btScalar radius, btScalar height, btVector3 position, btVector3 rotation = btVector3(0,0,0));
    virtual void setup();

private:

    void init(btScalar radius, btScalar height, btVector3 position, btScalar density, btVector3 EulerRotation);

protected:

    btScalar radius;
    btScalar height;
    btCylinderShape* shape;
    btDefaultMotionState* motionState;
};

}

#endif // BTCYLINDER_H
