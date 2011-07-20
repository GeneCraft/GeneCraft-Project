#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "result.h"
#include <QList>
#include <QDebug>
#include <QVariantMap>
#include <QDir>
#include "genelabcoreclasses.h"
#include "world/btworld.h"

namespace GeneLabCore {

    class Experiment
    {
    public:

        Experiment();
        Experiment(QVariant data);
        QVariant serialize();

        // -----------------
        // -- Information --
        // -----------------

        // Experiment name, or id
        QString getId() { return this->id; }
        void setId(QString id) { this->id = id; }

        // The experience description given by the creator
        QString getDescription() { return this->description; }
        void setDescription(QString description) { this->description = description; }

        // The experience description given by the creator
        QString getAuthor() { return this->author; }
        void setAuthor(QString author) { this->author = author; }

        // The experience comments given by the creator
        QString getComments() { return this->comments; }
        void setComments(QString comments) { this->comments = comments; }

        // The date when the exp was created
        QDateTime getDateOfCreation() { return this->dateOfCreation; }
        void setDateOfCreation(QDateTime dateOfCreation) { this->dateOfCreation = dateOfCreation; }

        // if the experiment is online
        bool isOnline() {return this->online;}
        void setOnline(bool online) {this->online = online;}

        // ----------------
        // -- Simulation --
        // ----------------

        // During time of the simulation in steps
        int getDuration() { return this->duration; }
        void setDuration(int duration) { this->duration = duration; }

        // The time to wait entity's stability (before starting experiment)
        int getTimeToWaitForStability() { return this->timeToWaitForStability; }
        void setTimeToWaitForStability(int timeToWaitForStability) { this->timeToWaitForStability = timeToWaitForStability; }

        // Need stability ?
        bool getOnlyIfEntityIsStable() { return this->onlyIfEntityIsStable; }
        void setOnlyIfEntityIsStable(bool onlyIfEntityIsStable) { this->onlyIfEntityIsStable = onlyIfEntityIsStable; }

        // ...
        bool getStopIfEntityIsNotInOnePiece() { return this->stopIfEntityIsNotInOnePiece; }
        void setStopIfEntityIsNotInOnePiece(bool stopIfEntityIsNotInOnePiece) { this->stopIfEntityIsNotInOnePiece = stopIfEntityIsNotInOnePiece; }

        QString getEndFunction() { return this->endFunction; }
        QString getDieFunction() { return this->dieFunction; }

        void setDieFunction(QString function) { dieFunction = function; }
        void setEndFunction(QString function) { endFunction = function; }

        // ----------------
        // -- Evaluation --
        // ----------------

        QString getEvalFunction() { return this->evalFunction; }
        QString getValidityFunction() { return this->validityFunction; }

        void setValidityFunction(QString function) { validityFunction = function; }
        void setEvalFunction(QString function) { evalFunction = function;  }

        // ---------------
        // -- Mutations --
        // ---------------

        MutationsManager *getMutationsManager() { return mutationsManager; }
        void setMutationsManager(MutationsManager *mutationsManager) { this->mutationsManager = mutationsManager; }

        // -----------
        // -- World --
        // -----------

        QVariantMap getWorldDataMap() { return worldDataMap; }
        void setWorldData(QVariantMap worldDataMap) { this->worldDataMap = worldDataMap; }

        // ----------
        // -- Seed --
        // ----------

        QVariantMap getSeedInfo() { return this->seedInfo; }
        void setSeedInfo(QVariantMap seedInfo) { this->seedInfo = seedInfo; }

        // -----------
        // -- Other --
        // -----------
        bool hasRessource() { return ressource != NULL; }
        Ressource* getRessource() { return ressource; }
        void setRessource(Ressource* ressource) { this->ressource = ressource; }

    protected:

        // Information
        QString id;
        QString description;
        QString author;
        QString comments;
        QDateTime dateOfCreation;

        // Online ?
        bool online;

        // file
        Ressource* ressource;

        // Simulation
        int duration;
        int timeToWaitForStability;
        bool onlyIfEntityIsStable;
        bool stopIfEntityIsNotInOnePiece;

        // Mutations
        MutationsManager *mutationsManager;

        // World
        QVariantMap worldDataMap;

        // Seed
        QVariantMap seedInfo;

        QString evalFunction;
        QString validityFunction;
        QString endFunction;
        QString dieFunction;
    };
}

#endif // EXPERIMENT_H
