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

#include "experimentmanager.h"
#include "statistics/statisticsprovider.h"
#include "statistics/statisticsstorage.h"

#include <QDir>
#include <ctime>
#include "ressources/jsonfile.h"

#include "families/spiderfamily.h"
#include "families/snakefamily.h"
#include "families/genericfamily.h"
#include "families/antfamily.h"
#include "families/caterpillarfamily.h"
#include "families/realspiderfamily.h"
#include "entity.h"
#include "entityfamily.h"

#include "btworldfactory.h"
#include "creaturefactory.h"
#include "btshapesfactory.h"

#include "bullet/btworld.h"
#include "entities/entitiesengine.h"
#include "LinearMath/btVector3.h"

#include "body/treeshape.h"
#include "body/fixation.h"

#include "statistics/statisticsstorage.h"
#include "statistics/statisticsprovider.h"
#include "statistics/fixationstats.h"
#include "statistics/treeshapestats.h"

#include "ressources/dbrecord.h"
#include "ressources/ressourcesmanager.h"

#include "tools.h"

#include <QtScript>
#include <qxtjson.h>

namespace GeneCraftCore {

    /**
      * Creating an experiment manager for a given experiment
      */
    ExperimentManager::ExperimentManager(btFactory* factory, Experiment* exp, QVariant workerData) {
        this->factory = factory;
        this->exp = exp;
        this->load(workerData);
    }

    /**
      * Creating an experiment manager for a giver experiment data
      */
    ExperimentManager::ExperimentManager(btFactory* factory, QVariant expData, QVariant workerData) {
        this->factory = factory;
        this->exp = new Experiment(Ressource::load(expData));
        this->load(workerData);
    }


    //protected
    void ExperimentManager::load(QVariant workerData) {
        QVariantMap workerMap = workerData.toMap();
        this->maxGen          = workerMap["maxGen"].toInt();
        this->popSize         = workerMap["popSize"].toInt();
        this->workerName      = workerMap["name"].toString();

        int bestResultsStored   = workerMap["nbBestResults"].toInt();
        int randomResultsStored = workerMap["nbRandomResults"].toInt();

        this->results = new ResultsManager(exp,bestResultsStored, randomResultsStored,workerName);
        if(exp->isOnline()) {
            this->ressources = new RessourcesManager(this->results->getDb(), QDir());
        }

        QVariantMap selectionMap   = workerMap["selection"].toMap();
        this->probFromBestsPop     = selectionMap["bestPop"].toDouble();
        this->probFromBestsResult  = selectionMap["bestResult"].toDouble();
        this->probFromRandomPop    = selectionMap["randomPop"].toDouble();
        this->probFromRandomResult = selectionMap["randomResult"].toDouble();
        this->probFromRandomNew    = selectionMap["randomNew"].toDouble();

        // Normalisation of probability
        btScalar sumProb = probFromBestsPop + probFromBestsResult + probFromRandomNew
                        + probFromRandomPop + probFromRandomResult;

        this->probFromBestsPop     /= sumProb;
        this->probFromBestsResult  /= sumProb;
        this->probFromRandomNew    /= sumProb;
        this->probFromRandomPop    /= sumProb;
        this->probFromRandomResult /= sumProb;
    }

    void ExperimentManager::bindEntity(Entity* e) {
        // Create a new empty script object
        entityObj      = scriptEngine.newObject();

        // For each statistics of the entity
        QMap<QString, Statistic*> stats = e->getStatisticsStorage()->getStatistics();
        foreach(QString statName, stats.keys()) {
            Statistic* stat = stats[statName];
            // Insert a new properties of our top level object
            // With the name of the statistic
            QScriptValue statObject = scriptEngine.newQObject(stat);
            entityObj.setProperty(statName, statObject);
        }

        // And set the new object created as the "entity" object
        // in the global scope
        scriptEngine.globalObject().setProperty("entity", entityObj);
    }

