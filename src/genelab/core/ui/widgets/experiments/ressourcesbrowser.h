#ifndef RESSOURCESBROWSER_H
#define RESSOURCESBROWSER_H

#include <QWidget>
#include "genelabcoreclasses.h"
#include "factories/ressources/ressourcesmanager.h"

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


private:
    Ui::RessourcesBrowser *ui;

    GeneLabCore::RessourcesManager *localRessourceManager;
    GeneLabCore::RessourcesManager *onlineRessourceManager;
};

#endif // RESSOURCESBROWSER_H
