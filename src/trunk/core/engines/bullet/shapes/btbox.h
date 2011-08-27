#ifndef BTBOX_H
#define BTBOX_H

#include "genecraftcoreclasses.h"
#include "btshape.h"
#include "BulletCollision/CollisionShapes/btBoxShape.h"
#include "LinearMath/btDefaultMotionState.h"

namespace GeneCraftCore {

class btBox : public btShape
{
public:
    btBox(btWorld *world, btVector3 size, const btTransform &transform, const btScalar density);
    ~btBox();
    virtual void setup();

private:

    void init(btVector3 size, const btTransform &transform, const btScalar density);

protected:

    btBoxShape* shape;
    btDefaultMotionState* motionState;
};

}

#endif // BTBOX_H
