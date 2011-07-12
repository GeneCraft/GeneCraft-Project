#ifndef EXPERIMENTMANAGER_H
#define EXPERIMENTMANAGER_H

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
        ExperimentManager(btFactory* factory, Experiment* exp) ;

        /**
          * Creating an experiment manager for a giver experiment data
          */
        ExperimentManager(btFactory* factory, QVariant expData);

        /**
          * Experimentation loop
          */
        void experiment();

        /**
          * To load results from file system
          * Return the number of loaded results
          */
        int loadResults();

        /**
          * To load results from online database
          * Return the number of retrieved results
          */
        int retrieveResults();

        /**
          * To generate a new population from last population
          */
        void genNewPop();

        /**
          * To generate a new population from existing result
          */
        void genNewPopFromResults();

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

    protected:
        // To simulate a specific entity
        Entity* spawnEntity(QVariant genome);
        bool stabilizeEntity(Entity* e);
        bool simulateEntity(Entity* e);
        float evaluateEntity(Entity* e);
        void engineStep();

    private:
        Experiment* exp;
        MutationsManager* mutations;
        SelectionManager* selections;
        btFactory* factory;
        bool broadcast;

        btWorldFactory* worldFactory;
        btShapesFactory* shapesFactory;
        CreatureFactory* creatureFactory;

        btWorld* world;

        EntitiesEngine* ee;

        QMap<QString, Engine*> engines;

        int resultNameCpt;
    };
}

#endif // EXPERIMENTMANAGER_H
