#ifndef RIGIDBODYORIGIN_H
#define RIGIDBODYORIGIN_H

#include <QObject>

namespace GeneLabCore {

class RigidBodyOrigin : public QObject
{

public:

    enum RigidBodyType
    {
        BONE = 0,
        FIXATION,
        BASIC_SHAPE,
        FOOD
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
