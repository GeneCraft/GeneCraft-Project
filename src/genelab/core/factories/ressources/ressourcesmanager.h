#ifndef RESSOURCESMANAGER_H
#define RESSOURCESMANAGER_H

#include <QObject>
#include <QDir>
#include "dbrecord.h"

namespace GeneLabCore {

    struct DataWrapper {

        QVariantMap data;
        Ressource *r;
    };


    class RessourcesManager : public QObject
    {
        Q_OBJECT
    public:

        RessourcesManager(DataBase db, QDir ressourceDir, QObject *parent = 0);

        void reloadDb();
        void reloadDir();

        QList<DataWrapper> getWorlds();
        QList<DataWrapper> getCreatures();
        QList<DataWrapper> getExperiments();

    signals:

    public slots:
    protected:
        QDir directory;
        DataBase db;
        QList<DataWrapper> worlds;
        QList<DataWrapper> creatures;
        QList<DataWrapper> experiments;

        void getAllWorld();
        void getAllCreatures();
        void getAllExperiments();

        void examine(DataWrapper dataw);


    };
}
#endif // RESSOURCESMANAGER_H
