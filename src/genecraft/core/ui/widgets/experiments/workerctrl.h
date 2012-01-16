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

#ifndef WORKERCTRL_H
#define WORKERCTRL_H

#include <QWidget>
#include <QProcess>

#include "experiment/experiment.h"

namespace Ui {
    class WorkerCtrl;
}

namespace GeneCraftCore {

class WorkerCtrl : public QWidget
{
    Q_OBJECT

public:
    explicit WorkerCtrl(QWidget *parent = 0);
    ~WorkerCtrl();

    void connectToInspectorInputManager(InspectorsInputManager * iim);

public slots:
    void setExperiment(Experiment* exp);

private:
    Ui::WorkerCtrl *ui;
    QProcess* process;
    Experiment* exp;

private slots:
    void on_btnStart_clicked();
    void readyRead();

};
}

#endif // WORKERCTRL_H
