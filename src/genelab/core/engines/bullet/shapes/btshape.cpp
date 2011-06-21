#include "btshape.h"

namespace GeneLabCore {

btShape::btShape(btWorld* world, QObject *parent) :
    QObject(parent), world(world), rigidBody(NULL)//, collisionShape(NULL)
{
}

}
