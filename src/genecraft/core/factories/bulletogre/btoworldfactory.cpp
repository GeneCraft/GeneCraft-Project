#include "btoworldfactory.h"

#include "btofactory.h"
#include "btoshapesfactory.h"
#include "bulletogre/btoworld.h"
#include "bulletogre/btoscene.h"
#include "bulletogre/btobiome.h"

namespace GeneCraftCore {

    btoWorld* btoWorldFactory::createWorld(btoFactory *factory,
                                 btoShapesFactory *shapesFactory,
                                 QVariant map) {
        QVariantMap worldMap = map.toMap();

        // Create the world
        btoWorld* world = new btoWorld(factory, shapesFactory, worldMap["world"]);
        shapesFactory->setWorld(world);

        btBiome* biome = new btoBiome(world, worldMap["biome"]);
        world->setBiome(biome);

        btScene* scene = new btoScene(world, worldMap["scene"]);
        world->setScene(scene);

        world->setup();

        return world;
    }
}
