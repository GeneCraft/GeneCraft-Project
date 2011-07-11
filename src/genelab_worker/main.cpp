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
#include "btworldfactory.h"
#include "creaturefactory.h"

#include <QMap>
#include <QVariant>
#include <QVariantMap>
#include <QDebug>

#include "tools.h"

#include "ressources/dbrecord.h"
#include "ressources/jsonfile.h"
#include "bullet/bulletengine.h"
#include "statistics/statisticsstorage.h"
#include "statistics/statisticsprovider.h"
#include "statistics/fixationstats.h"
#include "mutation/mutationsmanager.h"

#define MAX_ENTITY 1
#define MAX_TIME 600
#define EPSILON 0.00001

using namespace GeneLabCore;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    btFactory* factory = new btFactory();

    QMap<QString, Engine*> engines = factory->getEngines();
    EntitiesEngine* ee = (EntitiesEngine*)engines.find("Entities").value();

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
    btWorldFactory* worldFactory = new btWorldFactory();
    btShapesFactory* shapesFactory = new btShapesFactory();
    CreatureFactory* creatureFactory = new CreatureFactory();
    QVariant bestGenome;
    float max = 0;
    btWorld* world = worldFactory->createWorld(factory, shapesFactory, worldFactory->createSimpleWorld());
    int cptMutation = 0;
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
                    ((FixationStats*)stat)->resetOrigin();
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
                    bestGenome = e->serialize();
                    r->save(bestGenome);
                    cptMutation = 0;
                }
            }

            foreach(Entity* e, entities) {
                ee->removeEntity(e);
                delete e;
            }


            for(int i = 0; i < MAX_ENTITY; i++) {
                cptMutation++;
                btVector3 pos = world->getSpawnPosition();

                if(cptMutation == 20) {
                    SpiderFamily* family = new SpiderFamily();
                    e = family->createEntity(shapesFactory, pos);
                } else {
                    MutationsManager* mutation = new MutationsManager(QVariant());
                    QVariant newGenome = mutation->mutateEntity(bestGenome);

                    e = creatureFactory->createEntity(newGenome, shapesFactory, pos);
                }
                e->setup();
                ee->addEntity(e);
            }

            stable = false;
        }
    }

    return a.exec();
}
