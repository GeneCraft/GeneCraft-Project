#ifndef RIGIDBODYORIGIN_H
#define RIGIDBODYORIGIN_H

#include <QObject>

namespace GeneCraftCore {

/**
 * @brief Create a link between a rigidbody and a QObject*
 is used to get the qt object back from a collision callback for example
 *
 */
class RigidBodyOrigin : public QObject
{

public:

    /**
     * @brief the type of the shape, to be able to cast the QObject to a more
     usefull type, new kind of shape should be added here accordingly
     *
     */
    enum RigidBodyType
    {
        BONE = 0, // A physical bone
        FIXATION, // A physical fixation (sphere)
        BASIC_SHAPE // Another type of shape
    };

/**
 * @brief create an information about the rigidbodyorigin
 *
 * @param typeOrigin the initial type
 * @param object the pointer to the linked object
 */
    RigidBodyOrigin(RigidBodyType typeOrigin, QObject * object);


    /**
     * @brief return to object type
     *
     * @return RigidBodyType
     */
    inline RigidBodyType getType()
    {
        return typeOrigin;
    }

    /**
     * @brief return the object pointer
     *
     * @return QObject *
     */
    QObject * getObject()
    {
        return object;
    }

protected:

    RigidBodyType typeOrigin; /**< the type of the object */
    QObject *object; /**< the pointer to the object */

};

}

#endif // RIGIDBODYORIGIN_H
