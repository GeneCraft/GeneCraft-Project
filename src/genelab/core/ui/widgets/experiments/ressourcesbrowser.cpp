#include "ressourcesbrowser.h"
#include "ui_ressourcesbrowser.h"

#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>
#include <QInputDialog>

#include "ressourcesItems.h"
#include "experiment/experiment.h"
#include "tools.h"
#include "creaturefactory.h"
#include "ressources/jsonfile.h"
#include "events/inspectorsinputmanager.h"

namespace GeneLabCore {

RessourcesBrowser::RessourcesBrowser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RessourcesBrowser)
{
    ui->setupUi(this);

    // TODO QSettings
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
    connect(ui->pbOpenExperimentsFolder,SIGNAL(clicked()),this,SLOT(openRessourcesFolder()));
    connect(ui->pbSaveExp,SIGNAL(clicked()),this,SLOT(saveExperiment()));
    connect(ui->pbShareExp,SIGNAL(clicked()),this,SLOT(shareExperiment()));
    connect(ui->pbInfoExp,SIGNAL(clicked()),this,SLOT(openInfoDatabase()));

    // worlds
    connect(ui->pbRefreshLocalWorlds,SIGNAL(clicked()),this,SLOT(refreshLocalRessources()));
    connect(ui->pbRefreshOnlineWorlds,SIGNAL(clicked()),this,SLOT(refreshOnlineRessources()));
    connect(ui->pbLoadLocalWorld,SIGNAL(clicked()),this,SLOT(loadLocalWorld()));
    connect(ui->pbLoadOnlineWorld,SIGNAL(clicked()),this,SLOT(loadOnlineWorld()));
    connect(ui->pbOpenWorldsFolder,SIGNAL(clicked()),this,SLOT(openRessourcesFolder())); // TODO
    connect(ui->pbSaveExp,SIGNAL(clicked()),this,SLOT(saveWorld()));
    connect(ui->pbShareWorld,SIGNAL(clicked()),this,SLOT(shareWorld()));
    connect(ui->pbInfoWorlds,SIGNAL(clicked()),this,SLOT(openInfoDatabase()));

    // entities
    connect(ui->pbRefreshLocalEntity,SIGNAL(clicked()),this,SLOT(refreshLocalRessources()));
    connect(ui->pbRefreshOnlineEntity,SIGNAL(clicked()),this,SLOT(refreshOnlineRessources()));
    connect(ui->pbLoadLocalEntity,SIGNAL(clicked()),this,SLOT(loadLocalEntity()));
    connect(ui->pbLoadOnlineEntity,SIGNAL(clicked()),this,SLOT(loadOnlineEntity()));
    connect(ui->pbOpenEntitiesFolder,SIGNAL(clicked()),this,SLOT(openRessourcesFolder())); // TODO
    connect(ui->pbSaveEntity,SIGNAL(clicked()),this,SLOT(saveEntity()));
    connect(ui->pbShareEntity,SIGNAL(clicked()),this,SLOT(shareEntity()));
    connect(ui->pbInfoEntities,SIGNAL(clicked()),this,SLOT(openInfoDatabase()));

    refreshLocalRessources();
}

RessourcesBrowser::~RessourcesBrowser()
{
    delete ui;
}

void RessourcesBrowser::connectToInspectorInputManager(GeneLabCore::InspectorsInputManager * iim) {

    connect(this,SIGNAL(loadExperiment(Experiment*)),iim,SLOT(loadExperiment(Experiment*)));
    connect(this,SIGNAL(loadWorld(QVariant worldData)),iim,SLOT(loadWorld(Experiment*)));
    connect(this,SIGNAL(loadEntity(Experiment*)),iim,SLOT(loadEntity(Experiment*)));

}


// ----------------
// -- RESSOURCES --
// ----------------

void RessourcesBrowser::refreshLocalRessources() {
    localRessourceManager->reloadDir();

    // clear lists
    Tools::clearTreeWidget(this->ui->twLocalExperiments);
    Tools::clearTreeWidget(this->ui->twLocalWorlds);
    Tools::clearTreeWidget(this->ui->twLocalEntities);

    // fill lists
    foreach(DataWrapper exp, localRessourceManager->getExperiments())
        ui->twLocalExperiments->insertTopLevelItem(0,new ExperimentTreeWidgetItem(exp));

    foreach(DataWrapper world, localRessourceManager->getWorlds())
        ui->twLocalWorlds->insertTopLevelItem(0,new WorldTreeWidgetItem(world));

    foreach(DataWrapper entity, localRessourceManager->getCreatures())
        ui->twLocalEntities->insertTopLevelItem(0,new EntityTreeWidgetItem(entity));
}

