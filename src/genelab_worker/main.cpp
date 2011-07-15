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
#include <ctime>

#include "ressources/dbrecord.h"
#include "ressources/jsonfile.h"
#include "bullet/bulletengine.h"
#include "statistics/statisticsstorage.h"
#include "statistics/statisticsprovider.h"
#include "statistics/fixationstats.h"
#include "mutation/mutationsmanager.h"

#include "experiment/experimentmanager.h"

#define MAX_ENTITY 1
#define MAX_TIME 1800
#define EPSILON 0.00001

using namespace GeneLabCore;

int main(int argc, char *argv[])
{
    qsrand(time(NULL));
    srand(time(NULL));
    QCoreApplication a(argc, argv);
    srand(time(NULL));
    qsrand(time(NULL));

    btFactory* factory = new btFactory();

    DataBase database;
    database.dbName = "/db/genecraft/";
    database.url = "http://www.genecraft-project.org";
    database.port = 80;

    Ressource* experience_res = new JsonFile("spider.exp");
    Ressource* worker_res = new JsonFile("myworker.exp");
    QVariant expdata = experience_res->load();
    QVariant workerdata = worker_res->load();
    Experiment* exp = new Experiment(expdata);
    ExperimentManager* expMan = new ExperimentManager(factory, exp, workerdata);

    expMan->experiment();
    //expMan->broadcastResults();

    return a.exec();
}
