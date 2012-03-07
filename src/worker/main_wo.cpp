/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <QtCore/QCoreApplication>
#include <QApplication>

#include "btfactory.h"

#include "engine.h"

#include "world/bullet/btworld.h"
#include "world/bullet/btscene.h"
#include "world/bullet/btbiome.h"

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

#include "widgets/experiments/workerconfiguration.h"

using namespace GeneCraftCore;

int main(int argc, char *argv[])
{
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

    DataBase database;
    database.dbName = "/db/genecraft/";
    database.url = "http://www.genecraft-project.org";
    database.port = 80;

    // Delete all fucking doc from database
    /*DbRecord* r = new DbRecord(database, "_all_docs?descending=true");
    QVariant data = r->load();
    QVariantMap docsMap = data.toMap();
    QVariantList docsList = docsMap["rows"].toList();
    int cpt = 0;
    foreach(QVariant doc, docsList) {
        cpt++;
        if(cpt > 30) {
            return 1;
        }
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

    QString expName = "";
    QString workerName = "";
    // Loading the worker data
    QVariant workerData;
    QVariant expdata;
    if(args.length() > 1) {
        QString convert = args.at(1);
        if(convert == "convert") {
            if(gui) {
                qDebug() << "convert don't accept --gui option";
                return -1;
            }
            if(args.length() < 5) {
                qDebug() << "not enough parameters, convert take tree parameters, exp1, exp2 and nb of results";
                return -1;
            }
            bool online1, online2;
            online1 = online2 = false;
            QString exp1 = args.at(2);
            QVariant exp1Data, exp2Data;
            QFile expf(exp1);
            if(expf.exists()) {
                JsonFile* f = new JsonFile(exp1);
                exp1Data = f->load();
            } else {
                DbRecord* d = new DbRecord(database, exp1);
                exp1Data = d->load();
                online1 = true;
                if(d->error) {
                    qDebug() << exp1Data;
                    qDebug() << exp1 << "don't exist !";
                    return -1;
                }
            }
            QString exp2 = args.at(3);
            QFile exp2f(exp2);
            qDebug() << exp2 << exp2f.exists();
            if(exp2f.exists()) {
                JsonFile* f = new JsonFile(exp2);
                exp2Data = f->load();
            } else {
                DbRecord* d = new DbRecord(database, exp2);
                exp2Data = d->load();
                online2 = true;
                if(d->error) {
                    qDebug() << exp2Data;
                    qDebug() << exp2 << "don't exist !";
                    return -1;
                }
            }

            int nb = args.at(4).toInt();
            QVariantMap worker;

            worker.insert("name", "conversion");
            worker.insert("maxGen", nb);
            worker.insert("popSize", nb);
            worker.insert("nbBestResults", nb);
            worker.insert("nbRandomResults", nb);
            QVariantMap selection;
            selection.insert("bestPop", 0);
            selection.insert("bestResult", 1);
            selection.insert("randomNew", 0);
            selection.insert("randomPop", 0);
            selection.insert("randomResult", 0);
            worker.insert("selection", selection);
            qDebug() << nb;
            Experiment* experiment1,* experiment2;
            experiment1 = new Experiment(exp1Data);
            experiment1->setOnline(online1);
            experiment2 = new Experiment(exp2Data);
            experiment2->setOnline(online2);
            btFactory* factory = new btFactory();
            ExperimentManager* expManager = new ExperimentManager(factory, experiment2, worker);
            expManager->convert(experiment1, nb);
            qDebug() << "done";
            return -1;
        }
    }

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
        QVariantMap worker;

        worker.insert("name", "Anonymous");
        worker.insert("maxGen", 100);
        worker.insert("popSize", 20);
        worker.insert("nbBestResults", 20);
        worker.insert("nbRandomResults", 200);
        QVariantMap selection;
        selection.insert("bestPop", 20);
        selection.insert("bestResult", 10);
        selection.insert("randomNew", 10);
        selection.insert("randomPop", 10);
        selection.insert("randomResult", 20);
        worker.insert("selection", selection);

        if(QFile("worker.json").exists()) {
            JsonFile* jf = new JsonFile("worker.json");
            worker = jf->load().toMap();
        }
        WorkerConfiguration* workerConfiguration = new WorkerConfiguration(worker);

        workerConfiguration->show();
        a.exec();
        if(!workerConfiguration->isValidated()) {
            qDebug() << "aborted, quitting";
            return 0;
        }
        workerData = workerConfiguration->getWorkerData();
        Ressource* r = new JsonFile("worker.json");
        r->save(workerData);
    }

    srand(time(NULL));
    qsrand(time(NULL));

    btFactory* factory = new btFactory();


    //QVariant workerdata = worker_res->load();
    QVariantMap worker = workerData.toMap();
    worker["name"] = worker["name"].toString() + QString::number(time(NULL));

    ExperimentManager* expMan = new ExperimentManager(factory, exp, worker);

    /**/

    expMan->experiment();
    //expMan->broadcastResults();

//    return a.exec();
}
