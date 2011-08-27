#include "rigidbodyorigin.h"

namespace GeneCraftCore {

RigidBodyOrigin::RigidBodyOrigin(RigidBodyType typeOrigin, QObject * object)
{
    this->typeOrigin = typeOrigin;
    this->object = object;
}

}
