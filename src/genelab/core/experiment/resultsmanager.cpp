#include "resultsmanager.h"
#include "ressources/jsonfile.h"
#include "ressources/dbrecord.h"

#define RESULTS_DIR "results"

namespace GeneLabCore {

    ResultsManager::ResultsManager(Experiment* exp, int nbBestStored, int nbRandomStored, QString workerName, QObject *parent) :
        QObject(parent)
    {

        db.dbName = "db/genecraft";
        db.port = 80;
        db.url = "http://www.genecraft-project.org";

        this->online = exp->isOnline();
        this->experiment = exp;
        this->resultNameCpt = 0;
        this->bestResultsStored = nbBestStored;
        this->randomResultsStored = nbRandomStored;

        if(!online) {
            this->resultsDirectory = QDir(exp->getId()+"/"+RESULTS_DIR);
            if(!this->resultsDirectory.exists()) {
                this->resultsDirectory.mkpath(".");
            }
        }


        lastLoadedId = "";
        this->workerName = workerName;
        lastModifiedResultLoaded = QDateTime();
    }


    /**
      * To load all old results
      */
    int ResultsManager::load() {
        if(online) {
            return retrieveResults();
        } else {
            return loadResults();
        }
    }

    /**
      * To reload new results
      */
    int ResultsManager::reload() {
        if(online) {
            return retrieveNewResults();
        } else {
            return loadNewResults();
        }
    }

    /**
      * To load results from file system
      */
    int ResultsManager::loadResults() {
        qDebug() << "loading results";
        QDir results = this->resultsDirectory;
        int cptLoaded = 0;
        foreach(QString f, results.entryList(QDir::NoDotAndDotDot
                                             | QDir::Files
                                             | QDir::Readable,
                                             QDir::Time
                                             | QDir::Reversed)) {
            QFile realFile(results.absoluteFilePath(f));
            QFileInfo fileInfo(realFile);
            if(!realFile.exists()) {
                continue;
            }

            this->lastModifiedResultLoaded
                    = qMax(lastModifiedResultLoaded, fileInfo.lastModified());

            JsonFile* file = new JsonFile(results.absoluteFilePath(f));
            QVariant result = file->load();
            bool valid = false;
            Result* r = Result::loadResult(result, valid);
            r->setRessource(file);
            r->setBroadcasted(true);
            if(valid) {
                qDebug() << "valid result from " << f;
                this->addResult(r);
                cptLoaded++;
            } else {
                qDebug() << "invalid file format" << f;
            }

            delete r;

        }

        this->resultNameCpt = cptLoaded;
        qDebug() << cptLoaded;

        return cptLoaded;
    }

    int ResultsManager::loadNewResults() {
        int cptNew = 0;
        QDir results = this->resultsDirectory;
        QDateTime newLastModified = lastModifiedResultLoaded;
        foreach(QString f, results.entryList(QDir::NoDotAndDotDot
                                             | QDir::Files
                                             | QDir::Readable,
                                             QDir::Time)) {
            QFile realFile(results.absoluteFilePath(f));
            QFileInfo fileInfo(realFile);
            if(!realFile.exists()) {
                continue;
            }

            if(this->lastModifiedResultLoaded < fileInfo.lastModified()) {
            } else {
                break;
            }

            if(newLastModified < fileInfo.lastModified()){
                qDebug() << "new last modified" << fileInfo.lastModified();
                newLastModified = fileInfo.lastModified();
            }

            JsonFile* file = new JsonFile(results.absoluteFilePath(f));
            QVariant result = file->load();
            bool valid = false;
            Result* r = Result::loadResult(result, valid);
            r->setRessource(file);
            r->setBroadcasted(true);
            if(valid && r->getWorker() != this->workerName) {
                cptNew++;
                //qDebug() << "valid result from " << f << fileInfo.lastModified();
                this->addResult(r);
            } else {
                //qDebug() << "invalid file format" << f;
            }

            delete r;

        }
        this->lastModifiedResultLoaded = newLastModified;
        return cptNew;
    }

