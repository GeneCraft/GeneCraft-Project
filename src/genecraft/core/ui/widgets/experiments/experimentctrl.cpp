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

#include "experimentctrl.h"
#include "ui_experimentctrl.h"
#include "experiment/result.h"
#include "uitools.h"
#include "ressourcesItems.h"
#include "events/inspectorsinputmanager.h"

#include <QMessageBox>

namespace GeneCraftCore {

    ExperimentCtrl::ExperimentCtrl(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ExperimentCtrl)
    {
        ui->setupUi(this);
        this->experiment = NULL;
        this->resultsManager = NULL;

        epc = new ExperimentsPropertiesController();

        // Conversion controleur
        DataBase db;
        db.dbName = "/db/genecraft/";
        db.url = "http://www.genecraft-project.org";
        db.port = 80;
        conversionCtrl = new ConversionCtrl(QDir("./ressources/"), db);

        // refresh events
        autorefresh = new QTimer();
        autorefresh->setInterval(1000);
        connect(autorefresh, SIGNAL(timeout()), this, SLOT(refresh()));
        connect(this->ui->checkBox, SIGNAL(stateChanged(int)), this, SLOT(toggleRefresh()));
        connect(ui->pbRefresh,SIGNAL(clicked()),this,SLOT(refresh()));
        connect(ui->twResults,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_btnLoad_clicked()));

        connect(ui->pbEditExperiment,SIGNAL(clicked()),this,SLOT(openExperimentPropertiesController()));
        connect(ui->pbNewExperiment,SIGNAL(clicked()),this,SLOT(newExperiment()));

        connect(ui->pbDeleteAllResults,SIGNAL(clicked()),this,SLOT(deleteAllResults()));

        connect(ui->pbConvertResults,SIGNAL(clicked()),this,SLOT(openConvertWidget()));

