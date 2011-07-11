#ifndef RIGIDBODYORIGIN_H
#define RIGIDBODYORIGIN_H

#include <QObject>

namespace GeneLabCore {

class RigidBodyOrigin : public QObject
{

public:

    enum type
    {
        BONE = 0,
        FIXATION,
        DESTROYABLE_BLOCK,
        PLAYER_CHARACTER,
        BASIC_SHAPE
    };

    RigidBodyOrigin(RigidBodyOrigin::type typeOrigin, QObject * object);


    inline RigidBodyOrigin::type getType()
    {
        return typeOrigin;
    }

    QObject * getObject()
    {
        return object;
    }

protected:

    RigidBodyOrigin::type typeOrigin;
    QObject *object;

};

}

#endif // RIGIDBODYORIGIN_H
