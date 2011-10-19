#ifndef BTCYLINDER_H
#define BTCYLINDER_H

#include "genecraftcoreclasses.h"
#include "btshape.h"
#include "BulletCollision/CollisionShapes/btCylinderShape.h"
#include "LinearMath/btDefaultMotionState.h"

namespace GeneCraftCore {

/**
 * @brief A basic physical cylinder
 *
 */
class btCylinder : public btShape
{
public:
/**
 * @brief Construct a cylinder in a given world
 *
 * @param world the world where the cylinder will be
 * @param radius the radius of the cylinder
 * @param height the height of the cylinder
 * @param transform the initial position of the cylinder (bullet physics)
 * @param density the density of the cylinder
 */
    btCylinder(btWorld *world, btScalar radius, btScalar height, const btTransform &transform, const btScalar density);
    /**
     * @brief destruct and remove the cylinder from the world
     *
     */
    virtual ~btCylinder();
    /**
     * @brief setup the cylinder in the world
     *
     */
    virtual void setup();
    /**
     * @brief change the size (both radius and height) of the cylinder
     *
     * @param radius the new radius of the cylinder
     * @param height the new height of the cylinder
     */
    virtual void setSize(btScalar radius, btScalar height);

private:

    /**
     * @brief
     *
     * @param radius
     * @param height
     * @param density
     * @param transform
     */
    void init(btScalar radius, btScalar height, btScalar density, const btTransform &transform);

protected:

    btScalar radius; /**< TODO */
    btScalar height; /**< TODO */
    btCylinderShape* shape; /**< TODO */
    btDefaultMotionState* motionState; /**< TODO */
};

}

#endif // BTCYLINDER_H
