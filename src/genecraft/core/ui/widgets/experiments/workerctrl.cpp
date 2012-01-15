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

#include "workerctrl.h"
#include "ui_workerctrl.h"

#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QProcess>
#include <QMessageBox>

#include "ressources/jsonfile.h"
#include "events/inspectorsinputmanager.h"

namespace GeneCraftCore {

    WorkerCtrl::WorkerCtrl(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::WorkerCtrl)
    {
        ui->setupUi(this);
        process = NULL;
        exp = NULL;

        setEnabled(false);
    }

    WorkerCtrl::~WorkerCtrl()
    {
        if(process && process->state() == QProcess::Running) {
            process->kill();
            delete process;
        }
        delete ui;
    }

    void WorkerCtrl::connectToInspectorInputManager(InspectorsInputManager * iim) {

        connect(iim,SIGNAL(sLoadExperiment(Experiment*)),this,SLOT(setExperiment(Experiment*)));
    }

    void WorkerCtrl::setExperiment(Experiment *exp) {
        this->exp = exp;

        setEnabled((bool)exp);

        if(exp) {
            this->ui->label->setText("Experiment : " + exp->getId());
        }
    }

    void WorkerCtrl::on_btnStart_clicked()
    {
        if(!this->exp)
            return;

        if(this->process) {
            this->process->kill();
            this->process->deleteLater();
            this->process = NULL;
            this->ui->btnStart->setText("Start worker");
            return;
        }

        QString workerExe = "./genecraft_worker.exe";
        //QString workerExe = "/Users/cyprienhuissoud/Desktop/genelab/genelab/src/genelab_worker-build-desktop/genelab_worker";
        QFile workerFile(workerExe);
        if(!workerFile.exists()) {
            QString workerExe  = QFileDialog::getOpenFileName(this, "Select the worker binary","genecraft_worker.exe");

            if(workerExe.isEmpty())
                return;

            workerFile.setFileName(workerExe);
        }

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
        params << "--gui" << expFile;
        QDir workerDir = QDir(".");//workerFileInfo.absoluteDir();
        process->setWorkingDirectory(workerDir.absolutePath());
        process->setReadChannel(QProcess::StandardError);
        process->start(workerFileInfo.absoluteFilePath(), params);
        this->ui->btnStart->setText("Stop worker");
    }

    void WorkerCtrl::readyRead() {
        // Suppression au bout d'un moment
        // TODO : Remove static
        static int readyRead = 0;
        readyRead++;
        if(readyRead%200 == 0) {
            this->ui->txtOut->clear();
        }
        // Ajout du text Ã  la sortie de la console
        if(!process)
            return;
        QString data = process->readAllStandardError();
        this->ui->txtOut->append(data.left(data.size()-1));
    }

}
