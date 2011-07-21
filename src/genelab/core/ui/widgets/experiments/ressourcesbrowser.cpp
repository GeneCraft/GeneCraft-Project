#include "ressourcesbrowser.h"
#include "ui_ressourcesbrowser.h"

#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>

#include "ressourcesItems.h"
#include "experiment/experiment.h"
#include "tools.h"
#include "creaturefactory.h"
#include "ressources/jsonfile.h"

using namespace GeneLabCore;

RessourcesBrowser::RessourcesBrowser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RessourcesBrowser)
{
    ui->setupUi(this);

    // TODO QSettings
    database;
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
    connect(ui->pbOpenExperimentsFolder,SIGNAL(clicked()),this,SLOT(openExperimentFolder()));
    connect(ui->pbSaveExp,SIGNAL(clicked()),this,SLOT(saveExperiment()));

    // worlds


    // entities
    connect(ui->pbRefreshLocalEntity,SIGNAL(clicked()),this,SLOT(refreshLocalRessources()));
    connect(ui->pbRefreshOnlineEntity,SIGNAL(clicked()),this,SLOT(refreshOnlineRessources()));
    connect(ui->pbLoadLocalEntity,SIGNAL(clicked()),this,SLOT(loadLocalEntity()));
    connect(ui->pbLoadOnlineEntity,SIGNAL(clicked()),this,SLOT(loadOnlineEntity()));
    connect(ui->pbOpenEntitiesFolder,SIGNAL(clicked()),this,SLOT(openExperimentFolder()));
    connect(ui->pbSaveEntity,SIGNAL(clicked()),this,SLOT(saveEntity()));


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

    if(ui->twOnlineExperiments->currentItem()) {
        ExperimentTreeWidgetItem *expTWI = (ExperimentTreeWidgetItem *) ui->twOnlineExperiments->currentItem();
        emit setExperiment(new Experiment(expTWI->dataw.data));
    }
}

void RessourcesBrowser::loadLocalEntity() {
    if(ui->twLocalEntities->currentItem()) {
        EntityTreeWidgetItem *entityTWI = (EntityTreeWidgetItem *) ui->twLocalEntities->currentItem();
        emit addEntity(entityTWI->dataw.data, NULL /* entityTWI->dataw.r */);
    }
}

void RessourcesBrowser::loadOnlineEntity() {
    if(ui->twOnlineEntities->currentItem()) {
        EntityTreeWidgetItem *entityTWI = (EntityTreeWidgetItem *) ui->twOnlineEntities->currentItem();
        emit addEntity(entityTWI->dataw.data, NULL /* entityTWI->dataw.r */);
    }
}

void RessourcesBrowser::openExperimentFolder() {

    QString path = QDir::toNativeSeparators(QDir("ressources").absolutePath());
    QDesktopServices::openUrl(QUrl("file:///" + path));
}


void RessourcesBrowser::saveEntity() {

    if(ui->twOnlineEntities->currentItem()) {

        EntityTreeWidgetItem *entityTWI = (EntityTreeWidgetItem *) ui->twOnlineEntities->currentItem();
        QString selectedFile = QFileDialog::getSaveFileName(this, "Save the genome", "ressources", "Genome (*.genome)");

        if (!selectedFile.isEmpty()) {

            // Load Generic Entity
            Ressource* to = new JsonFile(selectedFile);
            to->save(entityTWI->dataw.data);

            refreshLocalRessources();
       }
    }
}

void RessourcesBrowser::saveExperiment() {

    if(ui->twOnlineExperiments->currentItem()) {

        ExperimentTreeWidgetItem *expTWI = (ExperimentTreeWidgetItem *) ui->twOnlineExperiments->currentItem();
        QString selectedFile = QFileDialog::getSaveFileName(this, "Save the experiment", "ressources", "Experiment (*.exp)");

        if (!selectedFile.isEmpty()) {

            // Load Generic Entity
            Ressource* to = new JsonFile(selectedFile);
            to->save(expTWI->dataw.data);

            refreshLocalRessources();
       }
    }
}

void RessourcesBrowser::on_pushButton_clicked()
{
    QMessageBox::information(this, "Utilisation of genecraft database", "This database is not an online backup."
                             "But a community tool. Everythings that you put online could be modified or deleted by someone else. So keep some backup of your loved creatures.");
}

void RessourcesBrowser::on_pbShareExp_clicked()
{
    if(ui->twLocalExperiments->currentItem()) {

        ExperimentTreeWidgetItem *expTWI = (ExperimentTreeWidgetItem *) ui->twLocalExperiments->currentItem();

        // Load Generic Entity
        Ressource* to = new DbRecord(database, expTWI->dataw.data["id"].toString());
        QVariant load = to->load();
        qDebug() << load;
        if(load.toMap().contains("error")) {
            to->save(expTWI->dataw.data);
            refreshOnlineRessources();
        } else {
            int replace = QMessageBox::warning(this, "Share to online database", "An experiment of "
                                               "this id already exist, would you like to replace it ?",
                                                QMessageBox::Yes, QMessageBox::No);
            if(replace == QMessageBox::Yes) {
                to->save(expTWI->dataw.data);
                refreshOnlineRessources();
            }

        }

    }
}
