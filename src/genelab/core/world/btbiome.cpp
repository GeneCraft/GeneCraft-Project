#include "btbiome.h"
#include "btworld.h"

namespace GeneLabCore {
    btBiome::btBiome(btWorld* world, QVariant biomeData, QObject *parent) :
        QObject(parent)
    {
        world->setBiome(this);
        this->data = biomeData.toMap();
    }

    void btBiome::setup() {
        btScalar gravity = data["gravity"].toFloat();
        world->setGravity(btVector3(0,-gravity,0));
    }

}
