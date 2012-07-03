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

#include "btworldfactory.h"
#include "btshapesfactory.h"
#include "tools.h"

#include <QDebug>

namespace GeneCraftCore {

    QVariant btWorldFactory::createSimpleWorld() {

        // World from program (soon from file)
        QVariantMap worldData;
        worldData.insert("name", "Somewhere on Earth");

        // ------------
        // -- Biome --
        // ------------
        QVariantMap biomeData;
        biomeData.insert("gravity", 9.81);
        biomeData.insert("skyMaterial", "Examples/CloudySky");

        QVariantMap gravityData;
        gravityData.insert("axeX", 0.0);
        gravityData.insert("axeY", -1.0);
        gravityData.insert("axeZ", 0.0);

        biomeData.insert("gravities", gravityData);

        // -- lights --
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
        pointLightMap.insert("r",(double)1.);
        pointLightMap.insert("g",(double)1.);
        pointLightMap.insert("b",(double)1.);
        pointLightMap.insert("posX",(double)2000);
        pointLightMap.insert("posY",(double)2000);
        pointLightMap.insert("posZ",(double)1);
        lights.append(pointLightMap);

        // directional
//        QVariantMap directionalLightMap;
//        directionalLightMap.insert("type","directional");
//        directionalLightMap.insert("r",(double)1.0);
//        directionalLightMap.insert("g",(double)1.0);
//        directionalLightMap.insert("b",(double)1.0);
//        directionalLightMap.insert("dirX",(double)-1);
//        directionalLightMap.insert("dirY",(double)-1);
//        directionalLightMap.insert("dirZ",(double)0);
//        directionalLightMap.insert("innerAngle", (double)-M_PI);
//        directionalLightMap.insert("outerAngle", (double)M_PI);
//        lights.append(directionalLightMap);

        biomeData.insert("lights",lights);
        worldData.insert("biome", biomeData);


        // -----------
        // -- Scene --
        // -----------
        QVariantMap sceneData;

        // -- Camera --
        QVariantMap camData;
        camData.insert("posX",  -20);
        camData.insert("posY",  10);
        camData.insert("posZ",  -20);
        camData.insert("targetX",  15);
        camData.insert("targetY",  -5);
        camData.insert("targetZ",  15);
        sceneData.insert("camera", camData);

        // -- Spawn areas --
        QVariantList spawns;

        //createBoxAreaSpawn(spawns,btVector3(100,1,100),btVector3(0,20,0));
        createPositionSpawn(spawns,btVector3(0,10,0));

//        QVariantMap zoneSpawn;
//        zoneSpawn.insert("type", (int)Spawn::Zone);
//        zoneSpawn.insert("minX", -60);
//        zoneSpawn.insert("minY", 10);
//        zoneSpawn.insert("minZ", -60);
//        zoneSpawn.insert("maxX", 60);
//        zoneSpawn.insert("maxY", 10);
//        zoneSpawn.insert("maxZ", 60);
//        spawns.append(zoneSpawn);

        sceneData.insert("spawns", spawns);

        // -- Static boxes --
        QVariantList shapes;

//        createRuins(shapes, 100.0, 100.0, btVector3(0,0,0), btVector3(1.0,1.0,1.0), btVector3(10.0,10.0,10.0), 100, 0);
//        createBoxesFloor(shapes, 100.0, 100.0, btVector3(0,0,0), btVector3(2.0,1.0,2.0), btVector3(15.0,2.0,15.0));
//        createBoxesFloor(shapes, 100.0, 100.0, btVector3(0,0,0), btVector3(2.0,0.5,2.0), btVector3(15.0,1.0,15.0));

//        createPoolOfBalls(shapes, 50.0, 50.0,btVector3(0,0,0), 100);

//        // Spheres sample
//        for(int i=0;i<100;++i)
//            createSphere(shapes,1,
//                         btVector3(Tools::random(-100.0, 100.0),10,Tools::random(-100.0, 100.0)),
//                         btVector3(Tools::random(-SIMD_PI, SIMD_PI),Tools::random(-SIMD_PI, SIMD_PI),Tools::random(-SIMD_PI, SIMD_PI)),
//                         5.0);

//        // Cylinders sample
//        for(int i=0;i<100;++i)
//            createCylinder(shapes,1,5,
//                         btVector3(Tools::random(-100.0, 100.0),10,Tools::random(-100.0, 100.0)),
//                         btVector3(Tools::random(-SIMD_PI, SIMD_PI),Tools::random(-SIMD_PI, SIMD_PI),Tools::random(-SIMD_PI, SIMD_PI)),
//                         5.0);

        sceneData.insert("shapes", shapes);

        // Floor
        QVariantMap floor;
        floor.insert("type", "flatland");
        floor.insert("material", "GeneCraft/GrassFloor");
        sceneData.insert("floor",floor);

        worldData.insert("scene", sceneData);

        return worldData;
    }

