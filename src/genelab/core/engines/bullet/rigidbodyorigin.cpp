#include "rigidbodyorigin.h"

namespace GeneLabCore {

RigidBodyOrigin::RigidBodyOrigin(RigidBodyType typeOrigin, QObject * object)
{
    this->typeOrigin = typeOrigin;
    this->object = object;
}

}
