#include <QtCore/QCoreApplication>
#include <QApplication>

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
#include <direct.h>

#include "ressources/dbrecord.h"
#include "ressources/jsonfile.h"
#include "bullet/bulletengine.h"
#include "statistics/statisticsstorage.h"
#include "statistics/statisticsprovider.h"
#include "statistics/fixationstats.h"
#include "mutation/mutationsmanager.h"

#include "experiment/experimentmanager.h"

#include "widgets/experiments/workerconfiguration.h"

using namespace GeneLabCore;

int main(int argc, char *argv[])
{
    char newPath[500];
    getcwd(newPath, 500);
    qDebug() << "Current Path: " << newPath;
    qsrand(time(NULL));
    srand(time(NULL));
    bool gui = false;
    for(int i=1; i<argc; i++)
        if(!strcmp(argv[i], "--gui")){
        gui = true;
        break;
    }

    QApplication a(argc, argv, gui);
    QStringList args = a.arguments();
    QString expName = "";
    QString workerName = "";

    DataBase database;
    database.dbName = "/db/genecraft/";
    database.url = "http://www.genecraft-project.org";
    database.port = 80;

    // Loading the worker data
    QVariant workerData;
    QVariant expdata;

    bool online = false;
    // One argument, the experience (id or file)
    if(args.length() > 1) {
        expName = args.at(1);
        if(expName == "--gui") {
            if(args.length() > 2) {
                expName = args.at(2);
            }
        }
        qDebug() << "loading experience at" << args.at(1);
        Ressource* experience_res = new JsonFile(expName);
        expdata = experience_res->load();

        if(expdata == QVariant()) {
            qDebug() << expName << "not found in file system, looking online";
            online = true;
            Ressource* experience_db = new DbRecord(database, expName);
            expdata = experience_db->load();
        }

    } else {
        qDebug() << "usage : genecraft_worker EXP_FILE|EXP_ID [WORKER_CONFIG]";
        return -1;
    }

    if(expdata == QVariant() || expdata.toMap().contains("error")) {
        qDebug() << expName << "not found in file system nor online... first argument should be the experiment";
        return -1;
    }

    if(!expdata.toMap().contains("author") || !expdata.toMap().contains("evalFunction") || !expdata.toMap().contains("mutations")) {
        qDebug() << expName << "does not contains experiment data. It should by an experiment file name or online db id.";
        return -1;
    }


    Experiment* exp           = new Experiment(expdata);
    exp->setOnline(online);

    // Two argument, the experience and the worker data
    if(args.length() > 2) {
        workerName = args.at(2);
        if(args.at(1) == "--gui" || workerName == "--gui") {
            if(args.length() > 3) {
                workerName = args.at(3);
            } else {
                workerName = "";
            }
        }
        if(workerName != "") {
            qDebug() << "loading worker configuration at" << workerName;
            Ressource* worker_res = new JsonFile(workerName);
            workerData = worker_res->load();
        }
    }

//    WorkerConfiguration* workerConfiguration = new WorkerConfiguration();

    if(workerData == QVariant() ||
       !workerData.toMap().contains("name") ||
       !workerData.toMap().contains("maxGen") ||
       !workerData.toMap().contains("popSize") ||
       !workerData.toMap().contains("selection")) {

        qDebug() << "Didn't find any worker configuration, or incomplete one. Starting the gui-config";
	WorkerConfiguration* workerConfiguration = new WorkerConfiguration();

        workerConfiguration->show();
        a.exec();
        workerData = workerConfiguration->getWorkerData();
    }

    srand(time(NULL));
    qsrand(time(NULL));

    btFactory* factory = new btFactory();


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


    //QVariant workerdata = worker_res->load();


    ExperimentManager* expMan = new ExperimentManager(factory, exp, workerData);

    /**/

    expMan->experiment();
    //expMan->broadcastResults();

//    return a.exec();
}
