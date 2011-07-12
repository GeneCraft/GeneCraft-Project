#include "experimentmanager.h"
#include "statistics/statisticsprovider.h"
#include "statistics/statisticsstorage.h"

#include <QDir>
#include "ressources/jsonfile.h"

#include "families/spiderfamily.h"
#include "families/genericfamily.h"
#include "entity.h"
#include "entityfamily.h"

#include "btworldfactory.h"
#include "creaturefactory.h"
#include "btshapesfactory.h"

#include "world/btworld.h"
#include "entities/entitiesengine.h"
#include "LinearMath/btVector3.h"

#include "body/treeshape.h"
#include "body/fixation.h"

#include "statistics/statisticsstorage.h"
#include "statistics/statisticsprovider.h"
#include "statistics/fixationstats.h"

#include "ressources/dbrecord.h"

namespace GeneLabCore {

    /**
      * Creating an experiment manager for a given experiment
      */
    ExperimentManager::ExperimentManager(btFactory* factory, Experiment* exp) {
        this->factory = factory;
        this->exp = exp;
        this->broadcast = false;
    }

    /**
      * Creating an experiment manager for a giver experiment data
      */
    ExperimentManager::ExperimentManager(btFactory* factory, QVariant expData) {
        this->factory = factory;
        this->exp = new Experiment(Ressource::load(expData));
        this->broadcast = false;
    }

    /**
      * Experimentation loop
      */
    void ExperimentManager::experiment() {

        // The result name cpt
        this->resultNameCpt = 0;

        // The entity engine
        engines = factory->getEngines();
        ee = (EntitiesEngine*)engines.find("Entities").value();

        // All those cool factory !
        worldFactory    = new btWorldFactory();
        shapesFactory   = new btShapesFactory();
        creatureFactory = new CreatureFactory();
        mutations       = new MutationsManager(QVariant());

        // The world to experiment inside
        world = worldFactory->createWorld(factory, shapesFactory, worldFactory->createSimpleWorld());

        // Nb gen to compute
        int nbGen = exp->getMaxGen();

        // Load result from files
        int nb = this->loadResults();
        qDebug() << "loaded" << nb << "results from file.";

        // Or from db (online experience)
        if(nb == 0) {
            this->retrieveResults();
            qDebug() << "loaded" << nb << "results from db.";
        }

        // No results so far
        if(nb == 0) {
            // New boostrap population
            this->genRandomPop();
            qDebug() << "generated" << exp->getPopSize() << "random new entities";
        } else {
            // New population from results
            this->genNewPopFromResults();
            qDebug() << "generated" << exp->getPopSize() << "mutated entities from results";
        }

        // For each generations
        while(nbGen > 0 || nbGen == -1) {
            qDebug() << nbGen;
            qDebug() << "------ GENERATION" << exp->getMaxGen() - nbGen << "-------";
            nbGen--;

            // Evaluation of population
            qDebug() << "Evaluation of population";
            evalPop();

            // Saving results to file
            qDebug() << "Saving results";
            save();

            // Broadcast result to community
            if(broadcast) {
                qDebug() << "Sending results to community";
                broadcastResults();
            }

            // Generate new population
            qDebug() << "Generation of a new population";
            genNewPop();
            qDebug() << "generated" << this->exp->getPopSize() << "mutated entiteis from active population";
        }

    }

    /**
      * To load results from file system
      */
    int ExperimentManager::loadResults() {
        QDir results = exp->getResultsDir();
        int cptLoaded = 0;
        foreach(QString f, results.entryList(QDir::NoDotAndDotDot
                                             | QDir::Files
                                             | QDir::Readable)) {
            JsonFile* file = new JsonFile(results.absoluteFilePath(f));
            QVariant result = file->load();
            bool valid = false;
            Result r = Result::loadResult(result, valid);
            if(valid) {
                qDebug() << "valid result from " << f;
                qDebug() << r.getDate();
                exp->addResult(r);
                cptLoaded++;
            } else {
                qDebug() << "invalid file format" << f;
            }

        }
        this->resultNameCpt = cptLoaded;
        return cptLoaded;
    }

