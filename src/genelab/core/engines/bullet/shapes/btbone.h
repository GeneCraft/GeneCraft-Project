#ifndef BTBONE_H
#define BTBONE_H

#include "genelabcoreclasses.h"
#include "btshape.h"
#include "BulletCollision/CollisionShapes/btSphereShape.h"
#include "BulletCollision/CollisionShapes/btCylinderShape.h"
#include "BulletCollision/CollisionShapes/btCompoundShape.h"
#include "LinearMath/btDefaultMotionState.h"

namespace GeneLabCore {
class btBone : public btShape
{
    Q_OBJECT
public:
    explicit btBone(BulletEngine *btEngine, btScalar length, btScalar radius, btScalar radiusArticulation, const btTransform &transform);
    virtual void setup();

private:

    void init(btScalar length, btScalar radius, btScalar radiusArticulation, btScalar density, const btTransform &transform);

protected:

    BulletEngine* btEngine;
    btCompoundShape* shape;
    btDefaultMotionState* motionState;

};
}

#endif // BTBONE_H
