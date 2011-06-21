#ifndef BTBOX_H
#define BTBOX_H

#include "genelabcoreclasses.h"
#include "btshape.h"
#include "BulletCollision/CollisionShapes/btBoxShape.h"
#include "LinearMath/btDefaultMotionState.h"

namespace GeneLabCore {

class btBox : public btShape
{
public:
    btBox(btWorld *world, btVector3 size, const btTransform &transform);
    virtual void setup();

private:

    void init(btVector3 size, btScalar density, const btTransform &transform);

protected:

    btBoxShape* shape;
    btDefaultMotionState* motionState;
};

}

#endif // BTBOX_H
