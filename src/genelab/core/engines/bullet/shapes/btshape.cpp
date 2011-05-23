#include "btshape.h"

btShape::btShape(QObject *parent) :
    QObject(parent), btEngine(NULL), rigidBody(NULL)//, collisionShape(NULL)
{
}