    void btWorldFactory::createPositionSpawn(QVariantList &spawnsList,btVector3 pos) {

        QVariantMap positionSpawn;
        positionSpawn.insert("type", "position");
        positionSpawn.insert("posX", (double)pos.x());
        positionSpawn.insert("posY", (double)pos.y());
        positionSpawn.insert("posZ", (double)pos.z());
        spawnsList.append(positionSpawn);
    }

    void btWorldFactory::createBoxAreaSpawn(QVariantList &spawnsList, btVector3 size, btVector3 pos)
    {
        QVariantMap spawnMap;
        spawnMap.insert("type", "boxArea");
        spawnMap.insert("sizeX", (double)size.x());
        spawnMap.insert("sizeY", (double)size.y());
        spawnMap.insert("sizeZ", (double)size.z());
        spawnMap.insert("posX", (double)pos.x());
        spawnMap.insert("posY", (double)pos.y());
        spawnMap.insert("posZ", (double)pos.z());
        spawnsList.append(spawnMap);
    }

    void btWorldFactory::createBox(QVariantList &shapesList, btVector3 size, btVector3 pos, btVector3 euler, double density)
    {
        QVariantMap boxMap;
        boxMap.insert("type","box");
        boxMap.insert("density",(double)density);
        boxMap.insert("posX",(double)pos.x());
        boxMap.insert("posY",(double)pos.y());
        boxMap.insert("posZ",(double)pos.z());
        boxMap.insert("eulerX",(double)euler.x());
        boxMap.insert("eulerY",(double)euler.y());
        boxMap.insert("eulerZ",(double)euler.z());
        boxMap.insert("sizeX",(double)size.x());
        boxMap.insert("sizeY",(double)size.y());
        boxMap.insert("sizeZ",(double)size.z());
        shapesList.append(boxMap);
    }

    void btWorldFactory::createSphere(QVariantList &shapesList, btScalar radius, btVector3 pos, btVector3 euler, double density) {

        QVariantMap sphereMap;
        sphereMap.insert("type","sphere");
        sphereMap.insert("radius",(double)radius);
        sphereMap.insert("posX",(double)pos.x());
        sphereMap.insert("posY",(double)pos.y());
        sphereMap.insert("posZ",(double)pos.z());
        sphereMap.insert("eulerX",(double)euler.x());
        sphereMap.insert("eulerY",(double)euler.y());
        sphereMap.insert("eulerZ",(double)euler.z());
        sphereMap.insert("density",(double)density);
        shapesList.append(sphereMap);
    }

    void btWorldFactory::createCylinder(QVariantList &shapesList, btScalar radius, btScalar height, btVector3 pos, btVector3 euler, double density) {

        QVariantMap cylinderMap;
        cylinderMap.insert("type","cylinder");
        cylinderMap.insert("radius",(double)radius);
        cylinderMap.insert("height",(double)height);
        cylinderMap.insert("posX",(double)pos.x());
        cylinderMap.insert("posY",(double)pos.y());
        cylinderMap.insert("posZ",(double)pos.z());
        cylinderMap.insert("eulerX",(double)euler.x());
        cylinderMap.insert("eulerY",(double)euler.y());
        cylinderMap.insert("eulerZ",(double)euler.z());
        cylinderMap.insert("density",(double)density);
        shapesList.append(cylinderMap);
    }

    void btWorldFactory::createBoxesStairs(QVariantList &shapesList, double areaX, double areaZ, btVector3 pos, double stepWidth, double yMinStep, double yMaxStep) {

        // Boxes Floor
        double sizeX = stepWidth;
        double sizeZ = stepWidth;

        int nbBoxesX = areaX / sizeX;
        int nbBoxesZ = areaZ / sizeZ;

        double maxY = (nbBoxesX+nbBoxesZ)*Tools::random(yMinStep, yMaxStep);


        for(int i=0;i<nbBoxesX;++i){
            for(int j=0;j<nbBoxesZ;++j){

                //double sizeY = 2*maxY - sin((double)i/nbBoxesX*M_PI)*maxY - sin((double)j/nbBoxesX*M_PI)*maxY;
                double sizeY = qAbs(nbBoxesX/2. - i)/nbBoxesX*maxY + qAbs(nbBoxesZ/2. - j)/nbBoxesZ*maxY;

                createBox(shapesList,
                          btVector3(sizeX,sizeY,sizeZ),
                          btVector3(i*sizeX - areaX*0.5 + pos.x(),sizeY/2.0 + pos.y(),j*sizeZ - areaZ*0.5 +  pos.z()),
                          btVector3(0,0,0),0);
            }
        }
    }

