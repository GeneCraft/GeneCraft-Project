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

using namespace GeneLabCore;

int main(int argc, char *argv[])
{
    qsrand(time(NULL));
    srand(time(NULL));
    QCoreApplication a(argc, argv);
    QStringList args = a.arguments();
    QString expName = "../genelab_worker/myOwnExp.exp";
    QString workerName = "worker.exp";

    if(args.length() > 1) {
        expName = args.at(1);
        qDebug() << "loading experience" << args.first();
    }

    if(args.length() > 2) {
        workerName = args.at(2);
        qDebug() << "loading worker" << args.at(1);
    }

    srand(time(NULL));
    qsrand(time(NULL));

    btFactory* factory = new btFactory();

    DataBase database;
    database.dbName = "/db/genecraft/";
    database.url = "http://www.genecraft-project.org";
    database.port = 80;

    // Delete all fucking doc from database
    /*DbRecord* r = new DbRecord(database, "_all_docs");
    QVariant data = r->load();
    QVariantMap docsMap = data.toMap();
    QVariantList docsList = docsMap["rows"].toList();
    foreach(QVariant doc, docsList) {
        QVariantMap docMap = doc.toMap();
        QString id = docMap["id"].toString();
        if(id.size() == 32 && id.left(1) != "_" && id.left(1) != "S" && id > "04a82cae4acfecf9c64c4bf790a58d4b") {
            qDebug() << id << "should be deleted";
            DbRecord * r = new DbRecord(database, id);
            r->deleteDoc(docMap["value"].toMap()["rev"].toString());
            delete r;
        }
    }

    return 0;*/


    Ressource* experience_res = new JsonFile(expName);
    Ressource* worker_res     = new JsonFile(workerName);

    QVariant expdata = experience_res->load();
    //QVariant workerdata = worker_res->load();

    QVariantMap workerData;
    workerData["maxGen"] = 100;
    workerData["popSize"] = 40;
    workerData["name"] = "reds" + QString::number(time(NULL));
    workerData["nbBestResults"] = 150;
    workerData["nbRandomResults"] = 150;
    QVariantMap selectionData;
    selectionData["bestPop"] = 0.2;
    selectionData["bestResult"] = 0.2;
    selectionData["randomPop"] = 0.1;
    selectionData["randomResult"] = 0.2;
    selectionData["randomNew"] = 0.2;
    workerData["selection"] = selectionData;

    Experiment* exp           = new Experiment(expdata);
    ExperimentManager* expMan = new ExperimentManager(factory, exp, workerData);

    expMan->experiment();
    //expMan->broadcastResults();

//    return a.exec();
}
