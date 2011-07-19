#include "ressourcesmanager.h"
#include "jsonfile.h"
#include "dbrecord.h"
#include <QDebug>

namespace GeneLabCore {

    RessourcesManager::RessourcesManager(DataBase db, QDir ressourceDir, QObject *parent) :
        QObject(parent)
    {
        this->db = db;
        this->directory = ressourceDir;
    }


    void RessourcesManager::reloadDb() {

        qDebug() << "reload db !";

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
    }

    void RessourcesManager::getAllCreatures() {
        //http://www.genecraft-project.com/db/genecraft/_design/creature/_view/all?stale=ok&include_docs=true
        DbRecord * listDb = new DbRecord(db, "_design/creature/_view/all?stale=ok&include_docs=true");
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
        if(dataMap.contains("author") && dataMap.contains("id") && dataMap.contains("duration")) {
            this->experiments.append(dataw);
            // Take the inside world
            if(dataMap.contains("world")) {
                QVariantMap worldMap = dataMap["world"].toMap();
                DataWrapper dataWorld = {worldMap, NULL};
                worlds.append(dataWorld);
            }

            return;
        }

        // if it's a result
        if(dataMap.contains("type") && dataMap["type"].toString() == "result") {
            dataMap = dataMap["genome"].toMap();
        }

        // Creature ?
        if(dataMap.contains("body") && dataMap.contains("brain") && dataMap.contains("origins")) {
            creatures.append(dataw);
            return;
        }

        // World ?
        if(dataMap.contains("type") && dataMap["type"].toString() == "world") {
            worlds.append(dataw);
            return;
        }
    }
}
