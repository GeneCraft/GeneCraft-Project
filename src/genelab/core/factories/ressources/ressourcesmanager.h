#ifndef RESSOURCESMANAGER_H
#define RESSOURCESMANAGER_H

#include <QObject>
#include <QDir>
#include "dbrecord.h"

namespace GeneLabCore {

    class RessourcesManager : public QObject
    {
        Q_OBJECT
    public:
        explicit RessourcesManager(DataBase db, QDir ressourceDir, QObject *parent = 0);

        void reloadDb();
        void reloadDir();

        QList<QVariantMap> getWorlds();
        QList<QVariantMap> getCreatures();
        QList<QVariantMap> getExperiments();

    signals:

    public slots:
    protected:
        QDir directory;
        DataBase db;
        QList<QVariantMap> worlds;
        QList<QVariantMap> creatures;
        QList<QVariantMap> experiments;

        void getAllWorld();
        void getAllCreatures();
        void getAllExperiments();

        void examine(QVariant data);


    };
}
#endif // RESSOURCESMANAGER_H