    /**
      * To load results from online database
      */
    int ResultsManager::retrieveResults() {
        int cptLoaded = 0;
        QString id = "_design/results/_view/all?group=true&group_level=2&startkey=[\""+
                     experiment->getId() +"\",\"a\"]&endkey=[\""+
                     experiment->getId() +"\",0]&limit="+
                     QString::number(qMax(this->randomResultsStored, this->bestResultsStored))
                     +"&descending=true";
        DbRecord* r = new DbRecord(db, id);
        QVariant data = r->load();
        delete r;
        QVariantMap results = data.toMap();
        QVariantList rows = results["rows"].toList();
        QVariantList ids;
        foreach(QVariant row, rows) {
            QString id = row.toMap()["value"].toList()[4].toString();
            if(id.left(14) > lastLoadedId.left(14)) {
                lastLoadedId = id;
            }
            ids.append(id);
        }
        QVariantMap postData;
        postData.insert("keys", ids);
        Ressource* re = new DbRecord(db, "_all_docs?include_docs=true", postData);
        QVariant genomes = re->load();

        QVariantMap genomesMap = genomes.toMap();
        QVariantList genomesList = genomesMap["rows"].toList();

        foreach(QVariant genomeResult, genomesList) {
            QVariant genome = genomeResult.toMap()["doc"];
            bool valid;
            Result* result = Result::loadResult(genome, valid);
            if(valid) {
                qDebug() << "valid result from " << id;
                qDebug() << result->getDate() << result->getFitness() << result->getWorker();
                result->setBroadcasted(true);
                this->addResult(result);
                cptLoaded++;
            } else {
                qDebug() << "invalid file format";
            }

            delete result;
        }
        delete re;

        return cptLoaded;
    }

    int ResultsManager::retrieveNewResults() {
        int cptNew = 0;
        QString id = "_design/results/_view/all?group=true&group_level=2&startkey=[\""+
                     experiment->getId() +"\",\"a\"]&endkey=[\""+
                     experiment->getId() +"\",0]&limit="+
                     QString::number(qMax(this->randomResultsStored, this->bestResultsStored))
                     +"&descending=true";
        qDebug() << id;
        DbRecord* r = new DbRecord(db, id);
        QVariant data = r->load();
        delete r;
        QVariantMap results = data.toMap();
        QVariantList rows = results["rows"].toList();
        QString newLastLoadedId = lastLoadedId;
        QVariantList ids;
        foreach(QVariant row, rows) {
            QString id = row.toMap()["value"].toList()[4].toString();

            if(id.left(14) <= lastLoadedId.left(14)) {
                continue;
            }

            if(id.left(14) > newLastLoadedId.left(14)) {
                newLastLoadedId = id;
            }
            ids.append(id);
        }

        QVariantMap postData;
        postData.insert("keys", ids);
        qDebug() << postData;
        Ressource* re = new DbRecord(db, "_all_docs?include_docs=true", postData);
        QVariant genomes = re->load();

        QVariantMap genomesMap = genomes.toMap();
        QVariantList genomesList = genomesMap["rows"].toList();

        foreach(QVariant genomeResult, genomesList) {
            QVariant genome = genomeResult.toMap()["doc"];
            bool valid;
            Result* result = Result::loadResult(genome, valid);
            if(valid && result->getWorker() != this->workerName) {
                qDebug() << "valid result from " << id;
                qDebug() << result->getDate() << result->getFitness() << result->getWorker();
                result->setBroadcasted(true);
                this->addResult(result);
                cptNew++;
            } else {
                qDebug() << "invalid file format";
            }

            delete result;
        }
        delete re;
        lastLoadedId = newLastLoadedId;
        return cptNew;
    }



    /**
      * To save the actual progression of the experiment
      */
    void ResultsManager::save() {
        QVariantList docsList;
        foreach(Result* r, bestResults) {
            if(r->getFitness() > 0.0 && !r->isBroadcasted()) {

                if(r->getRessource() != NULL)
                    continue;

                qDebug() << "save : " << r->getDate() << r->getFitness();

                if(online) {
                    docsList.append(r->serialize());
                } else {
                    QString filename = r->getWorker() + QString::number(resultNameCpt++);
                    r->save(new JsonFile(this->resultsDirectory.absoluteFilePath(filename)));
                }

                r->setBroadcasted(true);
            }
        }

        if(online) {
            QVariantMap postData;
            postData.insert("docs", docsList);
            DbRecord* r = new DbRecord(db, "_bulk_docs");
            r->save(postData);
            delete r;
        }

    }

    /**
      * To add a new result to this experience
      */
    void ResultsManager::addResult(Result* result) {
        // Best one ?
        if(this->bestResults.size() < this->bestResultsStored
           || (this->bestResultsStored > 0 && result->getFitness() > this->bestResults.last()->getFitness())) {
            this->bestResults.append(new Result(*result));
            while(bestResults.size() > this->bestResultsStored) {
                    qSort(bestResults.begin(), bestResults.end(), myLessThan);
                    Result *r = this->bestResults.takeLast();
                    delete r;
            }
        }

        // Random one ?
        this->randomResults.append(new Result(*result));
        while(this->randomResults.size() > this->randomResultsStored) {
            int at = qrand()%randomResults.size();
            Result *r = this->randomResults.takeAt(at);
            delete r;
        }

        qSort(bestResults.begin(), bestResults.end(), myLessThan);
    }


}
