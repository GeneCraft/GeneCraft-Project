#ifndef BTOWORLD_H
#define BTOWORLD_H

#include "genelabcoreclasses.h"
#include "btworld.h"

namespace GeneLabCore {

class btoWorld : public btWorld
{
    Q_OBJECT
public:
    explicit btoWorld(MainFactory* factory, QObject *parent = 0);

signals:

public slots:


protected:
    BulletOgreEngine *btoEngine;

};

}

#endif // BTOWORLD_H
