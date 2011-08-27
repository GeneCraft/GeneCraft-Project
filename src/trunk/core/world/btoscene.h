#ifndef BTOSCENE_H
#define BTOSCENE_H

#include "genecraftcoreclasses.h"
#include "btscene.h"

#include "btofactory.h"

namespace GeneCraftCore {

class btoScene : public btScene
{
public:
    explicit btoScene(btoWorld* world, QVariant sceneData, QObject *parent = 0);

    virtual void setup();
};

}

#endif // BTOSCENE_H
