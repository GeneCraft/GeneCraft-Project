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

#include "conversionctrl.h"
#include "ui_conversionctrl.h"

#include "events/inspectorsinputmanager.h"
#include "experiment.h"
#include "ressources/ressourcesmanager.h"
#include "uitools.h"
#include "ressourcesItems.h"
#include "ressources/jsonfile.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

namespace GeneCraftCore {

    ConversionCtrl::ConversionCtrl(QDir ressourceDir, DataBase db, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ConversionCtrl)
    {
        ui->setupUi(this);
        localRes  = new RessourcesManager(db, ressourceDir);
        onlineRes = new RessourcesManager(db, ressourceDir);

        // Null at start
        process = NULL;
        exp = NULL;
        from = NULL;

        // Refresh exp
        this->on_btnRefresh_clicked();
        this->ui->stackedWidget->setCurrentIndex(1);

        connect(ui->pbInformation,SIGNAL(clicked()),this,SLOT(showInformation()));
    }

    ConversionCtrl::~ConversionCtrl()
    {
        delete ui;
    }

    void ConversionCtrl::setExperiment(Experiment *exp) {
        this->exp = exp;
        this->ui->lblExp->setText(exp->getId());
    }


    void ConversionCtrl::connectToInspectorInputManager(GeneCraftCore::InspectorsInputManager *iim) {
        connect(iim, SIGNAL(sExperimentUpdated(Experiment*)), this, SLOT(setExperiment(Experiment*)));
        connect(iim, SIGNAL(sLoadExperiment(Experiment*)), this, SLOT(setExperiment(Experiment*)));
    }

    void ConversionCtrl::on_btnConvert_clicked()
    {

        qDebug() << "CONVERT";
        if(!this->exp || !this->from)
            return;


        QString workerExe = "./genecraft_worker.exe";
        QFile workerFile(workerExe);

        // The From Id
        QString expFrom;
        if(from->isOnline()) {
            expFrom = from->getId();
        } else if(from->hasRessource()) {
            expFrom = QFileInfo(((JsonFile*)from->getRessource())->filename).absoluteFilePath();
        } else {
            qDebug() << "NOT A VALID FROM EXPERIMENT, ABORTING";
            return;
        }

        // The To Id
        QString expFile;
        if(exp->isOnline()) {
            expFile = exp->getId();
        } else if(exp->hasRessource()) {
            expFile = QFileInfo(((JsonFile*)exp->getRessource())->filename).absoluteFilePath();
        } else {

            // save experiment
            expFile = QFileDialog::getSaveFileName(this, "Save your experiment before launch worker", "./ressources/" + exp->getId() + ".exp", "Experiment (*.exp)");

            if(expFile.isEmpty())
                return;

            // To exp ressource
            Ressource* to = new JsonFile(expFile);
            int code = to->save(exp->serialize());

            // Error
            if(code != 0) {
                QMessageBox::warning(this, "Impossible to save experiment",
                QString("Impossible to save experiment : error code : ") + QString::number(code));

                exp->setRessource(NULL);
                return;
            }

            exp->setRessource(to);
        }

        process = new QProcess();
        connect(process, SIGNAL(readyReadStandardError()), this, SLOT(readyRead()));
        QFileInfo workerFileInfo(workerFile);
        QStringList params;
        params << "convert" << expFrom << expFile << QString::number(ui->spbNb->value());
        QDir workerDir = QDir(".");
        qDebug() << params;
        process->setWorkingDirectory(workerDir.absolutePath());
        process->setReadChannel(QProcess::StandardError);
        process->start(workerFileInfo.absoluteFilePath(), params);
        this->ui->stackedWidget->setCurrentIndex(0);

    }

    void ConversionCtrl::on_btnStop_clicked()
    {
        if(this->process) {
            this->process->kill();
            this->process->deleteLater();
            this->process = NULL;
        }
        this->ui->stackedWidget->setCurrentIndex(1);
    }

    void ConversionCtrl::on_btnRefresh_clicked()
    {
        onlineRes->reloadDb();
        localRes->reloadDir();

        UITools::clearTreeWidget(ui->twExperiments);

        foreach(DataWrapper exp, onlineRes->getExperiments())
            ui->twExperiments->insertTopLevelItem(0,new ExperimentTreeWidgetItem(exp,true));

        foreach(DataWrapper exp, localRes->getExperiments())
            ui->twExperiments->insertTopLevelItem(0,new ExperimentTreeWidgetItem(exp,true));

    }

    void ConversionCtrl::readyRead() {
        // Suppression au bout d'un moment
        // TODO : Remove static
        static int readyRead = 0;
        readyRead++;
        if(readyRead%200 == 0) {
            this->ui->txtOut->clear();
        }
        // Ajout du text   la sortie de la console
        if(!process)
            return;
        QString data = process->readAllStandardError();
        this->ui->txtOut->append(data.left(data.size()-1));
    }

    void ConversionCtrl::on_twExperiments_currentItemChanged(QTreeWidgetItem* item,  QTreeWidgetItem *)
    {
        if(item) {
            ExperimentTreeWidgetItem *expTWI = (ExperimentTreeWidgetItem *)item;
            Experiment* e = new Experiment(expTWI->dataw.data);
            e->setRessource(expTWI->dataw.r);
            e->setOnline(!e->hasRessource()); // Online experimentation ?
            from = e;
            qDebug() << "from setted to" << e->getId();
        }
        else {
            this->from = NULL;
        }
    }

    void ConversionCtrl::showInformation() {

        QMessageBox::information(this, "Import results", "This form allows you to import results from a specific experiment. "
                                 "Results will be reassess to fit to the fitness function of the experiment.\n\nJust select "
                                 "experiment which contains the results you would like import and press on the 'Import' button. "
                                 "Then, the convertion process will start. Notice that you can choose how many results you want to import.");
    }
}