    /**
      * To load results from online database
      */
    int ExperimentManager::retrieveResults() {

    }

    /**
      * To create a boodstrap pop
      */
    void ExperimentManager::genRandomPop() {
        // The new random population
        QList<Result> newPop;

        // How to create the new entities ?
        QVariantMap seedInfo = exp->getSeedInfo();
        QString type = seedInfo["type"].toString();

        // From a family
        if(type == "family") {
            // Which one ?
            QString familyName = seedInfo["familyName"].toString();
            // The spider ! Scary !
            if(familyName == "spider") {
                // Creating N new spider
                for(int i = 0; i < exp->getPopSize(); i++) {
                    // New entity
                    SpiderFamily* family = new SpiderFamily();
                    btVector3 position = world->getSpawnPosition();
                    Entity* e = family->createEntity(shapesFactory, position);
                    // Setup to be able to serialize
                    e->setup();
                    // Serialisation
                    QVariant genome = e->serialize();
                    Result r(exp->getId(), -1, genome);
                    newPop.append(r);
                    delete e;
                }
            }
        }

        // Adding the population to the experience
        exp->setActivePopulation(newPop);

    }

    /**
      * To generate a new population from last population
      */
    void ExperimentManager::genNewPop() {
        QList<Result> results = exp->getResults();
        QList<Result> activePop = exp->getActivePopulation();

        qSort(results.begin(), results.end(), qGreater<Result>());
        QList<Result> newActivePop;
        int max = activePop.size();

        // For a tenth of the pop size -> the bests one
        for(int i = 0; i < exp->getPopSize()*0.3 + 1; i++) {
            if(i >= max)
                break;
            // Best 'i one
            Result r = results.at(i);

            // Mutation of best one
            r.setGenome(mutations->mutateEntity(r.getGenome()));

            qDebug() << "loading mutation of result with fitness " << r.getFitness();
            newActivePop.append(r);
        }

        // Creating a new population
        int already = newActivePop.size();
        for(int i = 0; i < exp->getPopSize() - already; i++) {
            // random new from results
            int id = qrand()%max;
            Result r = activePop.at(id);
            QVariant genome = r.getGenome();

            // Mutation
            QVariant newGenome = mutations->mutateEntity(genome);

            // Adding to the active population
            newActivePop.append(Result(exp->getId(), -1, newGenome));

            qDebug() << "loading mutation of result with fitness " << r.getFitness();

        }

        this->exp->setActivePopulation(newActivePop);
    }

    /**
      * To generate a new population from existing result
      */
    void ExperimentManager::genNewPopFromResults() {
        QList<Result> results = exp->getResults();
        qSort(results.begin(), results.end(), qGreater<Result>());
        QList<Result> newActivePop;
        int max = results.size();

        // For a tenth of the pop size -> the bests one
        for(int i = 0; i < exp->getPopSize()*0.5 + 1; i++) {
            if(i >= max) {
                qDebug() << "not enough old result to fill the new pop";
                break;
            }

            Result r = results.at(i);
            qDebug() << "loading result with fitness " << r.getFitness();
            newActivePop.append(r);
        }

        // Creating a new population
        int already = newActivePop.size();
        for(int i = 0; i < exp->getPopSize() - already; i++) {
            // random new from results
            int id = qrand()%max;
            Result r = results.at(id);
            QVariant genome = r.getGenome();

            // Mutation
            QVariant newGenome = mutations->mutateEntity(genome);

            // Adding to the active population
            newActivePop.append(Result(exp->getId(), -1, newGenome));

            qDebug() << "creating mutation of result with fitness " << r.getFitness();

        }

        this->exp->setActivePopulation(newActivePop);
    }

