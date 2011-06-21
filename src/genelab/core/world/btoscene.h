#ifndef BTOSCENE_H
#define BTOSCENE_H

#include "genelabcoreclasses.h"
#include "btscene.h"

namespace GeneLabCore {

class btoScene : public btScene
{
    Q_OBJECT
public:
    explicit btoScene(QObject *parent = 0);

signals:

public slots:

};

}

#endif // BTOSCENE_H
