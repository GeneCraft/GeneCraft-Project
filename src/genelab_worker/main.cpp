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
#include "brain/brain.h"
#include "brain/brainpluggrid.h"
#include "entities/entitiesengine.h"

#include "btshapesfactory.h"
#include "btworldfactory.h"
#include "creaturefactory.h"
#include "body/bone.h"
#include "body/fixation.h"
#include "body/treeshape.h"
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
#define MAX_TIME 1800
#define EPSILON 0.00001

using namespace GeneLabCore;



void setupBonesProperties2(Fixation *fixation, int action)
{
    QList<Bone *> bones = fixation->getBones();
    for(int i=0;i<bones.size();++i)
    {
        Bone *bone = bones.at(i);

        switch(action)
        {
            case 0:
                bone->disableMotors();
            break;
            case 1:
                bone->setBrainMotors();
            break;
            case 2:
                bone->setRandomMotors();
            break;
            case 3:
                bone->setNormalPositionMotors();
            break;
        }

        setupBonesProperties2(bone->getEndFixation(),action);
    }
}



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
    r = new DbRecord(database, "SpiderMutated2");
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
    int cptBoostrap = 10;
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
	if(!stable && cpt < 100) {
        foreach(Engine* e, engines) {

            e->beforeStep();
        }
    
        foreach(Engine* e, engines) {
    
            e->step();
        }
        
        foreach(Engine* e, engines) {
         
            e->afterStep();
        }
	continue;	
	}
        if(!stable && cpt < 600) {
            QList<Entity*> entities = ee->getAllEntities();
            foreach(Entity* e, entities) {
		setupBonesProperties2(e->getShape()->getRoot(), 3);
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
		    
                    e->setAge(0);
		    setupBonesProperties2(e->getShape()->getRoot(), 1);
		    qDebug() << "stable at " << cpt;
                    cpt = 0;
		}
            }
//            ((BulletEngine*)engines.find("Bullet").value())->beforeStep();
//            ((BulletEngine*)engines.find("Bullet").value())->step();
//            ((BulletEngine*)engines.find("Bullet").value())->afterStep();

        foreach(Engine* e, engines) {
                   
            e->beforeStep();
        }
                    
        foreach(Engine* e, engines) {
                
            e->step();
        }
                    
        foreach(Engine* e, engines) {
                    
            e->afterStep();
        }


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

        if(cpt >= MAX_TIME || !stable) {
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
                    qDebug() << "taille du cerveau " << e->getBrain()->getPlugGrid()->getSize();
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

                if(cptBoostrap > 0) {
		    cptBoostrap--;
                    SpiderFamily* family = new SpiderFamily();
                    e = family->createEntity(shapesFactory, pos);
                } else {
                    MutationsManager* mutation = new MutationsManager(QVariant());
		    QVariant newGenome = bestGenome;
		for(int i = 0; i < 1 + cptMutation/100 || (newGenome == bestGenome); i++) {
                    newGenome = mutation->mutateEntity(newGenome);
                    qDebug() << (newGenome == bestGenome);
//		    if(!(newGenome == bestGenome))
//			qDebug() << newGenome << "\n" << bestGenome;
	            qDebug() << "mutating from best once";
		}
                    e = creatureFactory->createEntity(newGenome, shapesFactory, pos);
                }
//		if(cptMutation > 50) {
//			qDebug() << "adding mutation to best genome !";
//			bestGenome = newGenome;// boosting mutation
//		}
                e->setup();
                ee->addEntity(e);
                qDebug() << "brain size " << e->getBrain()->getPlugGrid()->getSize();
            }

            stable = false;
        }
    }

    return a.exec();
}
