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

#ifndef STATISTICSPROPERTIESCONTROLLER_H
#define STATISTICSPROPERTIESCONTROLLER_H

#include <QWidget>
#include <QTimer>
#include "genecraftcoreclasses.h"
#include "widgets/plot/fitnessplot.h"

using namespace GeneCraftCore;
namespace Ui {
    class StatisticsPropertiesController;
}

class StatisticsPropertiesController : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsPropertiesController(QWidget *parent = 0);
    ~StatisticsPropertiesController();

    // To connect inspector input manager to be notified if the entity is deleted
    void connectToInspectorInputManager(InspectorsInputManager *iim);

public slots:
    void setEntity(Entity *entity);
    void updateStats();
    void resetAllStats();
    void resetSelectedStat();

    void entityDeleted(Entity *entity);
public:

    FitnessPlot* fitness;

private:
    Ui::StatisticsPropertiesController *ui;

    Entity *entity;

    QTimer *statsTimer;

private slots:
    void on_pushButton_clicked();
};

#endif // STATISTICSPROPERTIESCONTROLLER_H
