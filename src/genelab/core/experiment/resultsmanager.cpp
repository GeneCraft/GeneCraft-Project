#include "resultsmanager.h"
#include "ressources/jsonfile.h"
#include "ressources/dbrecord.h"

#define RESULTS_DIR "results"

namespace GeneCraftCore {

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
            this->resultsDirectory = QDir(RESULTS_DIR+QString("/")+exp->getId()+"/");
            if(!this->resultsDirectory.exists()) {
                this->resultsDirectory.mkpath(".");
            }
        }


        lastLoadedId = "";
        this->workerName = workerName;
        lastModifiedResultLoaded = QDateTime();
    }

    ResultsManager::~ResultsManager() {
        qDeleteAll(bestResults);
        qDeleteAll(randomResults);
        bestResults.clear();
        randomResults.clear();
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
                this->addResult(r);
                cptLoaded++;
            }

            delete r;

        }

        this->resultNameCpt = cptLoaded;

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
                this->addResult(r);
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
                result->setBroadcasted(true);
                this->addResult(result);
                cptLoaded++;
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
        Ressource* re = new DbRecord(db, "_all_docs?include_docs=true", postData);
        QVariant genomes = re->load();

        QVariantMap genomesMap = genomes.toMap();
        QVariantList genomesList = genomesMap["rows"].toList();

        foreach(QVariant genomeResult, genomesList) {
            QVariant genome = genomeResult.toMap()["doc"];
            bool valid;
            Result* result = Result::loadResult(genome, valid);
            if(valid && result->getWorker() != this->workerName) {
                result->setBroadcasted(true);
                this->addResult(result);
                cptNew++;
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
            bool already = false;
            foreach(Result * r, bestResults) {
                if(r->getFitness() + 0.0001 > result->getFitness() &&
                   r->getFitness() - 0.0001 < result->getFitness()) {
                    QVariantMap g1 = r->getGenome().toMap();
                    g1.insert("origins", QVariant());
                    QVariantMap g2 = result->getGenome().toMap();
                    g2.insert("origins", QVariant());
                    // Check if genome is the same
                    if(g1 == g2) {
                        qDebug() << "same genome ! discarding result" << r->getFitness();
                        already = true;
                        break;
                    } else {
                        qDebug() << "same fitness, but different genomes" << r->getFitness();
                    }
                } else if(r->getFitness() + 0.0001 < result->getFitness()) {
                    break;
                }
            }


            if(!already) {
                this->bestResults.append(new Result(*result));
                while(bestResults.size() > this->bestResultsStored) {
                        qSort(bestResults.begin(), bestResults.end(), myLessThan);
                        Result *r = this->bestResults.takeLast();
                        delete r;
                }
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

    void ResultsManager::clear() {
        qDeleteAll(bestResults);
        qDeleteAll(randomResults);
        this->bestResults.clear();
        this->randomResults.clear();
    }


}
