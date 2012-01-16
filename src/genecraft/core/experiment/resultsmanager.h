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

#ifndef RESULTSMANAGER_H
#define RESULTSMANAGER_H

#include <QObject>
#include <QDir>
#include "result.h"
#include "experiment.h"

#include "ressources/dbrecord.h"
#include "tools.h"

namespace GeneCraftCore {

class ResultsManager : public QObject
{
    Q_OBJECT
public:
    explicit ResultsManager(Experiment* exp, int nbBestStored, int nbRandomStored, QString workerName, QObject *parent = 0);
    ~ResultsManager();
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

    /**
      * The db object
      */
    DataBase getDb() {
        return this->db;
    }

    /**
      * Delete all results from this experiment
      */
    void deleteAll()
    {
        if(!online) {
            Tools::removeDir(resultsDirectory.absolutePath());
            clear();
        }
        else {
            // TODO DELETE ONLINE RESULTS
        }
    }

    /**
      * Clear results lists
      */
    void clear();

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
