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

#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "result.h"
#include <QList>
#include <QDebug>
#include <QJsonObject>
#include <QDir>
#include "genecraftcoreclasses.h"
#include "bullet/btworld.h"

namespace GeneCraftCore {

    class Experiment
    {
    public:

        Experiment();
        ~Experiment();
        Experiment(QJsonObject data);
        QJsonObject serialize();

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

        QJsonObject getWorldDataMap() { return worldDataMap; }
        void setWorldData(QJsonObject worldDataMap) { this->worldDataMap = worldDataMap; }

        // ----------
        // -- Seed --
        // ----------

        QJsonObject getSeedInfo() { return this->seedInfo; }
        void setSeedInfo(QJsonObject seedInfo) { this->seedInfo = seedInfo; }

        // -----------
        // -- Other --
        // -----------
        bool hasRessource() { return ressource != NULL; }
        Ressource* getRessource() { return ressource; }
        void setRessource(Ressource* ressource) { this->ressource = ressource; }

        int getNbRun() { return this->nbRun; }
        void setNbRun(int n) {this->nbRun = n; }

        bool getSpawnNoise() { return this->spawnNoise; }
        void setSpawnNoise(bool spawnNoise) { this->spawnNoise = spawnNoise; }

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
        QJsonObject worldDataMap;

        // Seed
        QJsonObject seedInfo;

        QString evalFunction;
        QString validityFunction;
        QString endFunction;
        QString dieFunction;

        // Simulations
        int nbRun;
        bool spawnNoise;
    };
}

#endif // EXPERIMENT_H
