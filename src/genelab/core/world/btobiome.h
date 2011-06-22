#ifndef BTOBIOME_H
#define BTOBIOME_H

#include "genelabcoreclasses.h"
#include "btbiome.h"

namespace GeneLabCore {

class btoBiome : public btBiome
{
    Q_OBJECT
public:
    explicit btoBiome(MainFactory* factory, QVariant biomeData, QObject *parent = 0);

    virtual void setup();
signals:

public slots:

};

}

#endif // BTOBIOME_H
