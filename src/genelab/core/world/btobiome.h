#ifndef BTOBIOME_H
#define BTOBIOME_H

#include "genecraftcoreclasses.h"
#include "btbiome.h"

namespace GeneCraftCore {

class btoBiome : public btBiome
{
public:
    explicit btoBiome(btoWorld* world, QVariant biomeData, QObject *parent = 0);

    virtual void setup();

    QVariantList getLightsData() { return lightsData; }
    void setLightsData(QVariantList lightsData) { this->lightsData = lightsData; }

private:
    btoWorld* world;

    QVariantList lightsData;
};

}

#endif // BTOBIOME_H
