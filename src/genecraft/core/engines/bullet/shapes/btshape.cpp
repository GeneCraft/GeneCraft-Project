#include "btshape.h"

namespace GeneCraftCore {

btShape::btShape(btWorld* world) :
    world(world), rigidBody(NULL)//, collisionShape(NULL)
{
}

btShape::~btShape() {
}

}
