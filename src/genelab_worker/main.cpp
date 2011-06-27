#include <QtCore/QCoreApplication>

#include "btfactory.h"

#include "engine.h"

#include "world/btworld.h"
#include "world/btscene.h"
#include "world/btbiome.h"

#include "families/spider/spider.h"
#include "entity.h"
#include "entities/entitiesengine.h"

#include "btshapesfactory.h"

#include <QMap>
#include <QVariant>
#include <QVariantMap>
#include <QDebug>

using namespace GeneLabCore;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    btFactory* factory = new btFactory();

    QMap<QString, Engine*> engines = factory->getEngines();
    EntitiesEngine* ee = (EntitiesEngine*)engines.find("Entities").value();

    // Création du monde ---> WorldFactory
    QVariantMap worldData;
    worldData.insert("name", "Earth");

    QVariantMap biomeData;
    biomeData.insert("gravity", (float)9.81);

    biomeData.insert("sky", "Examples/CloudySky");

    biomeData.insert("aR", (float)0.8);
    biomeData.insert("aG", (float)0.8);
    biomeData.insert("aB", (float)0.8);

    biomeData.insert("lR", (float)0.6);
    biomeData.insert("lG", (float)0.6);
    biomeData.insert("lB", (float)0.6);

    QVariantMap camData;
    camData.insert("cX", (float) -20);
    camData.insert("cY", (float) 10);
    camData.insert("cZ", (float) -20);

    camData.insert("lX", (float) 15);
    camData.insert("lY", (float) -5);
    camData.insert("lZ", (float) 15);

    QVariantList spawns;
    QVariantMap zoneSpawn;
    QVariantMap positionSpawn;

    zoneSpawn.insert("type", (int)Spawn::Zone);
    zoneSpawn.insert("minX", (float)-60);
    zoneSpawn.insert("minY", (float)10);
    zoneSpawn.insert("minZ", (float)-60);

    zoneSpawn.insert("maxX", (float)60);
    zoneSpawn.insert("maxY", (float)30);
    zoneSpawn.insert("maxZ", (float)60);

    spawns.append(zoneSpawn);

    positionSpawn.insert("type", (int)Spawn::Position);
    positionSpawn.insert("x", -10);
    positionSpawn.insert("y", 15);
    positionSpawn.insert("z", -10);

    //spawns.append(positionSpawn);

    QVariantMap sceneData;
    sceneData.insert("type", "flatland");
    sceneData.insert("cam", camData);
    sceneData.insert("spawns", spawns);
    sceneData.insert("floor", "Examples/GrassFloor");



    // Spider
    qDebug() << "Spider creation !";
    srand(time(NULL));
    qsrand(time(NULL));
    Entity* e;
    btWorld* world = new btWorld(factory, worldData);
    btShapesFactory* shapesFactory = new btShapesFactory(world);

    btBiome* biome = new btBiome(factory, biomeData);
    world->setBiome(biome);

    btScene* scene = new btScene(factory, sceneData);
    world->setScene(scene);

    world->setup();
    for(int i = 0; i < 10; i++) {

        Spider *spider = new Spider();
        btVector3 pos = world->getSpawnPosition();
        e = spider->createEntity(shapesFactory, pos);
        e->setup();
        ee->addEntity(e);
    }

    qDebug() << "lancement des engines !";

    int cpt = 0;
    while(1) {
        cpt++;
        //qDebug() << cpt;
        foreach(Engine* e, engines) {

            e->beforeStep();
        }

        foreach(Engine* e, engines) {

            e->step();
        }

        foreach(Engine* e, engines) {

            e->afterStep();
        }
        if(cpt%60 == 0) {
            qDebug() << "\r" << cpt/60 << "secondes";
        }
    }

    return a.exec();
}
