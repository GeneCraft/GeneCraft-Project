#include "experimentmanager.h"
#include "statistics/statisticsprovider.h"
#include "statistics/statisticsstorage.h"

#include <QDir>
#include "ressources/jsonfile.h"

#include "families/spiderfamily.h"
#include "families/snakefamily.h"
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
        qDebug() << "HUM";
        this->exp = new Experiment(Ressource::load(expData));

        this->load(workerData);
    }


    //protected
    void ExperimentManager::load(QVariant workerData) {
        db.dbName = "/db/genecraft/";
        db.port = 80;
        db.url = "http://www.genecraft-project.org";

        QVariantMap workerMap = workerData.toMap();
        this->online          = workerMap["online"].toBool();
        this->maxGen          = workerMap["maxGen"].toInt();
        this->popSize         = workerMap["popSize"].toInt();
        this->workerName      = workerMap["name"].toString();

        this->bestResultsStored   = workerMap["nbBestResults"].toInt();
        this->randomResultsStored = workerMap["nbRandomResults"].toInt();

        QVariantMap selectionMap   = workerMap["selection"].toMap();
        this->probFromBestsPop     = selectionMap["bestPop"].toDouble();
        this->probFromBestsResult  = selectionMap["bestResult"].toDouble();
        this->probFromRandomPop    = selectionMap["randomPop"].toDouble();
        this->probFromRandomResult = selectionMap["randomResult"].toDouble();
        this->probFromRandomNew    = selectionMap["randomNew"].toDouble();

        // Normalisation of probability
        float sumProb = probFromBestsPop + probFromBestsResult + probFromRandomNew
                        + probFromRandomPop + probFromRandomResult;

        this->probFromBestsPop     /= sumProb;
        this->probFromBestsResult  /= sumProb;
        this->probFromRandomNew    /= sumProb;
        this->probFromRandomPop    /= sumProb;
        this->probFromRandomResult /= sumProb;

        // default -> "results"
        this->resultsDirectory = QDir(exp->getId()+"/"+workerMap["resultsDir"].toString());
        if(!this->resultsDirectory.exists()) {
            this->resultsDirectory.mkpath(".");
        }

        lastLoadedId = "";
        lastModifiedResultLoaded = QDateTime();
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
        mutations       = exp->getMutationsManager();
        online = false;
        this->bestResultsStored = 100;
        this->randomResultsStored = 100;
        this->popSize = 10;
        this->maxGen = 10;
        this->probFromBestsPop     = 0.1;
        this->probFromBestsResult  = 0.1;
        this->probFromRandomNew    = 0.1;
        this->probFromRandomPop    = 0.1;
        this->probFromRandomResult = 0.1;

        // The world to experiment inside
        world = worldFactory->createWorld(factory, shapesFactory, worldFactory->createSimpleWorld());

        // Nb gen to compute
        int nbGen = this->maxGen;

        int nbLoaded;
        // from db (online experience)
        if(online) {
            nbLoaded = this->retrieveResults();
            qDebug() << "loaded" << nbLoaded << "results from db.";
        } else { // of offline from file
            // Load result from files
            nbLoaded = this->loadResults();
            qDebug() << "loaded" << nbLoaded << "results from file.";
        }

        // No results so far
        if(nbLoaded == 0) {
            // New boostrap population
            this->genRandomPop();
            qDebug() << "generated" << this->popSize << "random new entities";
        } else {
            // New population from results
            this->genNewPop();
            qDebug() << "generated" << this->popSize << "mutated entities from results";
        }

        // For each generations
        while(nbGen > 0 || nbGen == -1) {
            qDebug() << nbGen;
            qDebug() << "------ GENERATION" << this->maxGen - nbGen << "-------";
            nbGen--;

            // Evaluation of population
            qDebug() << "Evaluation of population";
            evalPop();


            // Broadcast result to community
            if(online) {
                qDebug() << "Sending results to community";
                broadcastResults();
                retrieveNewResults();
            } else {
                // Saving results to file
                qDebug() << "Saving results";
                save();
                loadNewResults();
            }

            // Generate new population
            qDebug() << "Generation of a new population";
            genNewPop();
            qDebug() << "generated" << this->popSize << "mutated entities from active population";
        }

    }

    /**
      * To load results from file system
      */
    // TODO : Use Bulk documents
    int ExperimentManager::loadResults() {
        qDebug() << "loading results";
        QDir results = this->resultsDirectory;
        int cptLoaded = 0;
        foreach(QString f, results.entryList(QDir::NoDotAndDotDot
                                             | QDir::Files
                                             | QDir::Readable,
                                             QDir::Time
                                             | QDir::Reversed)) {
            qDebug() << f;
            QFile realFile(results.absoluteFilePath(f));
            QFileInfo fileInfo(realFile);
            if(!realFile.exists()) {
                continue;
            }

            this->lastModifiedResultLoaded
                    = qMax(lastModifiedResultLoaded, fileInfo.lastModified());

            JsonFile* file = new JsonFile(results.absoluteFilePath(f));
            QVariant result = file->load();
            bool valid = false;
            Result* r = Result::loadResult(result, valid);
            r->setRessource(file);
            if(valid) {
                qDebug() << "valid result from " << f;
                qDebug() << r->getDate();
                this->addResult(r);
                cptLoaded++;
            } else {
                qDebug() << "invalid file format" << f;
            }

            delete r;

        }

        this->resultNameCpt = cptLoaded;
        qDebug() << cptLoaded;

        return cptLoaded;
    }

    // TODO : Use Bulk documents
    void ExperimentManager::loadNewResults() {
        QDir results = this->resultsDirectory;
        QDateTime newLastModified = lastModifiedResultLoaded;
        foreach(QString f, results.entryList(QDir::NoDotAndDotDot
                                             | QDir::Files
                                             | QDir::Readable,
                                             QDir::Time)) {
            QFile realFile(results.absoluteFilePath(f));
            QFileInfo fileInfo(realFile);
            if(!realFile.exists()) {
                continue;
            }

            if(this->lastModifiedResultLoaded < fileInfo.lastModified()) {
                qDebug() << "new result : " << f;
                newLastModified = fileInfo.lastModified();
            } else {
                break;
            }

            JsonFile* file = new JsonFile(results.absoluteFilePath(f));
            QVariant result = file->load();
            bool valid = false;
            Result* r = Result::loadResult(result, valid);
            r->setRessource(file);
            if(valid) {
                qDebug() << "valid result from " << f;
                qDebug() << r->getDate();
                this->addResult(r);
            } else {
                qDebug() << "invalid file format" << f;
            }

            delete r;

        }
        this->lastModifiedResultLoaded = newLastModified;
    }

    /**
      * To load results from online database
      */
    int ExperimentManager::retrieveResults() {
        int cptLoaded = 0;
        QString id = "_design/results/_view/all?group=true&group_level=2&startkey=[\""+
                     exp->getId() +"\",\"a\"]&endkey=[\""+
                     exp->getId() +"\",0]&limit="+
                     QString::number(qMax(this->randomResultsStored, this->bestResultsStored))
                     +"&descending=true";
        qDebug() << id;
        DbRecord* r = new DbRecord(db, id);
        QVariant data = r->load();
        delete r;
        QVariantMap results = data.toMap();
        QVariantList rows = results["rows"].toList();
        foreach(QVariant row, rows) {
            bool valid = false;
            QString id = row.toMap()["value"].toList()[4].toString();
            if(id > lastLoadedId) {
                lastLoadedId = id;
            }
            Ressource* re = new DbRecord(db, id);
            QVariant genome = re->load();
            Result* r = Result::loadResult(genome, valid);
            r->setRessource(re);
            if(valid) {
                qDebug() << "valid result from " << id;
                qDebug() << r->getDate() << r->getFitness() << r->getWorker();
                this->addResult(r);
                cptLoaded++;
            } else {
                qDebug() << "invalid file format";
            }

            delete r;
        }
        return cptLoaded;
    }

    void ExperimentManager::retrieveNewResults() {
        QString id = "_design/results/_view/all?group=true&group_level=2&startkey=[\""+
                     exp->getId() +"\",\"a\"]&endkey=[\""+
                     exp->getId() +"\",0]&limit="+
                     QString::number(qMax(this->randomResultsStored, this->bestResultsStored))
                     +"&descending=true";
        qDebug() << id;
        DbRecord* r = new DbRecord(db, id);
        QVariant data = r->load();
        delete r;
        QVariantMap results = data.toMap();
        QVariantList rows = results["rows"].toList();
        QString newLastLoadedId = lastLoadedId;
        foreach(QVariant row, rows) {
            bool valid = false;
            QString id = row.toMap()["value"].toList()[4].toString();

            if(id <= lastLoadedId) {
                continue;
            }

            if(id > newLastLoadedId) {
                newLastLoadedId = id;
            }

            Ressource* re = new DbRecord(db, id);
            QVariant genome = re->load();
            Result* r = Result::loadResult(genome, valid);
            r->setRessource(re);
            if(valid) {
                qDebug() << "valid result from ";
                qDebug() << r->getDate();
                this->addResult(r);
            } else {
                qDebug() << "invalid file format";
            }

            delete r;
        }

        lastLoadedId = newLastLoadedId;
    }

    /**
      * To create a boodstrap pop
      */
    void ExperimentManager::genRandomPop() {
        // The new random population
        QList<Result*> newPop;


        // Creating N new spider
        for(int i = 0; i < this->popSize; i++) {
            newPop.append(new Result(exp->getId(), -1, this->randomNewEntity(), this->workerName));
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
            QString familyName = seedInfo["familyName"].toString();
            // The spider ! Scary !
            if(familyName == "spider") {
                // New entity
                SpiderFamily* family = new SpiderFamily();
                btVector3 position = world->getSpawnPosition();
                Entity* e = family->createEntity(shapesFactory, position);
                // Setup to be able to serialize
                e->setup();
                // Serialisation
                QVariant genome = e->serialize();
                delete e;
                return genome;
            }
        }
        return QVariant();
    }

    // To sort result, descending
    bool myLessThan( const Result *a, const Result *b )
    {
       return !((*a) < (*b));
    }

    /**
      * To generate a new population from last population
      */
    void ExperimentManager::genNewPop() {
        // Sorting best results and active pop if needed
        if(this->probFromBestsResult > 0.0f)
            qSort(bestResults.begin(), bestResults.end(), myLessThan);
        if(this->probFromBestsPop > 0.0f)
            qSort(activePop.begin(), activePop.end(), myLessThan);

        QList<Result*> newActivePop;

        // For probFromBestsResult part
        int max = this->bestResults.size();
        if(max)
        for(int i = 0; i < this->popSize*this->probFromBestsResult; i++) {
            // No bests results enough?
            if(i >= max)
                break;

            // Best 'i one
            Result* r = bestResults.at(i);

            // Mutation of best one
            newActivePop.append(new Result(this->exp->getId(), -1,
                                           mutations->mutateEntity(r->getGenome()), this->workerName));
            qDebug() << "loading mutation of best results with fitness " << r->getFitness();
        }

        // For probFromRandomResults part
        max = randomResults.size();
        if(max)
        for(int i = 0; i < this->popSize*this->probFromRandomResult; i++) {
            // random new from results
            int id = qrand()%max;
            Result* r = randomResults.at(id);
            QVariant genome = r->getGenome();

            // Mutation
            QVariant newGenome = mutations->mutateEntity(genome);

            // Adding to the active population
            newActivePop.append(new Result(exp->getId(), -1, newGenome, workerName));
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
            newActivePop.append( new Result(this->exp->getId(), -1,
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

            // Adding to the active population
            newActivePop.append(new Result(exp->getId(), -1, newGenome, workerName));
            qDebug() << "loading mutation of activePop with fitness " << r->getFitness();
        }

        //Remaining random new
        int needed = this->popSize - newActivePop.length();
        for(int i = 0; i < needed; i++) {
            QVariant newGenome = this->randomNewEntity();
            newActivePop.append(new Result(exp->getId(), -1, newGenome, workerName));
            qDebug() << "new random genome !";
        }

        this->setActivePopulation(newActivePop);
    }

    /**
      * To evaluate the actual population, generating results
      */
    void ExperimentManager::evalPop() {
        foreach(Result* r, this->activePop) {
            Entity *e = this->spawnEntity(r->getGenome());
            bool stable, simulated;
            float fitness;
            stable = this->stabilizeEntity(e);

            if(stable)
                simulated = this->simulateEntity(e);

            if(stable && simulated) {
                fitness = this->evaluateEntity(e);
                r->setFitness(fitness);
                qDebug() << "entity evaluated, fitness =" << fitness;
            } else {
                qDebug() << "corrupted entity";
                r->setFitness(-1);
            }

            // Delete the entity !! Very important
            ee->removeEntity(e);
            delete e;
        }
    }

    /**
      * To save the actual progression of the experiment
      */
    void ExperimentManager::save() {
        foreach(Result* r, activePop) {
            if(r->getFitness() > 0.0) {

                if(r->getRessource() != NULL)
                    continue;

                QString filename = this->workerName + QString::number(resultNameCpt++);
                r->save(new JsonFile(this->getResultsDir().absoluteFilePath(filename)));
                this->addResult(r);
            }
        }
    }

    /**
      * To broadcast result to online database
      */
    void ExperimentManager::broadcastResults() {
        // Neede to sort
        qSort(bestResults.begin(), bestResults.end(), myLessThan);

        foreach(Result* result, activePop) {
            if(result->getRessource() != NULL)
                continue;

            result->save(new DbRecord(db, ""));
            this->addResult(result);
            qDebug() << "saved !";
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
        int maxStableTry = 300;
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
        for(int i = 0; i < exp->getDuration(); i++) {
            this->engineStep();
            if(!e->isAlive()) {
                qDebug() << "entity died at age " << e->getAge();
                return false;
            }
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

    /**
      * To add a new result to this experience
      */
    void ExperimentManager::addResult(Result* result) {
        // Best one ?
        if(this->bestResults.size() < this->bestResultsStored
           || (this->bestResultsStored > 0 && result->getFitness() > this->bestResults.last()->getFitness())) {
            this->bestResults.append(new Result(*result));
            while(bestResults.size() > this->bestResultsStored) {
                    qSort(bestResults.begin(), bestResults.end(), myLessThan);
                    Result *r = this->bestResults.takeLast();
                    delete r;
            }
        }

        // Random one ?
        this->randomResults.append(new Result(*result));
        while(this->randomResults.size() > this->randomResultsStored) {
            int at = qrand()%randomResults.size();
            Result *r = this->randomResults.takeAt(at);
            delete r;
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
