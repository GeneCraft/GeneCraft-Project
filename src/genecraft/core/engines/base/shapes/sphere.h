#ifndef BTSPHERE_H
#define BTSPHERE_H

#include "genecraftcoreclasses.h"
#include "btshape.h"
#include "BulletCollision/CollisionShapes/btSphereShape.h"
#include "LinearMath/btDefaultMotionState.h"

namespace GeneCraftCore {

/**
 * @brief a basic physical sphere, mainly used at the primary fixation of an
 entity
 *
 */
class btSphere : public btShape
{
public:
/**
 * @brief construct a sphere in a given world
 *
 * @param btWorld the world where the sphere will be
 * @param radius the radius of the sphere
 * @param transform the initial transformation of the sphere
 * @param density the density of the sphere
 */
    btSphere(btWorld *btWorld, btScalar radius, const btTransform &transform, const btScalar density);
    /**
     * @brief destruct and remove the sphere from the world
     *
     */
    virtual ~btSphere();
    /**
     * @brief setup the sphere in the world
     *
     */
    virtual void setup();
    /**
     * @brief change the size of the sphere
     *
     * @param radius the new radius of the sphere
     */
    virtual void setRadius(btScalar radius);
    /**
     * @brief return the mass of the sphere
     *
     */
    btScalar getMass() const;

private:

    /**
     * @brief protected init function
     *
     * @param radius
     * @param density
     * @param transform
     */
    void init(btScalar radius, btScalar density, const btTransform &transform);
    /**
     * @brief compute the mass of the sphere
     *
     */
    btScalar computeMass() const;

protected:

    btSphereShape* shape; /**< physical spherical bullet shape */
    btDefaultMotionState* motionState; /**< motion state (bullet) */
    RigidBodyOrigin* origin; /**< the link between the object to the rigid body */
    btScalar density; /**< the density of the sphere */
};

}

#endif // BTSPHERE_H
