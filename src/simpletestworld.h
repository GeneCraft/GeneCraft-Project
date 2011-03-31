#ifndef SIMPLETESTWORLD_H
#define SIMPLETESTWORLD_H

#include "classes.h"
#include "world/world.h"

class SimpleTestWorld : public GeneLabCore::World
{
    Q_OBJECT
public:
    explicit SimpleTestWorld(QObject *parent = 0);

signals:

public slots:

};

#endif // SIMPLETESTWORLD_H
