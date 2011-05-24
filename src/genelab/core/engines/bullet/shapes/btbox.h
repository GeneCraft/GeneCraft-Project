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
    btBox(BulletEngine *btEngine, btVector3 size, btVector3 position, btVector3 rotation = btVector3(0,0,0));
    virtual void setup();

private:

    void init(btVector3 size, btVector3 position, btScalar density, btVector3 EulerRotation);

protected:

    btBoxShape* shape;
    btDefaultMotionState* motionState;
};

}

#endif // BTBOX_H
