#ifndef BTBONE_H
#define BTBONE_H

#include "genecraftcoreclasses.h"
#include "btshape.h"
#include "BulletCollision/CollisionShapes/btSphereShape.h"
#include "BulletCollision/CollisionShapes/btCylinderShape.h"
#include "BulletCollision/CollisionShapes/btCompoundShape.h"
#include "LinearMath/btDefaultMotionState.h"

namespace GeneCraftCore {
class btBone : public btShape
{
public:
    explicit btBone(btWorld *world, btScalar length, btScalar radius, btScalar radiusArticulation, const btTransform &transform);
    ~btBone();
    virtual void setup();

    btScalar getLength() { return cylinderShape->getHalfExtentsWithMargin().y()*btScalar(2.0); }
    btScalar getRadius() { return cylinderShape->getRadius(); }
    btScalar getArticulationRadius() { return sphereShape->getRadius(); }

    virtual void setSize(btScalar radius, btScalar length);
    virtual void setEndFixationRadius(btScalar radius);

    static const btScalar DENSITY;

private:

    void init(btScalar length, btScalar radius, btScalar radiusArticulation, btScalar density, const btTransform &transform);

protected:

    BulletEngine* btEngine;
    btCompoundShape* shape;
    btDefaultMotionState* motionState;
    btCylinderShape* cylinderShape;
    btSphereShape* sphereShape;
};
}



#endif // BTBONE_H
