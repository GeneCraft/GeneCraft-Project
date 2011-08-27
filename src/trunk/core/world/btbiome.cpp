#include "btbiome.h"
#include "btworld.h"

namespace GeneCraftCore {
    btBiome::btBiome(btWorld* world, QVariant biomeData, QObject *parent) :
        QObject(parent)
    {
        world->setBiome(this);
        this->data = biomeData.toMap();
    }

    btBiome::~btBiome() {

    }

    void btBiome::setup() {
        btScalar gravity = data["gravity"].toFloat();
        world->setGravity(btVector3(0,-gravity,0));
    }

}