    void ExperimentManager::loadFunctions() {
        fitnessFunc  = scriptEngine.evaluate(exp->getEvalFunction());
        validityFunc = scriptEngine.evaluate(exp->getValidityFunction());
        endFunc      = scriptEngine.evaluate(exp->getEndFunction());
        dieFunc      = scriptEngine.evaluate(exp->getDieFunction());
    }

    /**
      * Experimentation loop
      */
    void ExperimentManager::experiment() {

        // The entity engine
        engines = factory->getEngines();
        ee = (EntitiesEngine*)engines.find("Entities").value();

        // All those cool factory !
        worldFactory    = new btWorldFactory();
        shapesFactory   = new btShapesFactory();
        creatureFactory = new CreatureFactory();
        mutations       = exp->getMutationsManager();

        // The world to experiment inside
        world = worldFactory->createWorld(factory, shapesFactory, exp->getWorldDataMap());

        // Nb gen to compute
        int nbGen = this->maxGen;

        // from db (online experience)
        int nbLoaded = results->load();
        qDebug() << "loaded" << nbLoaded << "results from db/file";

        this->genNewPop();
        qDebug() << "generated" << this->popSize << "mutated entities from results";

        // For each generations
        while(nbGen > 0 || nbGen == -1) {
            qDebug() << "------ GENERATION" << this->maxGen - nbGen << "/" << nbGen << "-------";
            nbGen--;

            // Evaluation of population
            evalPop();

            // Broadcast result to community
            results->save();
            results->reload();

            // Generate new population
            qDebug() << "Generation of a new population";
            genNewPop();
            qDebug() << "generated" << this->popSize << "mutated entities from active population";

            qDebug() << "reloading ressources on the server, to avoid to much out of sync";
            if(exp->isOnline()) {
                this->ressources->reloadDb();
            }
        }

        delete world;
        delete worldFactory;
        delete shapesFactory;
        delete creatureFactory;
        delete exp;
        delete results;
    }