        setEnabled(false);
    }

    void ExperimentCtrl::connectToInspectorInputManager(InspectorsInputManager * iim) {

        epc->connectToInspectorInputManager(iim);
        conversionCtrl->connectToInspectorInputManager(iim);


        connect(iim, SIGNAL(sLoadExperiment(Experiment*)),this,SLOT(loadExperiment(Experiment*)));
        connect(this, SIGNAL(sLoadResult(Result*)),iim,SLOT(loadResult(Result*)));
        connect(this, SIGNAL(sAddEntity(QJsonObject,Ressource*)), iim, SLOT(loadEntity(QJsonObject, Ressource*)));
    }

    void ExperimentCtrl::refresh() {
        if(!resultsManager) {
            return;
        }

        this->refreshInProgress();
        if(loaded)
            resultsManager->reload();
        else {
            if(oldResultsManager) {
                oldResultsManager = NULL;
                delete oldResultsManager;
            }
            resultsManager->load();
            loaded = true;
        }
        this->refreshUI();
    }

    void ExperimentCtrl::refreshUI() {
        this->ui->lblDb->setText("");
        results = resultsManager->getBestResults();

        // save the selected result
        Result *selectedResult = NULL;
        if(ui->twResults->currentItem())
            selectedResult = ((ResultTreeWidgetItem *) ui->twResults->currentItem())->r;

        // clear
        UITools::clearTreeWidget(this->ui->twResults);

        // fill
        foreach(Result* r, results) {
            ResultTreeWidgetItem * item = new ResultTreeWidgetItem(r);
            this->ui->twResults->addTopLevelItem(item);
        }

        // select previous selected item
        if(selectedResult) {
            int nbItems = ui->twResults->topLevelItemCount();
            for(int i=0;i<nbItems; ++i) {
               ResultTreeWidgetItem *item = (ResultTreeWidgetItem *) ui->twResults->topLevelItem(i);
               if(selectedResult == item->r) {
                    ui->twResults->setCurrentItem(item,0);
                    return;
               }
            }
        }
    }

    void ExperimentCtrl::toggleRefresh() {
        if(this->autorefresh->isActive())
            this->autorefresh->stop();
        else
            this->autorefresh->start();
    }

    void ExperimentCtrl::refreshInProgress() {
        this->ui->lblDb->setText("Loading data...");
    }

    ExperimentCtrl::~ExperimentCtrl()
    {
        delete ui;
    }

    void ExperimentCtrl::on_btnLoad_clicked()
    {
        if(this->ui->twResults->currentItem()) {
            Result* r = this->results[this->ui->twResults->currentIndex().row()];
            emit sLoadResult(r);
            //emit addEntity(r->serialize().toMap(), NULL);
        }
    }

    void ExperimentCtrl::openExperimentPropertiesController(){

        epc->setExperiment(experiment);
        epc->show();
        epc->setFocus(Qt::MouseFocusReason);
    }

    void ExperimentCtrl::loadExperiment(Experiment *experiment) {

        this->experiment = experiment;
        setEnabled((bool)experiment);

        if(experiment) {

            this->ui->lblId->setText(experiment->getId());
            this->ui->lblAuthor->setText(experiment->getAuthor());
            this->ui->lblDate->setText(experiment->getDateOfCreation().toString());
            this->ui->lblDescription->setText(experiment->getDescription());

            this->oldResultsManager = resultsManager;
            this->resultsManager    = new ResultsManager(experiment, 100, 100, "CreatureViewer");

            loaded = false;
            this->refresh();
            // this->autorefresh->start();
        }
    }

    void ExperimentCtrl::newExperiment() {

        epc->setExperiment(new Experiment());
        epc->show();
        epc->setFocus(Qt::MouseFocusReason);
    }

    void ExperimentCtrl::on_btnAdd_clicked()
    {
        if(this->ui->twResults->currentItem()) {
            Result* r = this->results[this->ui->twResults->currentIndex().row()];
            emit sAddEntity(r->serialize().toMap(), NULL);
        }
    }

    void ExperimentCtrl::on_btnHelp_clicked()
    {
        QMessageBox::information(this, "Loading results to the scene", "There's two way of adding a result to the scene."
                                 " As a result, which mean deleting everything in the simulation to get the exact same result"
                                 " that the worker did, with the initial stabilisation process and everything. Or as a creature, which mean add this creature where stand the camera."
                                 " Obviously because of the physical engine state and the initials conditions that are differents the result will not be the same"
                                 " that the worker compute.");

    }

    void ExperimentCtrl::deleteAllResults() {

        if(experiment->isOnline()) {
            QMessageBox::information(this, "You can delete online results",
                                     "Deletion of online results in not yet available.");
        }
        else {
            int buttonPressed = QMessageBox::question(this, "Are you sure ?",
                                 "Are you sure do you want to \ndefinitively delete all results of this experiment ?", QMessageBox::Ok | QMessageBox::Cancel);

            if(buttonPressed == QMessageBox::Ok) {
                resultsManager->deleteAll();
                refresh();
            }
        }

    //    // DELETE SELECTED RESULTS...
    //    if(this->ui->twResults->currentItem()) {
    //        foreach(QTreeWidgetItem* item, ui->twResults->selectedItems()) {
    //            int index = ui->twResults->indexOfTopLevelItem(item);
    //            qDebug() << Q_FUNC_INFO << 1;
    //            Result* r = this->results[index];
    //            qDebug() << Q_FUNC_INFO << 2;
    //            if(r->getRessource() != NULL) {
    //                r->getRessource()->remove();
    //                qDebug() << Q_FUNC_INFO << 3;
    //                results.removeAt(index);
    //                qDebug() << Q_FUNC_INFO << 4;
    //                ui->twResults->removeItemWidget(item,0);
    //            }
    //        }
    //    }
    }

    void ExperimentCtrl::openConvertWidget() {
        conversionCtrl->show();
    }

}