void RessourcesBrowser::refreshOnlineRessources() {
    this->ui->lblDb->setText("Loading from database...");
    onlineRessourceManager->reloadDb();
    this->ui->lblDb->setText("Ressources loaded from database...");

    // clear lists
    Tools::clearTreeWidget(this->ui->twOnlineExperiments);
    Tools::clearTreeWidget(this->ui->twOnlineWorlds);
    Tools::clearTreeWidget(this->ui->twOnlineEntities);

    // fill lists
    foreach(DataWrapper exp, onlineRessourceManager->getExperiments())
        ui->twOnlineExperiments->insertTopLevelItem(0,new ExperimentTreeWidgetItem(exp));

    foreach(DataWrapper world, onlineRessourceManager->getWorlds())
        ui->twOnlineWorlds->insertTopLevelItem(0,new WorldTreeWidgetItem(world));

    foreach(DataWrapper entity, onlineRessourceManager->getCreatures())
        ui->twOnlineEntities->insertTopLevelItem(0,new EntityTreeWidgetItem(entity));
}

// ----------
// -- LOAD --
// ----------
void RessourcesBrowser::loadLocalExperiment() {

    if(ui->twLocalExperiments->currentItem()) {
        ExperimentTreeWidgetItem *expTWI = (ExperimentTreeWidgetItem *) ui->twLocalExperiments->currentItem();
        Experiment* e = new Experiment(expTWI->dataw.data);
        e->setOnline(false); // Local experimentation
        e->setRessource(expTWI->dataw.r);
        emit loadExperiment(e);
    }
}

void RessourcesBrowser::loadOnlineExperiment() {

    if(ui->twOnlineExperiments->currentItem()) {
        ExperimentTreeWidgetItem *expTWI = (ExperimentTreeWidgetItem *) ui->twOnlineExperiments->currentItem();
        Experiment* e = new Experiment(expTWI->dataw.data);
        e->setOnline(true); // Online experimentation
        emit loadExperiment(e);
    }
}

void RessourcesBrowser::loadLocalWorld() {

    if(ui->twLocalWorlds->currentItem()) {
        WorldTreeWidgetItem *worldTWI = (WorldTreeWidgetItem *) ui->twLocalWorlds->currentItem();
        emit loadWorld(worldTWI->dataw.data);
    }
}

