#include "btbiome.h"

namespace GeneLabCore {
    btBiome::btBiome(btFactory* factory, QVariant biomeData, QObject *parent) :
        QObject(parent)
    {
        this->factory = factory;
        this->data = biomeData.toMap();
    }


    void btBiome::setup() {
        float gravity = data["gravity"].toFloat();
        world->setGravity(btVector3(0,-gravity,0));
    }

}
