#include "experiment.h"

namespace GeneLabCore {
    Experiment::Experiment(QVariant data) {
        QVariantMap map = data.toMap();
        this->id = "WalkingSpider";//map["id"].toString();
        this->description = map["description"].toString();
        this->expData = map;
        this->resultsDirectory = QDir(id+"/results");
        if(!this->resultsDirectory.exists()) {
            this->resultsDirectory.mkpath(".");
        }
        this->maxGen = 200;
        this->popSize = 100;
        this->expTime = 1200;

        seedInfo.insert("type", "family");
        seedInfo.insert("familyName", "spider");
    }


    /**
      * The list of all genomes evaluated for this experience
      * Sorted by fitness
      */
    QList<Result> Experiment::getResults() {
        return this->results;
    }

    /**
      * To add a new result to this experience
      */
    void Experiment::addResult(Result result) {
        sorted = false;
        this->results.append(result);
    }

    /**
      * The actual tested population
      */
    QList<Result> Experiment::getActivePopulation() {
        return QList<Result>(population);
    }

    /**
      * To set the new generation of population
      */
    void Experiment::setActivePopulation(QList<Result> newPop) {
        if(this->population.size() != newPop.size() && this->population.size() != 0)
            qDebug() << "Population size changed ! not a good sign";

        this->population = newPop;
    }

}
