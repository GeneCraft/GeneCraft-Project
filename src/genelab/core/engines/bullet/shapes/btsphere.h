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
    btSphere(btWorld *btWorld, btScalar radius, const btTransform &transform, const btScalar density);
    virtual ~btSphere();
    virtual void setup();
    virtual void setRadius(btScalar radius);
    btScalar getMass() const;

private:

    void init(btScalar radius, btScalar density, const btTransform &transform);
    btScalar computeMass() const;

protected:

    btSphereShape* shape;
    btDefaultMotionState* motionState;
    RigidBodyOrigin* origin;
    float density;
};

}

#endif // BTSPHERE_H
