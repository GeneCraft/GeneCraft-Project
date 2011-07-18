#include "btworldfactory.h"
#include "btshapesfactory.h"
#include "tools.h"

namespace GeneLabCore {

    QVariant btWorldFactory::createSimpleWorld() {

        // World from program (soon from file)
        QVariantMap worldData;
        worldData.insert("name", "Earth");

        // Biome
        QVariantMap biomeData;
        biomeData.insert("gravity", 9.81);
        biomeData.insert("sky", "Examples/CloudySky");

        // ------------
        // -- lights --
        // ------------
        QVariantList lights;

        // ambiant
        QVariantMap ambiantLightMap;
        ambiantLightMap.insert("type","ambient");
        ambiantLightMap.insert("r",(double)0.8);
        ambiantLightMap.insert("g",(double)0.8);
        ambiantLightMap.insert("b",(double)0.8);
        lights.append(ambiantLightMap);

        // point
        QVariantMap pointLightMap;
        pointLightMap.insert("type","point");
        pointLightMap.insert("r",(double)0.9);
        pointLightMap.insert("g",(double)0.1);
        pointLightMap.insert("b",(double)0.1);
        pointLightMap.insert("posX",(double)0);
        pointLightMap.insert("posY",(double)1);
        pointLightMap.insert("posZ",(double)0);
        lights.append(pointLightMap);
        biomeData.insert("lights",lights);


        // -----------
        // -- Scene --
        // -----------
        QVariantMap sceneData;

        // ------------
        // -- Camera --
        // ------------
        QVariantMap camData;
        camData.insert("posX",  -20);
        camData.insert("posY",  10);
        camData.insert("posZ",  -20);
        camData.insert("targetX",  15);
        camData.insert("targetY",  -5);
        camData.insert("targetZ",  15);
        sceneData.insert("camera", camData);

        // -----------------
        // -- Spawn areas --
        // -----------------
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
        sceneData.insert("spawns", spawns);

        // ------------------
        // -- Static boxes --
        // ------------------

        QVariantList shapes;

        // MineCraft Floor
        int sizeX = 10;
        int sizeZ = 10;
        for(int i=-10;i<10;++i){
            for(int j=-10;j<10;++j){

                double sizeY = Tools::random(0.1, 3.0);

                QVariantMap staticBox;
                staticBox.insert("type","box");
                staticBox.insert("density",0);
                staticBox.insert("posX",i*10);
                staticBox.insert("posY",sizeY/2.0);
                staticBox.insert("posZ",j*10);
                staticBox.insert("eulerX",0);
                staticBox.insert("eulerY",0);
                staticBox.insert("eulerZ",0);
                staticBox.insert("sizeX",sizeX);
                staticBox.insert("sizeY",sizeY);
                staticBox.insert("sizeZ",sizeZ);
                shapes.append(staticBox);
            }
        }

        // Spheres
        for(int i=0;i<10;++i){
            QVariantMap sphereMap;
            sphereMap.insert("type","sphere");
            sphereMap.insert("density",5);
            sphereMap.insert("posX",0);
            sphereMap.insert("posY",i*1+2);
            sphereMap.insert("posZ",0);
            sphereMap.insert("eulerX",0);
            sphereMap.insert("eulerY",0);
            sphereMap.insert("eulerZ",0);
            sphereMap.insert("radius",(double)1.0);
            shapes.append(sphereMap);
        }

        // Cylinders
        for(int i=0;i<10;++i){
            QVariantMap cylinderMap;
            cylinderMap.insert("type","cylinder");
            cylinderMap.insert("density",5);
            cylinderMap.insert("posX",5);
            cylinderMap.insert("posY",i*6+2);
            cylinderMap.insert("posZ",0);
            cylinderMap.insert("eulerX",0);
            cylinderMap.insert("eulerY",0);
            cylinderMap.insert("eulerZ",0);
            cylinderMap.insert("radius",(double)1.0);
            cylinderMap.insert("height",(double)5.0);
            shapes.append(cylinderMap);
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
        sceneData.insert("shapes", shapes);

        // Scene
        sceneData.insert("type", "flatland");
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
