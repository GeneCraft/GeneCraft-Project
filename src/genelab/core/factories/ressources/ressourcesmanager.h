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

        QList<QVariant> getWorlds();
        QList<QVariant> getCreatures();
        QList<QVariant> getExperiments();

    signals:

    public slots:

    };
}
#endif // RESSOURCESMANAGER_H
