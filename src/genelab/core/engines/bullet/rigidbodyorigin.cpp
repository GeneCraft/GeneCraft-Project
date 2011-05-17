#include "rigidbodyorigin.h"

namespace GeneLabCore {

RigidBodyOrigin::RigidBodyOrigin(RigidBodyOrigin::type typeOrigin, QObject * object)
{
    this->typeOrigin = typeOrigin;
    this->object = object;
}

}
