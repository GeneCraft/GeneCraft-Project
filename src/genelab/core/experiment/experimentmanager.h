#ifndef EXPERIMENTMANAGER_H
#define EXPERIMENTMANAGER_H

#include "ressources/dbrecord.h"
#include "experiment.h"
#include "resultsmanager.h"
#include "mutation/mutationsmanager.h"

#include <QtScript>

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
          * To set the new generation of population
          */
        void setActivePopulation(QList<Result*> newPop);


    protected:
        // To simulate a specific entity
        Entity* spawnEntity(QVariant genome);
        bool stabilizeEntity(Entity* e, Result* r);
        bool simulateEntity(Entity* e);
        btScalar evaluateEntity(Entity* e);
        void engineStep();
        QVariant randomNewEntity();

        void load(QVariant data);

        void createEngine();
        void bindEntity(Entity* e);
        void loadFunctions();

    private:
        Experiment* exp;
        MutationsManager* mutations;
        SelectionManager* selections;
        btFactory* factory;

        btWorldFactory* worldFactory;
        btShapesFactory* shapesFactory;
        CreatureFactory* creatureFactory;

        btWorld* world;

        EntitiesEngine* ee;

        QMap<QString, Engine*> engines;

        // Scripting
        QScriptEngine scriptEngine;
        QScriptValue  entityObj;
        QScriptValue  validityFunc;
        QScriptValue  endFunc;
        QScriptValue  dieFunc;
        QScriptValue  fitnessFunc;

        int maxGen;
        int popSize;

        btScalar probFromBestsResult;
        btScalar probFromBestsPop;
        btScalar probFromRandomResult;
        btScalar probFromRandomPop;
        btScalar probFromRandomNew;

        QString workerName;

        QList<Result*> activePop;

        ResultsManager* results;
        RessourcesManager* ressources;
    };
}

#endif // EXPERIMENTMANAGER_H
