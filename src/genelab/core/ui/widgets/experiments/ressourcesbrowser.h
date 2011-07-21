#ifndef RESSOURCESBROWSER_H
#define RESSOURCESBROWSER_H

#include <QWidget>
#include "genelabcoreclasses.h"
#include "factories/ressources/ressourcesmanager.h"
#include "ressources/dbrecord.h"

namespace Ui {
    class RessourcesBrowser;
}

class RessourcesBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit RessourcesBrowser(QWidget *parent = 0);
    ~RessourcesBrowser();

signals:

    void setExperiment(GeneLabCore::Experiment *);
    void addEntity(QVariantMap entityData, GeneLabCore::Ressource *ressource);

public slots:

    void refreshLocalRessources();
    void refreshOnlineRessources();

    void loadLocalExperiment();
    void loadOnlineExperiment();

    void loadLocalEntity();
    void loadOnlineEntity();

    void openExperimentFolder();

    void saveExperiment();
    void saveEntity();


private:
    Ui::RessourcesBrowser *ui;

    GeneLabCore::RessourcesManager *localRessourceManager;
    GeneLabCore::RessourcesManager *onlineRessourceManager;
    GeneLabCore::DataBase database;

private slots:
    void on_pbShareExp_clicked();
    void on_pushButton_clicked();
};

#endif // RESSOURCESBROWSER_H
