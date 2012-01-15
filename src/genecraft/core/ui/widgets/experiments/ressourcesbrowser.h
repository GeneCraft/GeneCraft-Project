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

#ifndef RESSOURCESBROWSER_H
#define RESSOURCESBROWSER_H

#include <QWidget>
#include "genecraftcoreclasses.h"
#include "factories/ressources/ressourcesmanager.h"
#include "ressources/dbrecord.h"

namespace Ui {
    class RessourcesBrowser;
}

namespace GeneCraftCore {

class RessourcesBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit RessourcesBrowser(QWidget *parent = 0);
    ~RessourcesBrowser();

    void connectToInspectorInputManager(GeneCraftCore::InspectorsInputManager * iim);

signals:

    void sLoadExperiment(Experiment *);
    void sLoadWorld(QVariantMap worldData);
    void sLoadEntity(QVariantMap genomeData, Ressource *ressource);

public slots:

    void refreshLocalRessources();
    void refreshOnlineRessources();
    void openInfoDatabase();

    // exp
    void loadLocalExperiment();
    void loadOnlineExperiment();
    void openRessourcesFolder();
    void saveExperiment();
    void shareExperiment();
    void deleteLocalExp();
    void deleteOnlineExp();
    void experimentUpdated(Experiment *experiment);

    // worls
    void loadLocalWorld();
    void loadOnlineWorld();
    void saveWorld();
    void shareWorld();
    void deleteLocalWorld();
    void deleteOnlineWorld();

    // entities
    void loadLocalEntity();
    void loadOnlineEntity();
    void saveEntity();
    void shareEntity();
    void deleteLocalEntity();
    void deleteOnlineEntity();

private:

    Ui::RessourcesBrowser *ui;

    GeneCraftCore::RessourcesManager *localRessourceManager;
    GeneCraftCore::RessourcesManager *onlineRessourceManager;
    GeneCraftCore::DataBase database;


};

}
#endif // RESSOURCESBROWSER_H
