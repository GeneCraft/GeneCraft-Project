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

    btWorld* world = worldFactory->createWorld(factory, shapesFactory, worldFactory->createSimpleWorld());

    for(int i = 0; i < MAX_ENTITY; i++) {

        EntityFamily *spider = new SpiderFamily();
        btVector3 pos = world->getSpawnPosition();
        e = spider->createEntity(shapesFactory, pos);
        e->setup();
        ee->addEntity(e);
    }

    qDebug() << "lancement des engines !";

    return a.exec();
}
