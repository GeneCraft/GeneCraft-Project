#ifndef BTOSCENE_H
#define BTOSCENE_H

#include "genelabcoreclasses.h"
#include "btscene.h"

#include "btofactory.h"

namespace GeneLabCore {

class btoScene : public btScene
{
public:
    explicit btoScene(btoWorld* world, QVariant sceneData, QObject *parent = 0);

    virtual void setup();
};

}

#endif // BTOSCENE_H