    void ExperimentManager::convert(Experiment *from, int nb) {
        qDebug() << "Converting" << nb << "results from" << from->getId() << "to" << exp->getId();
        // The entity engine
        engines = factory->getEngines();
        ee = (EntitiesEngine*)engines.find("Entities").value();

        // All those cool factory !
        worldFactory    = new btWorldFactory();
        shapesFactory   = new btShapesFactory();
        creatureFactory = new CreatureFactory();

        // The world to experiment inside
        world = worldFactory->createWorld(factory, shapesFactory, exp->getWorldDataMap());

        // The old results
        ResultsManager* oldresults = new ResultsManager(from, nb, nb, "");
        qDebug() << from->isOnline();
        int nbLoaded = oldresults->load();
        qDebug() << "loaded" << nbLoaded << "results from db/file";

        // Evaluation of population
        this->activePop = oldresults->getBestResults();
        foreach(Result* r, activePop) {
            r->setBroadcasted(false);
            r->setRessource(NULL);

            // date
            r->setDate(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

            // exp
            r->setExperienceId(exp->getId());

            // conversion
            r->setWorker("exp_" + from->getId());

            // reset fitness
            r->resetFitness();
        }

        results->clear();
        evalPop();

        // Broadcast result to community
        results->save();
        results->reload();

        qDebug() << "reloading ressources on the server, to avoid to much out of sync";
        if(exp->isOnline()) {
            this->ressources->reloadDb();
        }

        delete world;
        delete worldFactory;
        delete shapesFactory;
        delete creatureFactory;
        delete exp;
        delete from;
        delete results;
    }


    /**
      * To create a boodstrap pop
      */
    void ExperimentManager::genRandomPop() {
        // The new random population
        QList<Result*> newPop;

        // Creating N new spider
        for(int i = 0; i < this->popSize; i++) {
            newPop.append(new Result(exp->getId(), 0, 0, 0, this->randomNewEntity(), this->workerName));
        }

        // Adding the population to the experience
        this->setActivePopulation(newPop);
    }

    // A new entity
    QVariant ExperimentManager::randomNewEntity() {
        // How to create the new entities ?
        QVariantMap seedInfo = exp->getSeedInfo();
        QString type = seedInfo["type"].toString();
        // From a family
        if(type == "family") {
            // Which one ?
            QString familyName = seedInfo["family"].toString();
            EntityFamily* family;

            btVector3 position = world->getSpawnPosition();

            // The spider ! Scary !
            if(familyName == "spider") {
                // New entity
                family = new SpiderFamily();
                //qDebug() << "new random spider entity";
            } else if(familyName == "ant") {
                family = new AntFamily();
                //qDebug() << "new random ant entitiy";
            } else if(familyName == "caterpillar") {
                family = new CaterpillarFamily();
                //qDebug() << "new random caterpillar entity";
            } else if(familyName == "snake") {
                family = new SnakeFamily();
                //qDebug() << "new random snake entity";
            } else if(familyName == "realSpider") {
                family = new RealSpiderFamily();
            } else if(familyName == "virgin"){
                //qDebug() << "new random virgin entity";
                Entity* e = GenericFamily::createVirginEntity(shapesFactory, Tools::random(0.2, 1.0), position);
                e->setup();
                e->setGeneration(0);
                QVariant genome = e->serialize();
                // Tree starting mutations !
                for(int i = 0; i < 3; i++)
                    genome = mutations->mutateEntity(genome);

                delete e;

                return genome;
            } else {
                qDebug() << "family not found !";
                Entity* e = GenericFamily::createVirginEntity(shapesFactory, Tools::random(0.2, 1.0), position);
                e->setup();
                e->setGeneration(0);
                QVariant genome = e->serialize();
                // Tree starting mutations !
                for(int i = 0; i < 3; i++)
                    genome = mutations->mutateEntity(genome);

                delete e;

                return genome;
            }

            Entity* e = family->createEntity(shapesFactory, position);

            // Setup to be able to serialize
            e->setup();
            e->setGeneration(0);
            // Serialisation
            QVariant genome = e->serialize();
            delete e;
            delete family;
            return genome;
        } else if(type == "fixedGenomes") {
            //qDebug() << "loading from fixed genome";
            // TODO FIXME !
            static QVariantList genomes = QVariantList();
            if(genomes == QVariantList()) {
                QVariantList genomesInfo = seedInfo["genomes"].toList();
                foreach(QVariant genome, genomesInfo) {
                    genomes.append(Ressource::load(genome));
                }
            }
            int randomGen = qrand()%genomes.size();
            return mutations->mutateEntity(genomes.at(randomGen));
        }
        return QVariant();
    }

    /**
      * To generate a new population from last population
      */
    void ExperimentManager::genNewPop() {
        // Sorting active pop if needed
        if(this->probFromBestsPop > 0.0f)
            qSort(activePop.begin(), activePop.end(), myLessThan);

        QList<Result*> newActivePop;

        // For probFromBestsResult part
        int max = this->results->getBestResults().size();
        if(max)
        for(int i = 0; i < this->popSize*this->probFromBestsResult; i++) {
            // No bests results enough?
            if(i >= max)
                break;

            // Best 'i one
            Result* r = results->getBestResults().at(i);

            // Mutation of best one
            newActivePop.append(new Result(this->exp->getId(), 0, 0, 0,
                                          mutations->mutateEntity(r->getGenome()), this->workerName));
            qDebug() << "loading mutation of best results with fitness " << r->getFitness();
        }

        // For probFromRandomResults part
        max = results->getRandomResults().size();
        if(max)
        for(int i = 0; i < this->popSize*this->probFromRandomResult; i++) {
            // random new from results
            int id = qrand()%max;
            Result* r = results->getRandomResults().at(id);
            QVariant genome = r->getGenome();

            // Mutation
            QVariant newGenome = mutations->mutateEntity(genome);

            qDebug() << (newGenome == genome);
            // Adding to the active population
            newActivePop.append(new Result(exp->getId(), 0, 0, 0, newGenome, workerName));
            qDebug() << "loading mutation of random results with fitness " << r->getFitness();
        }

        // For probFromBestsPop part
        max = activePop.size();
        if(max)
        for(int i = 0; i < this->popSize*this->probFromBestsPop; i++) {
            // No bests results enough?
            if(i >= max)
                break;

            // Best 'i one
            Result* r = activePop.at(i);

            // Mutation of best one
            newActivePop.append( new Result(this->exp->getId(), 0, 0, 0,
                                            mutations->mutateEntity(r->getGenome()), this->workerName));
            qDebug() << "loading mutation of activePop with fitness " << r->getFitness();
        }

        // For probFromRandomResults part
        if(max)
        for(int i = 0; i < this->popSize*this->probFromRandomPop; i++) {
            // random new from results
            int id = qrand()%max;
            Result* r = activePop.at(id);
            QVariant genome = r->getGenome();

            // Mutation
            QVariant newGenome = mutations->mutateEntity(genome);

            qDebug() << (newGenome == genome);
            // Adding to the active population
            newActivePop.append(new Result(exp->getId(), 0, 0, 0, newGenome, workerName));
            qDebug() << "loading mutation of activePop with fitness " << r->getFitness();
        }

        //Remaining random new
        int needed = this->popSize - newActivePop.length();
        for(int i = 0; i < needed; i++) {
            QVariant newGenome = this->randomNewEntity();
            newActivePop.append(new Result(exp->getId(), 0, 0, 0, newGenome, workerName));
            qDebug() << "new random genome from seeds !";
        }

        this->setActivePopulation(newActivePop);
    }

    /**
      * To evaluate the actual population, generating results
      */
    void ExperimentManager::evalPop() {
        // for each individual in the population
        foreach(Result* r, this->activePop) {

            // To avoid saving rounding problematic
            // Could still append if the entity modified himself during or
            // At the beginning of the simulation
            r->setGenome(QxtJSON::parse(QxtJSON::stringify(r->getGenome())));

            qDebug() << "Evaluation of a specimen" << exp->getNbRun() << "times.";
            for(int run = 0; run < exp->getNbRun(); run++) {

                // Spawn the entity from his genome
                Entity *e = this->spawnEntity(r->getGenome());

                // Reset all stats
                foreach(Statistic* stat, e->getStatisticsStorage()->getStatistics()) {
                    stat->resetAll();
                }

                // Set age
                e->setAge(0);
                e->getShape()->getRoot()->setOutputsFrom(fromNormal); // From brain


                bool stable, simulated;
                btScalar fitness;

                // Make it stable if needed
                if(exp->getOnlyIfEntityIsStable())
                    stable = this->stabilizeEntity(e, r);
                else
                    stable = true;

                // Stabilisation reached simulate it
                if(stable)
                    simulated = this->simulateEntity(e);

                // If stable and simulated, evaluate it
                if(stable) {
                    if(simulated) {
                        fitness = this->evaluateEntity(e);
                        r->setFitness(fitness);

                        // Store the statistics inside the result
                        QString stats = scriptEngine.evaluate("JSON.stringify(entity)").toString();
                        r->setStatistics(QxtJSON::parse(stats));

                        // env pressure on genes
                        r->setGenome(e->serialize());

                        qDebug() << "entity evaluated, fitness =" << fitness << "for a mean of" << r->getFitness() << "on" << r->getNbRun() << "run.";
                    } else {
                        r->setFitness(-1);
                        qDebug() << "the entity die during simulation";
                    }
                } else {
                    qDebug() << "the entity wasn't able to stabilize in the given time, or exploded";
                    r->setFitness(-1);
                }

                // Delete the entity !! Very important
                ee->removeEntity(e);
                delete e;
            }


            // and finaly add the result to resultsManager
            results->addResult(r);
        }
    }



    // To simulate a specific entity
    Entity* ExperimentManager::spawnEntity(QVariant genome) {
        delete world;
        world = worldFactory->createWorld(factory, shapesFactory, exp->getWorldDataMap());
        btVector3 position = world->getSpawnPosition();

        // TODO: better Small noize
        if(exp->getSpawnNoise()) {
            position.setX(position.x() + Tools::random(-0.1, 0.1));
            position.setY(position.y() + Tools::random(-0.1, 0.1));
            position.setZ(position.z() + Tools::random(-0.1, 0.1));
        }


        Entity* e = CreatureFactory::createEntity(genome, shapesFactory, position);
        if(e == NULL) {
            qDebug() << "Entity genome corrupted tralala !";
            return GenericFamily::createVirginEntity(shapesFactory, 1, position);
        }
        e->setup();
        ee->addEntity(e);

        this->bindEntity(e);
        this->loadFunctions();

        return e;
    }

    bool ExperimentManager::stabilizeEntity(Entity* e, Result* r) {
        // Outputs from brain
        e->getShape()->getRoot()->setOutputsFrom(fromNormal); // Brain
        this->engineStep();

        QScriptValue valid = this->validityFunc.call();
        if(!valid.toBool()) {
            qDebug() << "user validity check fail";
            return false;
        }

        // Get the specific velocity value
        Statistic* s = e->getStatisticByName("rootAbsVelocity");

        int stableCpt = 0;
        int neededStableCpt = 60;

        // Not stable at the moment
        bool stable = false;

        for(int i = 0; i < exp->getTimeToWaitForStability() && exp->getOnlyIfEntityIsStable(); i++) {

            if(s->getValue() == 0.) {
                stableCpt++;
            } else {
                stableCpt = 0;
            }

            if(stableCpt > neededStableCpt) {
                stable = true;
                r->setStableAt(e->getAge());
                break;
            }

            this->engineStep();

            if(!e->isAlive() && exp->getStopIfEntityIsNotInOnePiece()) {
                qDebug() << "the entity exploded during stability time";
                return false;
            }
        }

        foreach(Statistic* stat, e->getStatisticsStorage()->getStatistics()) {
            stat->resetAll();
        }

        return stable;
    }

    bool ExperimentManager::simulateEntity(Entity* e) {

        e->setAge(0);
        e->getShape()->getRoot()->setOutputsFrom(fromBrain); // From brain

        for(int i = 0; i < exp->getDuration() || exp->getDuration() == -1; i++) {
            this->engineStep();
            if(!e->isAlive() && exp->getStopIfEntityIsNotInOnePiece()) {
                qDebug() << "entity exploded at age " << e->getAge();
                return false;
            }

            QScriptValue died = dieFunc.call();
            if(died.toBool()) {
                qDebug() << "creature die (user function)";
                return false;
            }

            QScriptValue endV = endFunc.call(QScriptValue(), QScriptValueList() << i);
            if(endV.toBool()) {
                qDebug() << "end of simulation (user triggered)";
                return true;
            }
        }
        return true;
    }

    btScalar ExperimentManager::evaluateEntity(Entity*) {
        // Call to the fitness function
        QScriptValue fitness = fitnessFunc.call();
        return fitness.toNumber();
    }

    void ExperimentManager::engineStep() {
        foreach(Engine* e, engines) {
            e->beforeStep();
        }

        foreach(Engine* e, engines) {
            e->step();
        }

        foreach(Engine* e, engines) {
            e->afterStep();
        }
    }

    /**
      * To set the new generation of population
      */
    void ExperimentManager::setActivePopulation(QList<Result*> newPop) {
        if(this->activePop.size() != newPop.size() && this->activePop.size() != 0)
            qDebug() << "Population size changed ! not a good sign";

        // Delete the old population
        while(!activePop.isEmpty()) {
            Result* r = activePop.takeFirst();
            delete r;
        }

        this->activePop = newPop;
    }
}
