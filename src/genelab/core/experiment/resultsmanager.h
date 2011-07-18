#ifndef RESULTSMANAGER_H
#define RESULTSMANAGER_H

#include <QObject>
#include <QDir>
#include "result.h"
#include "experiment.h"
#include "ressources/dbrecord.h"

namespace GeneLabCore {

class ResultsManager : public QObject
{
    Q_OBJECT
public:
    explicit ResultsManager(Experiment* exp, int nbBestStored, int nbRandomStored, QString workerName, QObject *parent = 0);

    /**
      * To load all old results
      */
    int load();

    /**
      * To reload new results
      */
    int reload();

    /**
      * To add a new result to this experience
      */
    void addResult(Result* result);

    /**
      * To save the actual progression of the experiment
      */
    void save();

    /**
      * To get the nb best stored results
      */
    int getNbBestStored() {
        return this->bestResultsStored;
    }

    /**
      * To get the nb random stored results
      */
    int getNbRandomStored() {
        return this->randomResultsStored;
    }

    /**
      * To get the actual best results stored
      */
    QList<Result*> getBestResults() {
        return bestResults;
    }


    /**
      * To get the actual best results stored
      */
    QList<Result*> getRandomResults() {
        return randomResults;
    }

protected:
    Experiment* experiment;
    bool online;
    int resultNameCpt;
    QList<Result*> bestResults;
    QList<Result*> randomResults;
    QDir resultsDirectory;
    int bestResultsStored;
    int randomResultsStored;
    QDateTime lastModifiedResultLoaded;
    QString lastLoadedId;
    QString workerName;

    /**
      * To load results from file system
      * Return the number of loaded results
      */
    int loadResults();
    // During the simulation, synchro with other worker
    int loadNewResults();

    /**
      * To load results from online database
      * Return the number of retrieved results
      */
    int retrieveResults();
    // During the simulation, synchro with other worker
    int retrieveNewResults();

    DataBase db;

signals:
    void newResultsAvailable();

public slots:

};

}

#endif // RESULTSMANAGER_H
