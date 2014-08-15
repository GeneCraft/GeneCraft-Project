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

#ifndef RESSOURCESMANAGER_H
#define RESSOURCESMANAGER_H

#include <QObject>
#include <QDir>
#include "dbrecord.h"

namespace GeneCraftCore {

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
