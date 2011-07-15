#ifndef EXPERIMENTMANAGER_H
#define EXPERIMENTMANAGER_H

#include "ressources/dbrecord.h"
#include "experiment.h"
#include "mutation/mutationsmanager.h"

class SelectionManager;

namespace GeneLabCore {
    class ExperimentManager
    {
    public:
        /**
          * Creating an experiment manager for a given experiment
          */
        ExperimentManager(btFactory* factory, Experiment* exp, QVariant workerData) ;

        /**
          * Creating an experiment manager for a giver experiment data
          */
        ExperimentManager(btFactory* factory, QVariant expData, QVariant workerData);

        /**
          * Experimentation loop
          */
        void experiment();

        /**
          * To load results from file system
          * Return the number of loaded results
          */
        int loadResults();
        // During the simulation, synchro with other worker
        void loadNewResults();

        /**
          * To load results from online database
          * Return the number of retrieved results
          */
        int retrieveResults();
        // During the simulation, synchro with other worker
        void retrieveNewResults();

        /**
          * To generate a new population from last population
          */
        void genNewPop();

        /**
          * Only for a new experimentation -> random population
          */
        void genRandomPop();

        /**
          * To evaluate the actual population, generating results
          */
        void evalPop();

        /**
          * To save the actual progression of the experiment
          */
        void save();

        /**
          * To broadcast result to online database
          */
        void broadcastResults();

        /**
          * To add a new result to this experience
          */
        void addResult(Result* result);

        /**
          * To set the new generation of population
          */
        void setActivePopulation(QList<Result*> newPop);

        /**
          * The directory where the results are stored
          */
        QDir getResultsDir() {
            return this->resultsDirectory;
        }

    protected:
        // To simulate a specific entity
        Entity* spawnEntity(QVariant genome);
        bool stabilizeEntity(Entity* e);
        bool simulateEntity(Entity* e);
        float evaluateEntity(Entity* e);
        void engineStep();
        QVariant randomNewEntity();

        void load(QVariant data);

    private:
        Experiment* exp;
        MutationsManager* mutations;
        SelectionManager* selections;
        btFactory* factory;
        bool online;

        btWorldFactory* worldFactory;
        btShapesFactory* shapesFactory;
        CreatureFactory* creatureFactory;

        btWorld* world;

        EntitiesEngine* ee;

        QMap<QString, Engine*> engines;

        int resultNameCpt;
        int maxGen;
        int popSize;
        int bestResultsStored;
        int randomResultsStored;

        QDateTime lastModifiedResultLoaded;
        QString lastLoadedId;

        float probFromBestsResult;
        float probFromBestsPop;
        float probFromRandomResult;
        float probFromRandomPop;
        float probFromRandomNew;

        QString workerName;

        QList<Result*> bestResults;
        QList<Result*> randomResults;
        QList<Result*> activePop;

        QDir resultsDirectory;
        DataBase db;
    };
}

#endif // EXPERIMENTMANAGER_H
