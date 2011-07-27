#include "btoworldfactory.h"

#include "factories/btofactory.h"
#include "factories/btoshapesfactory.h"
#include "world/btoworld.h"
#include "world/btoscene.h"
#include "world/btobiome.h"

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
