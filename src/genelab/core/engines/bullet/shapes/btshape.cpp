#include "btshape.h"

namespace GeneLabCore {

btShape::btShape(btWorld* world) :
    world(world), rigidBody(NULL)//, collisionShape(NULL)
{
}

btShape::~btShape() {
}

}
