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

#ifndef EXPERIMENTMANAGER_H
#define EXPERIMENTMANAGER_H

#include "ressources/dbrecord.h"
#include "experiment.h"
#include "resultsmanager.h"
#include "mutation/mutationsmanager.h"

#include <QtScript>

class SelectionManager;

namespace GeneCraftCore {
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
          * Convert nb results from another experiment
          */
        void convert(Experiment* from, int nb);

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

        void waitAndSetGravity(Entity *e);

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
