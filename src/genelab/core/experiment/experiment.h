#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "result.h"
#include <QList>
#include <QDebug>
#include <QVariantMap>

namespace GeneLabCore {
    class Experiment
    {
    public:
        Experiment(QVariant data) {
            QVariantMap map = data.toMap();
            this->id = map["id"].toString();
            this->description = map["description"].toString();
            this->expData = map;
        }

        /**
          * The list of all genomes evaluated for this experience
          * Sorted by fitness
          */
        QList<Result> getResults() {
            if(!sorted) {
                qSort(this->results.begin(), this->results.end(), qGreater<Result>());
                sorted = true;
            }

            return QList<Result>(this->results);
        }

        /**
          * To add a new result to this experience
          */
        void addResult(Result result) {
            sorted = false;
            this->results.append(result);
        }

        /**
          * The actual tested population
          */
        QList<Result> getActivePopulation() {
            return QList<Result>(population);
        }

        /**
          * To set the new generation of population
          */
        void setActivePopulation(QList<Result> newPop) {
            if(this->population.size() != newPop.size())
                qDebug() << "Population size changed ! not a good sign";

            this->population = newPop;
        }

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

    protected:
        QList<Result> results;
        QList<Result> population;
        bool sorted;
        QString id;
        QString description;
        QVariantMap expData;
    };
}

#endif // EXPERIMENT_H
