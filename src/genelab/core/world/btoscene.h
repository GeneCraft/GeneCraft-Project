#ifndef BTOSCENE_H
#define BTOSCENE_H

#include "genelabcoreclasses.h"
#include "btscene.h"

#include "mainfactory.h"

namespace GeneLabCore {

class btoScene : public btScene
{
    Q_OBJECT
public:
    explicit btoScene(MainFactory* factory, QVariant sceneData, QObject *parent = 0);

    virtual void setup();
signals:

public slots:

};

}

#endif // BTOSCENE_H
