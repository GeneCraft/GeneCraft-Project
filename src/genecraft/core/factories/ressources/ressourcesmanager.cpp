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

#include "ressourcesmanager.h"
#include "jsonfile.h"
#include "dbrecord.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

namespace GeneCraftCore {

    RessourcesManager::RessourcesManager(DataBase db, QDir ressourceDir, QObject *parent) :
        QObject(parent)
    {
        this->db = db;
        this->directory = ressourceDir;
    }

    void RessourcesManager::reloadDb() {
        // clear list
        experiments.clear();
        worlds.clear();
        creatures.clear();

        // Get all world
        getAllWorld();
        getAllCreatures();
        getAllExperiments();
    }

    void RessourcesManager::getAllWorld() {
        DbRecord * listDb = new DbRecord(db, "_design/worlds/_view/all");
        QJsonObject worlds = listDb->load();
        delete listDb;

        QJsonArray worldsList = worlds["rows"].toArray();
        foreach(QJsonValue world, worldsList) {
            DataWrapper dataw = {world.toObject()["value"].toObject(), NULL};
            this->examine(dataw);
        }
    }

    void RessourcesManager::getAllCreatures() {
        //http://www.genecraft-project.com/db/genecraft/_design/creature/_view/all?include_docs=true
        DbRecord * listDb = new DbRecord(db, "_design/creature/_view/all?include_docs=true");
        QJsonObject creatures = listDb->load();
        delete listDb;

        QJsonArray creaturesList = creatures["rows"].toArray();
        foreach(QJsonValue creature, creaturesList) {
            DataWrapper dataw = {creature.toObject()["doc"].toObject(), NULL};
            this->examine(dataw);
        }
    }

    void RessourcesManager::getAllExperiments() {
        DbRecord * listDb = new DbRecord(db, "_design/experiments/_view/all");
        QJsonObject experiments = listDb->load();
        delete listDb;

        QJsonArray experimentsList = experiments["rows"].toArray();
        foreach(QJsonValue experiment, experimentsList) {
            DataWrapper dataw = {experiment.toObject()["value"].toObject(), NULL};
            this->examine(dataw);
        }
    }

    void RessourcesManager::reloadDir() {

        // clear list
        experiments.clear();
        worlds.clear();
        creatures.clear();

        // load
        foreach(QString filename, directory.entryList(QDir::NoDotAndDotDot
                                             | QDir::Files
                                             | QDir::Readable,
                                             QDir::Time
                                             | QDir::Reversed)) {
            JsonFile* f = new JsonFile(directory.absoluteFilePath(filename));

            DataWrapper dataw = {f->load(), f};
            this->examine(dataw);
        }
    }

    QList<DataWrapper> RessourcesManager::getWorlds() {
        return this->worlds;
    }

    QList<DataWrapper> RessourcesManager::getCreatures() {
        return this->creatures;
    }

    QList<DataWrapper> RessourcesManager::getExperiments() {
        return this->experiments;
    }

    void RessourcesManager::examine(DataWrapper dataw) {
        QJsonObject dataMap = dataw.data;

        // Experience ?
        if(dataMap.contains("author") && dataMap.contains("duration")) {
            this->experiments.append(dataw);

            // Take the inside world
//            if(dataMap.contains("world")) {
//                QJsonObject worldMap = dataMap["world"].toObject();
//                DataWrapper dataWorld = {worldMap, NULL};

//                // no add two times the same world
//                foreach(DataWrapper dw, worlds)
//                    if(dataWorld.data == dw.data)
//                        return;

//                worlds.append(dataWorld);
//            }

            return;
        }

        // World ?
        if(dataMap.contains("biome") && dataMap.contains("scene")) {

            // no add two times the same world
            foreach(DataWrapper dw, worlds)
                if(dataw.data == dw.data)
                    return;

            worlds.append(dataw);
            return;
        }

        // if it's a result, convert to genome...
        if(dataMap.contains("type") && dataMap["type"].toString() == "result") {
            dataMap = dataMap["genome"].toObject();
        }

        // Creature ?
        if(dataMap.contains("body") && dataMap.contains("brain") && dataMap.contains("origins")) {
            creatures.append(dataw);
            return;
        }
    }
}
