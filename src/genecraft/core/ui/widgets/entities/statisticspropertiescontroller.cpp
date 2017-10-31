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

#include "statisticspropertiescontroller.h"
#include "ui_statisticspropertiescontroller.h"

#include "bodyitems.h"
#include "entity.h"
#include "uitools.h"
#include "events/inspectorsinputmanager.h"

#include "widgets/plot/fitnessplot.h"

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
    statsTimer->setInterval(1000/10); // by ms
    connect(statsTimer, SIGNAL(timeout()), this, SLOT(updateStats()));
    statsTimer->start();

    setEnabled(false);

    fitness = new FitnessPlot(parent);
    ui->tab_2->layout()->addWidget(fitness);
}


StatisticsPropertiesController::~StatisticsPropertiesController()
{
    delete ui;
}


void StatisticsPropertiesController::connectToInspectorInputManager(InspectorsInputManager *iim)
{
    // notifications
    connect(iim,SIGNAL(sEntitySelected(Entity *)),this,SLOT(setEntity(Entity*)), Qt::DirectConnection);
    connect(iim, SIGNAL(sEntitySelected(Entity*)), fitness, SLOT(setEntity(Entity*)), Qt::DirectConnection);
    connect(iim, SIGNAL(sExperimentUpdated(Experiment*)), fitness, SLOT(setExperiment(Experiment*)),Qt::DirectConnection);
    connect(iim, SIGNAL(sLoadExperiment(Experiment*)), fitness, SLOT(setExperiment(Experiment*)),Qt::DirectConnection);
    connect(iim,SIGNAL(sEntityDeleted(Entity *)),this,SLOT(entityDeleted(Entity *)),Qt::DirectConnection);
    connect(iim, SIGNAL(sEntityDeleted(Entity*)), fitness, SLOT(entityDeleted(Entity*)), Qt::DirectConnection);
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
        UITools::clearTreeWidget(ui->twStats);

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
        entity->setAge(0);
        fitness->reset();
    }

}

void StatisticsPropertiesController::resetSelectedStat(){
    if(entity){

        if(ui->twStats->currentItem()){
            if(((StatisticTreeWidgetItem *) ui->twStats->currentItem())->stat->getName() == "age") {
                fitness->reset();
                entity->setAge(0);
            }

            ((StatisticTreeWidgetItem *) ui->twStats->currentItem())->stat->resetAll();
        }
    }
}

void StatisticsPropertiesController::on_pushButton_clicked()
{
    if(entity){
        for(int i=0; i<ui->twStats->topLevelItemCount(); ++i) {
            ((StatisticTreeWidgetItem *) ui->twStats->topLevelItem(i))->stat->resetAll();
        }
        entity->setAge(0);
        fitness->reset();
    }
}
