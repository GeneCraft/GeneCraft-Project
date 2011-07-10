#include "experimentmanager.h"
#include "statistics/statisticsprovider.h"
#include "statistics/statisticsstorage.h"

#include "families/spiderfamily.h"

namespace GeneLabCore {
    void ExperimentManager::experiment() {
        /*int cpt = 0;
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
                        //r->save(e->serialize());
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
        }*/
    }
}
