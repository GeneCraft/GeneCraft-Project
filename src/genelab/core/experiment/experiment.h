#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "result.h"
#include <QList>
#include <QDebug>
#include <QVariantMap>
#include <QDir>

namespace GeneLabCore {
    class Experiment
    {
    public:
        Experiment(QVariant data);

        /**
          * The list of all genomes evaluated for this experience
          * Sorted by fitness
          */
        QList<Result> getResults();

        /**
          * To add a new result to this experience
          */
        void addResult(Result result);

        /**
          * The actual tested population
          */
        QList<Result> getActivePopulation();

        /**
          * To set the new generation of population
          */
        void setActivePopulation(QList<Result> newPop);

        /**
          * Experiment name, or id
          */
        QString getId() {
            return this->id;
        }

        /**
          * The experience description given by the creator
          */
        QString getDescription() {
            return this->description;
        }

        // TODO : Move to a struct
        /**
          * The actual experiment informations, must be parsed and stored in a struct
          */
        QVariantMap getExpData() {
            return this->expData;
        }

        int getPopSize() {
            return popSize;
        }

        int getMaxGen() {
            return maxGen;
        }

        QDir getResultsDir() {
            return this->resultsDirectory;
        }

        QVariantMap getSeedInfo() {
            return this->seedInfo;
        }

        int getExpTime() {
            return this->expTime;
        }

    protected:
        QList<Result> results;
        QList<Result> population;
        bool sorted;
        QString id;
        QString description;
        QVariantMap expData;
        QDir resultsDirectory;
        Ressource* expFile;
        int maxGen;
        int popSize;
        int expTime;

        QVariantMap seedInfo;

    };
}

#endif // EXPERIMENT_H
