#include "ressourcesmanager.h"
#include "jsonfile.h"
#include "dbrecord.h"

namespace GeneLabCore {
    RessourcesManager::RessourcesManager(DataBase db, QDir ressourceDir, QObject *parent) :
        QObject(parent)
    {
        this->db = db;
        this->directory = ressourceDir;
    }


    void RessourcesManager::reloadDb() {
        // Get all world
        getAllWorld();
        getAllCreatures();
        getAllExperiments();

    }


    void RessourcesManager::getAllWorld() {
    }

    void RessourcesManager::getAllCreatures() {
    }

    void RessourcesManager::getAllExperiments() {
    }

    void RessourcesManager::reloadDir() {
        foreach(QString filename, directory.entryList(QDir::NoDotAndDotDot
                                             | QDir::Files
                                             | QDir::Readable,
                                             QDir::Time
                                             | QDir::Reversed)) {
            JsonFile* f = new JsonFile(directory.absoluteFilePath(filename));
            QVariant data = f->load();
            this->examine(data);
        }
    }

    QList<QVariantMap> RessourcesManager::getWorlds() {
        return this->worlds;
    }

    QList<QVariantMap> RessourcesManager::getCreatures() {
        return this->creatures;
    }

    QList<QVariantMap> RessourcesManager::getExperiments() {
        return this->experiments;
    }

    void RessourcesManager::examine(QVariant data) {
        QVariantMap dataMap = data.toMap();
        // Experience ?
        if(dataMap.contains("author") && dataMap.contains("id") && dataMap.contains("duration")) {
            this->experiments.append(dataMap);
            // Take the inside world
            if(dataMap.contains("world")) {
                QVariantMap worldMap = dataMap["world"].toMap();
                worlds.append(worldMap);
            }

            return;
        }

        // if it's a result
        if(dataMap.contains("type") && dataMap["type"].toString() == "result") {
            dataMap = dataMap["genome"].toMap();
        }

        // Creature ?
        if(dataMap.contains("body") && dataMap.contains("brain") && dataMap.contains("origins")) {
            creatures.append(dataMap);
            return;
        }

        // World ?
        if(dataMap.contains("type") && dataMap["type"].toString() == "world") {
            worlds.append(dataMap);
            return;
        }
    }
}