    /**
      * To evaluate the actual population, generating results
      */
    void ExperimentManager::evalPop() {
        QList<Result> evaluatedPop;
        foreach(Result r, exp->getActivePopulation()) {
            Entity *e = this->spawnEntity(r.getGenome());
            bool stable, simulated;
            float fitness;
            stable = this->stabilizeEntity(e);

            if(stable)
                simulated = this->simulateEntity(e);

            if(stable && simulated) {
                fitness = this->evaluateEntity(e);
                r.setFitness(fitness);
                qDebug() << "entity evaluated, fitness =" << fitness;
            } else {
                qDebug() << "corrupted entity";
                r.setFitness(-1);
            }
            // Evaluated pop
            evaluatedPop.append(r);

            // Delete the entity !! Very important
            ee->removeEntity(e);
            delete e;
        }
        this->exp->setActivePopulation(evaluatedPop);
    }

    /**
      * To save the actual progression of the experiment
      */
    void ExperimentManager::save() {
        QList<Result> results = exp->getActivePopulation();
        foreach(Result r, results) {
            if(r.getFitness() > 0.0) {
                QString filename = "result" + QString::number(resultNameCpt++);
                r.save(new JsonFile(this->exp->getResultsDir().absoluteFilePath(filename)));
                exp->addResult(r);
            }
        }
    }

    /**
      * To broadcast result to online database
      */
    void ExperimentManager::broadcastResults() {
        QList<Result> results = exp->getResults();
        qSort(results.begin(), results.end(), qGreater<Result>());

        for(int i = 0; i < qMin(10, results.size()); i++) {
            Result result = results.at(i);
            DataBase db;
            db.dbName = "/db/genecraft/";
            db.port = 80;
            db.url = "http://www.genecraft-project.org";

            Ressource * r = new DbRecord(db, "");
            result.save(r);
        }
    }


    // To simulate a specific entity
    Entity* ExperimentManager::spawnEntity(QVariant genome) {
        btVector3 position = world->getSpawnPosition();
        Entity* e = creatureFactory->createEntity(genome, shapesFactory, position);
        e->setup();
        ee->addEntity(e);
        return e;
    }

    bool ExperimentManager::stabilizeEntity(Entity* e) {
        // Outputs from brain
        e->getShape()->getRoot()->setOutputsFrom(1); // Brain
        // 100 engines step
        for(int i = 0; i < 200; i++) {
            this->engineStep();
        }
        // Outputs disables
        e->getShape()->getRoot()->setOutputsFrom(3); // To normal position

        // Get the fixationstat
        StatisticsProvider* stat = e->getStatistics().find("FixationStats").value();
        // Get the specific velocity value
        Statistic* s = e->getStatisticByName("Root relative velocity");

        // The last velocity
        float lastVelocity = s->getValue();
        float EPSILON = 0.00001; // Stability needed
        int stableCpt = 0;
        int maxStableTry = 200;
        int neededStableCpt = 60;

        // Not stable at the moment
        bool stable = false;

        for(int i = 0; i < maxStableTry; i++) {

            if(lastVelocity + EPSILON > s->getValue() &&
               lastVelocity - EPSILON < s->getValue()) {
                stableCpt++;
            } else {
                stableCpt = 0;
            }

            lastVelocity = s->getValue();

            if(stableCpt > neededStableCpt) {
                stable = true;
                qDebug() << "stable at " << i;
                break;
            }

            this->engineStep();
        }

        s->resetAll();
        ((FixationStats*)stat)->resetOrigin();
        e->setAge(0);
        e->getShape()->getRoot()->setOutputsFrom(1); // From brain

        return stable;
    }

    bool ExperimentManager::simulateEntity(Entity* e) {
        for(int i = 0; i < exp->getExpTime(); i++) {
            this->engineStep();
            // Check for entity alive, in one piece or not moving maybe ?
                // return false;
        }
        return true;
    }

    float ExperimentManager::evaluateEntity(Entity* e) {
        Statistic* s = e->getStatisticByName("Root relative velocity");
        return s->getSum();
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
}
