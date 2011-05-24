#include "btshape.h"

namespace GeneLabCore {

btShape::btShape(QObject *parent) :
    QObject(parent), btEngine(NULL), rigidBody(NULL)//, collisionShape(NULL)
{
}

}
