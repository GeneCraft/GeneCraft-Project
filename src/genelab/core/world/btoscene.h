#ifndef BTOSCENE_H
#define BTOSCENE_H

#include "genelabcoreclasses.h"
#include "btscene.h"

#include "btofactory.h"

namespace GeneLabCore {

class btoScene : public btScene
{
    Q_OBJECT
public:
    explicit btoScene(btoWorld* world, QVariant sceneData, QObject *parent = 0);

    virtual void setup();
signals:

public slots:

};

}

#endif // BTOSCENE_H
