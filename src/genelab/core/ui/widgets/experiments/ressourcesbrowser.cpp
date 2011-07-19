#include "ressourcesbrowser.h"
#include "ui_ressourcesbrowser.h"

#include "ressourcesItems.h"
#include "experiment/experiment.h"
#include "tools.h"
#include "creaturefactory.h"

using namespace GeneLabCore;

RessourcesBrowser::RessourcesBrowser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RessourcesBrowser)
{
    ui->setupUi(this);

    DataBase database;
    database.dbName = "/db/genecraft/";
    database.url = "http://www.genecraft-project.org";
    database.port = 80;

    localRessourceManager = new RessourcesManager(database,QDir("ressources"));
    onlineRessourceManager = new RessourcesManager(database,QDir("ressources"));

    // experiments
    connect(ui->pbRefreshLocalExp,SIGNAL(clicked()),this,SLOT(refreshLocalRessources()));
    connect(ui->pbRefreshOnlineExp,SIGNAL(clicked()),this,SLOT(refreshOnlineRessources()));
    connect(ui->pbLoadLocalExp,SIGNAL(clicked()),this,SLOT(loadLocalExperiment()));
    connect(ui->pbLoadOnlineExp,SIGNAL(clicked()),this,SLOT(loadOnlineExperiment()));

    // worlds


    // entities
    connect(ui->pbRefreshLocalEntity,SIGNAL(clicked()),this,SLOT(refreshLocalRessources()));
    connect(ui->pbRefreshOnlineEntity,SIGNAL(clicked()),this,SLOT(refreshOnlineRessources()));
    connect(ui->pbLoadLocalEntity,SIGNAL(clicked()),this,SLOT(loadLocalEntity()));
    connect(ui->pbLoadOnlineEntity,SIGNAL(clicked()),this,SLOT(loadOnlineEntity()));

    refreshLocalRessources();
}

RessourcesBrowser::~RessourcesBrowser()
{
    delete ui;
}

void RessourcesBrowser::refreshLocalRessources() {
    localRessourceManager->reloadDir();

    // clear lists
    Tools::clearTreeWidget(this->ui->twLocalExperiments);
    Tools::clearTreeWidget(this->ui->twLocalEntities);

    // fill lists
    foreach(DataWrapper exp, localRessourceManager->getExperiments())
        ui->twLocalExperiments->insertTopLevelItem(0,new ExperimentTreeWidgetItem(exp));

    foreach(DataWrapper entity, localRessourceManager->getCreatures())
        ui->twLocalEntities->insertTopLevelItem(0,new EntityTreeWidgetItem(entity));
}

void RessourcesBrowser::refreshOnlineRessources() {
    this->ui->lblDb->setText("Loading from database...");
    onlineRessourceManager->reloadDb();
    this->ui->lblDb->setText("Ressources loaded from database...");

    // clear lists
    Tools::clearTreeWidget(this->ui->twOnlineExperiments);
    Tools::clearTreeWidget(this->ui->twOnlineEntities);

    // fill lists
    foreach(DataWrapper exp, onlineRessourceManager->getExperiments())
        ui->twOnlineExperiments->insertTopLevelItem(0,new ExperimentTreeWidgetItem(exp));

    foreach(DataWrapper entity, onlineRessourceManager->getCreatures())
        ui->twOnlineEntities->insertTopLevelItem(0,new EntityTreeWidgetItem(entity));
}

void RessourcesBrowser::loadLocalExperiment() {

    if(ui->twLocalExperiments->currentItem()) {
        ExperimentTreeWidgetItem *expTWI = (ExperimentTreeWidgetItem *) ui->twLocalExperiments->currentItem();
        emit setExperiment(new Experiment(expTWI->dataw.data));
    }
}

void RessourcesBrowser::loadOnlineExperiment() {
    ExperimentTreeWidgetItem *expTWI = (ExperimentTreeWidgetItem *) ui->twOnlineExperiments->currentItem();
    emit setExperiment(new Experiment(expTWI->dataw.data));
}

void RessourcesBrowser::loadLocalEntity() {
    EntityTreeWidgetItem *entityTWI = (EntityTreeWidgetItem *) ui->twLocalEntities->currentItem();
    emit addEntity(entityTWI->dataw.data, NULL /* entityTWI->dataw.r */);
}

void RessourcesBrowser::loadOnlineEntity() {
    EntityTreeWidgetItem *entityTWI = (EntityTreeWidgetItem *) ui->twOnlineEntities->currentItem();
    emit addEntity(entityTWI->dataw.data, NULL /* entityTWI->dataw.r */);
}

