#ifndef BTSHAPE_H
#define BTSHAPE_H

#include <QObject>
#include "genecraftcoreclasses.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

namespace GeneCraftCore {

/**
 * @brief A basic physical shape an abstract class meant to be implemented in
 various shape type.
 *
 */
class btShape : public QObject
{
public:
    /**
     * @brief construct the shape in a given world
     *
     * @param world
     */
    explicit btShape(btWorld* world);
    /**
     * @brief destruct and remove the shape from the world
     *
     */
    ~btShape();
    /**
     * @brief return the bulletphysic rigid body relatif to the shape
     *
     * @return btRigidBody *
     */
    btRigidBody * getRigidBody() { return rigidBody; }

    /**
     * @brief select the shape
     *
     * @param bool
     */
    virtual void setSelected(bool){}

    /**
     * @brief setup the physical shape into the world
     *
     */
    virtual void setup(){}

protected:

    btWorld *world; /**< the world where the shape live */
    btRigidBody *rigidBody; /**< the rigidbody of the shape */

};

}

#endif // BTSHAPE_H