void RessourcesBrowser::loadOnlineWorld() {

    if(ui->twOnlineExperiments->currentItem()) {
        WorldTreeWidgetItem *worldTWI = (WorldTreeWidgetItem *) ui->twOnlineWorlds->currentItem();
        emit loadWorld(worldTWI->dataw.data);
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


// ----------
// -- SAVE --
// ----------

void RessourcesBrowser::saveExperiment() {

    if(ui->twOnlineExperiments->currentItem()) {

        ExperimentTreeWidgetItem *expTWI = (ExperimentTreeWidgetItem *) ui->twOnlineExperiments->currentItem();

        QString selectedFile = QString("ressources/") + QString(expTWI->dataw.data["_id"].toString()) + QString(".exp");

//        QString selectedFile = QFileDialog::getSaveFileName(this, "Save the experiment", "ressources", "Experiment (*.exp)");
//        if (!selectedFile.isEmpty()) {

            // Load Generic Entity
            Ressource* to = new JsonFile(selectedFile);
            to->save(expTWI->dataw.data);

            refreshLocalRessources();
//       }
    }
}

void RessourcesBrowser::saveWorld() {

    if(ui->twOnlineWorlds->currentItem()) {

        WorldTreeWidgetItem *worldTWI = (WorldTreeWidgetItem *) ui->twOnlineWorlds->currentItem();

        QString selectedFile = QString("ressources/") + QString(worldTWI->dataw.data["name"].toString()) + QString(".world");

//        QString selectedFile = QFileDialog::getSaveFileName(this, "Save the world, that's good :)", "worlds", "World (*.world)");
//        if (!selectedFile.isEmpty()) {

            // Load Generic Entity
            Ressource* to = new JsonFile(selectedFile);
            to->save(worldTWI->dataw.data);

            refreshLocalRessources();
//       }
    }
}

void RessourcesBrowser::saveEntity() {

    if(ui->twOnlineEntities->currentItem()) {

        EntityTreeWidgetItem *entityTWI = (EntityTreeWidgetItem *) ui->twOnlineEntities->currentItem();

        QString selectedFile = QString("ressources/") + QString(entityTWI->dataw.data["name"].toString()) + QString(".genome");

//        QString selectedFile = QFileDialog::getSaveFileName(this, "Save the genome", "ressources", "Genome (*.genome)");
//        if (!selectedFile.isEmpty()) {

            // Load Generic Entity
            Ressource* to = new JsonFile(selectedFile);
            to->save(entityTWI->dataw.data);

            refreshLocalRessources();
//       }
    }
}

// -----------
// -- SHARE --
// -----------

void RessourcesBrowser::shareExperiment()
{
    if(ui->twLocalExperiments->currentItem()) {

        ExperimentTreeWidgetItem *expTWI = (ExperimentTreeWidgetItem *) ui->twLocalExperiments->currentItem();

        // Load Generic Entity
        Ressource* to = new DbRecord(database, expTWI->dataw.data["id"].toString());
        QVariant load = to->load();
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

void RessourcesBrowser::shareWorld()
{
    if(ui->twLocalWorlds->currentItem()) {

        WorldTreeWidgetItem *worldTWI = (WorldTreeWidgetItem *) ui->twLocalWorlds->currentItem();

        // Load Generic Entity
        Ressource* to = new DbRecord(database, worldTWI->dataw.data["id"].toString());
        QVariant load = to->load();
        if(load.toMap().contains("error")) {
            to->save(worldTWI->dataw.data);
            refreshOnlineRessources();
        } else {
            int replace = QMessageBox::warning(this, "Share to online database", "A world of "
                                               "this id already exist, would you like to replace it ?",
                                                QMessageBox::Yes, QMessageBox::No);
            if(replace == QMessageBox::Yes) {
                to->save(worldTWI->dataw.data);
                refreshOnlineRessources();
            }

        }
    }
}

void RessourcesBrowser::shareEntity()
{
    if(ui->twLocalEntities->currentItem()) {
        QString id = QInputDialog::getText(this, "Share to genecraft-project db", "Please, enter the creature id");
        if(id == "") {
            QMessageBox::warning(this, "Share to genecraft-project db", "Error, no id provided.");
            return;
        }

        EntityTreeWidgetItem *expTWI = (EntityTreeWidgetItem *) ui->twLocalEntities->currentItem();

        // Load Generic Entity
        Ressource* to = new DbRecord(database, id);
        QVariantMap creatureData = expTWI->dataw.data;
        QVariantMap origins = creatureData["origins"].toMap();
        qDebug() << creatureData["origins"].toMap();
        origins.insert("name", id);
        creatureData.insert("origins", origins);
        qDebug() << creatureData["origins"].toMap();

        QVariant load = to->load();
        if(load.toMap().contains("error")) {
            to->save(creatureData);
            refreshOnlineRessources();
        } else {
            int replace = QMessageBox::warning(this, "Share to online database", "A creature of "
                                               "this id already exist online, would you like to replace it ?",
                                                QMessageBox::Yes, QMessageBox::No);
            if(replace == QMessageBox::Yes) {
                to->save(creatureData);
                refreshOnlineRessources();
            }

        }

    }
}

// ----------
// -- INFO --
// ----------

void RessourcesBrowser::openInfoDatabase()
{
    QMessageBox::information(this, "Utilisation of genecraft database", "This database is not an online backup."
                             "But a community tool. Everythings that you put online could be modified or deleted by someone else. So keep some backup of your loved creatures.");
}


void RessourcesBrowser::openRessourcesFolder() {

    QString path = QDir::toNativeSeparators(QDir("ressources").absolutePath());
    QDesktopServices::openUrl(QUrl("file:///" + path));
}

}
