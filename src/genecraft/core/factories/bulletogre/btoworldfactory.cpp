/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

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
