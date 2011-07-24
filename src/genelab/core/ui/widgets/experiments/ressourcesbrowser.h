#ifndef RESSOURCESBROWSER_H
#define RESSOURCESBROWSER_H

#include <QWidget>
#include "genelabcoreclasses.h"
#include "factories/ressources/ressourcesmanager.h"
#include "ressources/dbrecord.h"

namespace Ui {
    class RessourcesBrowser;
}

namespace GeneLabCore {

class RessourcesBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit RessourcesBrowser(QWidget *parent = 0);
    ~RessourcesBrowser();

    void connectToInspectorInputManager(GeneLabCore::InspectorsInputManager * iim);

signals:

    void sLoadExperiment(Experiment *);
    void sLoadWorld(QVariantMap worldData);
    void sLoadEntity(QVariantMap genomeData, Ressource *ressource);

    // TODO replace by loadEntity
    //void addEntity(QVariantMap entityData, GeneLabCore::Ressource *ressource);

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

    // worls
    void loadLocalWorld();
    void loadOnlineWorld();
    void saveWorld();
    void shareWorld();
    void deleteLocalWorld();

    // entities
    void loadLocalEntity();
    void loadOnlineEntity();
    void saveEntity();
    void shareEntity();
    void deleteLocalEntity();


private:

    Ui::RessourcesBrowser *ui;

    GeneLabCore::RessourcesManager *localRessourceManager;
    GeneLabCore::RessourcesManager *onlineRessourceManager;
    GeneLabCore::DataBase database;


};

}
#endif // RESSOURCESBROWSER_H
