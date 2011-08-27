#include "ressourcesmanager.h"
#include "jsonfile.h"
#include "dbrecord.h"
#include <QDebug>

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
        QVariant worlds = listDb->load();
        delete listDb;

        QVariantMap worldsMap = worlds.toMap();
        QVariantList worldsList = worldsMap["rows"].toList();
        foreach(QVariant world, worldsList) {
            DataWrapper dataw = {world.toMap()["value"].toMap(), NULL};
            this->examine(dataw);
        }
    }

    void RessourcesManager::getAllCreatures() {
        //http://www.genecraft-project.com/db/genecraft/_design/creature/_view/all?include_docs=true
        DbRecord * listDb = new DbRecord(db, "_design/creature/_view/all?include_docs=true");
        QVariant creatures = listDb->load();
        delete listDb;

        QVariantMap creaturesMap = creatures.toMap();
        QVariantList creaturesList = creaturesMap["rows"].toList();
        foreach(QVariant creature, creaturesList) {
            DataWrapper dataw = {creature.toMap()["doc"].toMap(), NULL};
            this->examine(dataw);
        }
    }

    void RessourcesManager::getAllExperiments() {
        DbRecord * listDb = new DbRecord(db, "_design/experiments/_view/all");
        QVariant experiments = listDb->load();
        delete listDb;

        QVariantMap experimentsMap = experiments.toMap();
        QVariantList experimentsList = experimentsMap["rows"].toList();
        foreach(QVariant experiment, experimentsList) {
            DataWrapper dataw = {experiment.toMap()["value"].toMap(), NULL};
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

            DataWrapper dataw = {f->load().toMap(), f};
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
        QVariantMap dataMap = dataw.data;

        // Experience ?
        if(dataMap.contains("author") && dataMap.contains("duration")) {
            this->experiments.append(dataw);

            // Take the inside world
//            if(dataMap.contains("world")) {
//                QVariantMap worldMap = dataMap["world"].toMap();
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
            dataMap = dataMap["genome"].toMap();
        }

        // Creature ?
        if(dataMap.contains("body") && dataMap.contains("brain") && dataMap.contains("origins")) {
            creatures.append(dataw);
            return;
        }
    }
}
