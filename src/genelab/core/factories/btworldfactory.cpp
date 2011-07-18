#include "btworldfactory.h"
#include "btshapesfactory.h"
#include "tools.h"

namespace GeneLabCore {

    btWorldFactory::btWorldFactory(QObject *parent) :
        QObject(parent)
    {
    }


    QVariant btWorldFactory::createSimpleWorld() {
        // World from program (soon from file)
        QVariantMap worldData;
        worldData.insert("name", "Earth");

        // Biome
        QVariantMap biomeData;
        biomeData.insert("gravity", 9.81);
        biomeData.insert("sky", "Examples/CloudySky");
        biomeData.insert("aR", 0.8);
        biomeData.insert("aG", 0.8);
        biomeData.insert("aB", 0.8);
        biomeData.insert("lR", 0.6);
        biomeData.insert("lG", 0.6);
        biomeData.insert("lB", 0.6);

        // Camera
        QVariantMap camData;
        camData.insert("cX",  -20);
        camData.insert("cY",  10);
        camData.insert("cZ",  -20);
        camData.insert("lX",  15);
        camData.insert("lY",  -5);
        camData.insert("lZ",  15);

        // Spawn areas
        QVariantList spawns;
        QVariantMap zoneSpawn;
        QVariantMap positionSpawn;

        zoneSpawn.insert("type", (int)Spawn::Zone);
        zoneSpawn.insert("minX", -60);
        zoneSpawn.insert("minY", 10);
        zoneSpawn.insert("minZ", -60);
        zoneSpawn.insert("maxX", 60);
        zoneSpawn.insert("maxY", 10);
        zoneSpawn.insert("maxZ", 60);
        //spawns.append(zoneSpawn);

        positionSpawn.insert("type", (int)Spawn::Position);
        positionSpawn.insert("x", -10);
        positionSpawn.insert("y", 15);
        positionSpawn.insert("z", -10);
        spawns.append(positionSpawn);

        // Static boxes
        QVariantList staticBoxes;

        // MineCraft Floor
        int sizeX = 10;
        int sizeZ = 10;
        for(int i=-10;i<10;++i){
            for(int j=-10;j<10;++j){

                double sizeY = Tools::random(0.1, 3.0);

                QVariantMap staticBox;
                staticBox.insert("posX",i*10);
                staticBox.insert("posY",sizeY/2.0);
                staticBox.insert("posZ",j*10);
                staticBox.insert("eulerX",0);
                staticBox.insert("eulerY",0);
                staticBox.insert("eulerZ",0);
                staticBox.insert("sizeX",sizeX);
                staticBox.insert("sizeY",sizeY);
                staticBox.insert("sizeZ",sizeZ);
                staticBoxes.append(staticBox);
            }
        }

    //    // Ruin Floor
    //    for(int i=0;i<100;++i){

    //        double sizeX = Tools::random(1.0, 10.0);
    //        double sizeY = Tools::random(1.0, 10.0);
    //        double sizeZ = Tools::random(1.0, 10.0);

    //        double posX = Tools::random(-100, 100);
    //        double posZ = Tools::random(-100, 100);

    //        QVariantMap staticBox;
    //        staticBox.insert("posX",posX);
    //        staticBox.insert("posY",sizeY/2.0);
    //        staticBox.insert("posZ",posZ);
    //        staticBox.insert("eulerX",0);
    //        staticBox.insert("eulerY",0);
    //        staticBox.insert("eulerZ",0);
    //        staticBox.insert("sizeX",sizeX);
    //        staticBox.insert("sizeY",sizeY);
    //        staticBox.insert("sizeZ",sizeZ);
    //        staticBoxes.append(staticBox);
    //    }


        // Scene
        QVariantMap sceneData;
        sceneData.insert("type", "flatland");
        sceneData.insert("cam", camData);
        sceneData.insert("spawns", spawns);
        //sceneData.insert("staticBoxes", staticBoxes);
        sceneData.insert("floor", "Examples/GrassFloor");

        QVariantMap map;
        map.insert("world", worldData);
        map.insert("scene", sceneData);
        map.insert("biome", biomeData);

        return map;
    }

    btWorld* btWorldFactory::createWorld(btFactory* factory,
                                       btShapesFactory* shapesFactory,
                                       QVariant map) {
        QVariantMap worldMap = map.toMap();

        // Create the world
        btWorld* world = new btWorld(factory, shapesFactory, worldMap["world"]);
        shapesFactory->setWorld(world);

        btBiome* biome = new btBiome(world, worldMap["biome"]);
        world->setBiome(biome);

        btScene* scene = new btScene(world, worldMap["scene"]);
        world->setScene(scene);

        world->setup();

        return world;
    }
}
