#ifndef RIGIDBODYORIGIN_H
#define RIGIDBODYORIGIN_H

#include <QObject>

namespace GeneCraftCore {

class RigidBodyOrigin : public QObject
{

public:

    enum RigidBodyType
    {
        BONE = 0,
        FIXATION,
        BASIC_SHAPE
    };

    RigidBodyOrigin(RigidBodyType typeOrigin, QObject * object);


    inline RigidBodyType getType()
    {
        return typeOrigin;
    }

    QObject * getObject()
    {
        return object;
    }

protected:

    RigidBodyType typeOrigin;
    QObject *object;

};

}

#endif // RIGIDBODYORIGIN_H