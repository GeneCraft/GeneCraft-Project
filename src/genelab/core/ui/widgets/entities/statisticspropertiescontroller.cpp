#include "statisticspropertiescontroller.h"
#include "ui_statisticspropertiescontroller.h"

#include "bodyitems.h"
#include "entity.h"
#include "tools.h"
#include "events/inspectorsinputmanager.h"

StatisticsPropertiesController::StatisticsPropertiesController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsPropertiesController)
{
    ui->setupUi(this);

    // Statistics headers
    connect(this->ui->pbResetAllStats,SIGNAL(clicked()),this,SLOT(resetAllStats()));
    connect(this->ui->pbResetSelectedStat,SIGNAL(clicked()),this,SLOT(resetSelectedStat()));

    ui->twStats->setColumnWidth(0,200);
    ui->twStats->setColumnWidth(1,70);
    ui->twStats->setColumnWidth(2,60);

    // Statistics refresh timer
    statsTimer = new QTimer();
    statsTimer->setInterval(1000/5); // by ms
    connect(statsTimer, SIGNAL(timeout()), this, SLOT(updateStats()));
    statsTimer->start();

    setEnabled(false);
}

StatisticsPropertiesController::~StatisticsPropertiesController()
{
    delete ui;
}

void StatisticsPropertiesController::connectToInspectorInputManager(InspectorsInputManager *iim)
{
    // notifications
    connect(iim,SIGNAL(sEntitySelected(Entity *)),this,SLOT(setEntity(Entity*)));
    connect(iim,SIGNAL(sEntityDeleted(Entity *)),this,SLOT(entityDeleted(Entity *)),Qt::DirectConnection);
}

void StatisticsPropertiesController::entityDeleted(Entity * entity){

    if(this->entity == entity)
        setEntity(NULL);
}

void StatisticsPropertiesController::setEntity(Entity *entity)
{
    this->entity = entity;

    if(entity)
    {
        // Statistics
        Tools::clearTreeWidget(ui->twStats);

        QMapIterator<QString, Statistic *> iStats(entity->getStatisticsStorage()->getStatistics());
        iStats.toBack();
        while (iStats.hasPrevious()) {
            Statistic * stat = iStats.previous().value();
            ui->twStats->insertTopLevelItem(0,new StatisticTreeWidgetItem(stat));
        }
        updateStats();

        setEnabled(true);
    }
    else
        setEnabled(false);
}

void StatisticsPropertiesController::updateStats(){
    if(entity){
        for(int i=0; i<ui->twStats->topLevelItemCount(); ++i) {
            ((StatisticTreeWidgetItem *) ui->twStats->topLevelItem(i))->update();
        }
    }
}

void StatisticsPropertiesController::resetAllStats(){
    if(entity){
        for(int i=0; i<ui->twStats->topLevelItemCount(); ++i) {
            ((StatisticTreeWidgetItem *) ui->twStats->topLevelItem(i))->stat->resetAll();
        }
    }
}

void StatisticsPropertiesController::resetSelectedStat(){
    if(entity){
        if(ui->twStats->currentItem()){
            ((StatisticTreeWidgetItem *) ui->twStats->currentItem())->stat->resetAll();
        }
    }
}
