#ifndef BTOWORLD_H
#define BTOWORLD_H

#include "genelabcoreclasses.h"
#include "btworld.h"

namespace GeneLabCore {

class btoWorld : public btWorld
{
public:
    explicit btoWorld(btoFactory* factory, btoShapesFactory* shapesFactory, QVariant data, QObject *parent = 0);

    virtual void setup();

    BulletOgreEngine* getBulletOgreEngine() {
        return btoEngine;
    }

protected:
    BulletOgreEngine *btoEngine;

};

}

#endif // BTOWORLD_H
