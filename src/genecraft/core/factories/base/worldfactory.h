#ifndef WORLDFACTORY_H
#define WORLDFACTORY_H

#include "world/btworld.h"

namespace GeneCraftCore {

    class btWorldFactory
    {

    public:

        static QVariant createSimpleWorld();
        static btWorld* createWorld( btFactory* factory,
                                     btShapesFactory* shapesFactory,
                                     QVariant worldData);

        // spawns
        static void createPositionSpawn(QVariantList &spawns,btVector3 pos);
        static void createBoxAreaSpawn(QVariantList &spawnsList, btVector3 size, btVector3 pos);

        // shapes
        static void createBox(QVariantList &shapesList, btVector3 size, btVector3 pos, btVector3 euler, double density);
        static void createSphere(QVariantList &shapesList, btScalar radius, btVector3 pos, btVector3 euler, double density);
        static void createCylinder(QVariantList &shapesList, btScalar radius, btScalar height, btVector3 pos, btVector3 euler, double density);

        // floors
        static void createRuins(QVariantList &shapesList, double areaX, double areaZ, btVector3 pos, btVector3 boxMin, btVector3 boxMax, int nbBoxes, double density = 0);
        static void createBoxesFloor(QVariantList &shapesList, double areaX, double areaZ, btVector3 pos, btVector3 boxMin, btVector3 boxMax);
        static void createBoxesStairs(QVariantList &shapesList, double areaX, double areaZ, btVector3 pos, double stepWidth, double yMinStep, double yMaxStep);
        static void createSlope(QVariantList &shapesList, double areaX, double areaZ, btVector3 pos, btVector3 axis, double minAngle, double maxAngle);
        // sphere pool
        static void createPoolOfBalls(QVariantList &shapesList, double areaX, double areaZ, btVector3 pos, int nbBalls);
    };

}

#endif // WORLDFACTORY_H
