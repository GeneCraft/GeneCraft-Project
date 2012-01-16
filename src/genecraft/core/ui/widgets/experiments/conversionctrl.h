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

#ifndef CONVERSIONCTRL_H
#define CONVERSIONCTRL_H

#include <QWidget>
#include <QDir>
#include <QProcess>
#include <QTreeWidgetItem>
#include "ressources/dbrecord.h"
#include "genecraftcoreclasses.h"


namespace Ui {
    class ConversionCtrl;
}

namespace GeneCraftCore {

    class ConversionCtrl : public QWidget
    {
        Q_OBJECT

    public:
        explicit ConversionCtrl(QDir ressourceDir, DataBase db, QWidget *parent = 0);
        ~ConversionCtrl();

        void connectToInspectorInputManager(GeneCraftCore::InspectorsInputManager * iim);


    public slots:
        void setExperiment(Experiment* exp);
        void showInformation();

    private:
        Ui::ConversionCtrl *ui;
        // The actual experiment
        Experiment* exp;
        // The one to take data from
        Experiment* from;
        // All ressources, to get the experiments list
        RessourcesManager* localRes;
        RessourcesManager* onlineRes;
        // The worker process
        QProcess* process;


private slots:
    void on_twExperiments_currentItemChanged(QTreeWidgetItem* item, QTreeWidgetItem* previous);
    void on_btnRefresh_clicked();
    void on_btnStop_clicked();
    void on_btnConvert_clicked();
    void readyRead();
};

}

#endif // CONVERSIONCTRL_H
