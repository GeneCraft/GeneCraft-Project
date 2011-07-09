#include <QtCore/QCoreApplication>

#include "btfactory.h"

#include "engine.h"

#include "world/btworld.h"
#include "world/btscene.h"
#include "world/btbiome.h"

#include "families/spiderfamily.h"
#include "families/antfamily.h"
#include "families/snakefamily.h"
#include "entity.h"
#include "entities/entitiesengine.h"

#include "btshapesfactory.h"

#include <QMap>
#include <QVariant>
#include <QVariantMap>
#include <QDebug>

#include "tools.h"

#include "ressources/dbrecord.h"
#include "bullet/bulletengine.h"
#include "statistics/statisticsstorage.h"
#include "statistics/statisticsprovider.h"

#define MAX_ENTITY 1
#define MAX_TIME 6000
#define EPSILON 0.00001

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

    // Biome
    QVariantMap biomeData;
    biomeData.insert("gravity", (float)9.81);
    biomeData.insert("sky", "Examples/CloudySky");
    biomeData.insert("aR", (float)0.8);
    biomeData.insert("aG", (float)0.8);
    biomeData.insert("aB", (float)0.8);
    biomeData.insert("lR", (float)0.6);
    biomeData.insert("lG", (float)0.6);
    biomeData.insert("lB", (float)0.6);

    // Camera
    QVariantMap camData;
    camData.insert("cX", (float) -20);
    camData.insert("cY", (float) 10);
    camData.insert("cZ", (float) -20);
    camData.insert("lX", (float) 15);
    camData.insert("lY", (float) -5);
    camData.insert("lZ", (float) 15);

    // Spawn areas
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
    //spawns.append(zoneSpawn);

    positionSpawn.insert("type", (int)Spawn::Position);
    positionSpawn.insert("x", -10);
    positionSpawn.insert("y", 15);
    positionSpawn.insert("z", -10);
    spawns.append(positionSpawn);

    // Static boxes
    QVariantList staticBoxes;

    // MineCraft Floor
    /*int sizeX = 10;
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
    }*/

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

    float max = 0;
    QString bestGen = "";
    Ressource* r;
    DataBase database;
    database.dbName = "/db/genecraft/";
    database.url = "http://www.genecraft-project.org";
    database.port = 80;
    r = new DbRecord(database, "HighestSpider" + QString::number(time(NULL)));
    r->load();

    // Spider
    qDebug() << "Spider creation !";
    srand(time(NULL));
    qsrand(time(NULL));
    Entity* e;
    btShapesFactory* shapesFactory = new btShapesFactory();
    btWorld* world = new btWorld(factory, shapesFactory, worldData);
    shapesFactory->setWorld(world);

    btBiome* biome = new btBiome(world, biomeData);
    world->setBiome(biome);

    btScene* scene = new btScene(world, sceneData);
    world->setScene(scene);

    world->setup();
    for(int i = 0; i < MAX_ENTITY; i++) {

        EntityFamily *spider = new SpiderFamily();
        btVector3 pos = world->getSpawnPosition();
        e = spider->createEntity(shapesFactory, pos);
        e->setup();
        ee->addEntity(e);
    }

    qDebug() << "lancement des engines !";

    int cpt = 0;
    bool stable = false;
    int needStableCpt = 0;
    float lastHeight = 0;
    while(1) {
        cpt++;
        if(!stable && cpt < 600) {
            QList<Entity*> entities = ee->getAllEntities();
            foreach(Entity* e, entities) {
                StatisticsProvider* stat = e->getStatistics().find("FixationStats").value();
                stat->step();
                Statistic* s = e->getStatisticByName("Root relative velocity");
                if(lastHeight + EPSILON > s->getValue() &&
                   lastHeight - EPSILON < s->getValue()) {
                    needStableCpt++;
                } else {
                    needStableCpt = 0;
                }
                lastHeight = s->getValue();

                if(needStableCpt > 60) {
                    stable = true;
                    s->resetAll();
                    needStableCpt = 0;
                }
            }
            ((BulletEngine*)engines.find("Bullet").value())->beforeStep();
            ((BulletEngine*)engines.find("Bullet").value())->step();
            ((BulletEngine*)engines.find("Bullet").value())->afterStep();
            continue;
        }

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
            //qDebug() << "\r" << cpt/60 << "secondes";
        }

        if(cpt >= MAX_TIME) {
            qDebug() << "new entity !";
            cpt = 0;
            // Evaluation
            QList<Entity*> entities = ee->getAllEntities();
            if(stable)
            foreach(Entity* e, entities) {
                Statistic* s = e->getStatisticByName("Root relative velocity");
                qDebug() << s->getSum();
                if(s->getSum() > max) {
                    max = s->getSum();
                    qDebug() << "! new max " << s->getSum();
                    r->save(e->serialize());
                }
            }

            foreach(Entity* e, entities) {
                ee->removeEntity(e);
                delete e;
            }


            for(int i = 0; i < MAX_ENTITY; i++) {

                EntityFamily *spider = new SpiderFamily();
                btVector3 pos = world->getSpawnPosition();
                e = spider->createEntity(shapesFactory, pos);
                e->setup();
                ee->addEntity(e);
            }

            stable = false;
        }
    }

    return a.exec();
}