    void btWorldFactory::createSlope(QVariantList &shapesList, double areaX, double areaZ, btVector3 pos, btVector3 axis, double minAngle, double maxAngle) {



        createBox(shapesList,
                  btVector3(areaX,1.0,areaZ),
                  pos,
                  axis*Tools::random(minAngle, maxAngle),0);

    }

    void btWorldFactory::createBoxesFloor(QVariantList &shapesList, double areaX, double areaZ, btVector3 pos, btVector3 boxMin, btVector3 boxMax) {

        // Boxes Floor
        double sizeX = Tools::random((double)boxMin.x(), (double)boxMax.x());
        double sizeZ = Tools::random((double)boxMin.z(), (double)boxMax.z());

        btVector3 recal(sizeX,0,sizeZ);
        pos = pos + recal;

        int nbBoxesX = areaX / sizeX;
        int nbBoxesZ = areaZ / sizeZ;

        for(int i=0;i<nbBoxesX;++i){
            for(int j=0;j<nbBoxesZ;++j){

                double sizeY = Tools::random((double)boxMin.y(), (double)boxMax.y());

                createBox(shapesList,
                          btVector3(sizeX,sizeY,sizeZ),
                          btVector3(i*sizeX - areaX*0.5 + pos.x(),sizeY/2.0 + pos.y(),j*sizeZ - areaZ*0.5 +  pos.z()),
                          btVector3(0,0,0),0);
            }
        }
    }

    void btWorldFactory::createRuins(QVariantList &shapesList, double areaX, double areaZ, btVector3 pos, btVector3 boxMin, btVector3 boxMax, int nbBoxes, double density) {

        // Ruin Floor
        for(int i=0;i<nbBoxes;++i){

            btVector3 size(Tools::random((double)boxMin.x(), (double)boxMax.x()),
                           Tools::random((double)boxMin.y(), (double)boxMax.y()),
                           Tools::random((double)boxMin.z(), (double)boxMax.z()));

            btVector3 localPos(Tools::random((double)-areaX/2.0, (double)areaX/2.0),
                           size.y()/2.0,
                           Tools::random(-areaZ/2.0, areaZ/2.0));

            btVector3 euler(Tools::random(-SIMD_PI, SIMD_PI),
                            Tools::random(-SIMD_PI, SIMD_PI),
                            Tools::random(-SIMD_PI, SIMD_PI));

            createBox(shapesList,size,pos + localPos, euler, density);
        }
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

    void btWorldFactory::createPoolOfBalls(QVariantList &shapesList, double areaX, double areaZ, btVector3 pos, int nbBalls) {

        // walls
        btScalar wallsHeight = 10.0;
        btScalar wallsWidth = 4.0;
        createBox(shapesList, btVector3(areaX,wallsHeight,wallsWidth), pos + btVector3(0,wallsHeight*.5,areaZ*0.5-wallsWidth*0.5), btVector3(0,0,0), 0);
        createBox(shapesList, btVector3(areaX,wallsHeight,wallsWidth), pos + btVector3(0,wallsHeight*.5,-(areaZ*0.5-wallsWidth*0.5)), btVector3(0,0,0), 0);


        btScalar cubeSize = 20;
        btScalar cubeZRot = M_PI * 0.08 ;

        createBox(shapesList, btVector3(cubeSize,cubeSize,areaZ), pos + btVector3(areaX*0.5,-7,0), btVector3(0,0,cubeZRot), 0);
        createBox(shapesList, btVector3(cubeSize,cubeSize,areaZ), pos + btVector3(-areaX*0.5,-7,0), btVector3(0,0,-cubeZRot), 0);


        // balls
//        btScalar ballRadius = 1.0;

//        int nbx = 8;
//        int nby = 4;
//        int nbz = 14;

//        for(int x=0;x<nbx;x++) {
//            for(int y=0;y<nby;y++) {
//                for(int z=0;z<nbz;z++) {
//                    createSphere(shapesList,
//                                 ballRadius,pos - btVector3(nbx*ballRadius,0,nbz*ballRadius) + btVector3(x* ballRadius*2,y* ballRadius*2+ ballRadius,z* ballRadius*2),
//                                 btVector3(0,0,0),20.0);
//                }
//            }
//        }
    }
}
