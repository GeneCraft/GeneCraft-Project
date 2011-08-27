#ifndef BTOWORLD_H
#define BTOWORLD_H

#include "genecraftcoreclasses.h"
#include "btworld.h"

namespace GeneCraftCore {

class btoWorld : public btWorld
{
public:

    // To create a default world
    btoWorld(btoFactory* factory, btoShapesFactory* shapesFactory, QObject *parent = 0);

    // To create a world from serialization data
    btoWorld(btoFactory* factory, btoShapesFactory* shapesFactory, QVariant data, QObject *parent = 0);

    virtual void setup();

    BulletOgreEngine* getBulletOgreEngine() {
        return btoEngine;
    }

protected:
    BulletOgreEngine *btoEngine;

};

}

#endif // BTOWORLD_H
