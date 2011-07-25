#include "experimentctrl.h"
#include "ui_experimentctrl.h"
#include "experiment/result.h"
#include "tools.h"
#include "ressourcesItems.h"
#include "events/inspectorsinputmanager.h"

namespace GeneLabCore {

    ExperimentCtrl::ExperimentCtrl(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ExperimentCtrl)
    {
        ui->setupUi(this);
        this->experiment = NULL;
        this->resultsManager = NULL;

        epc = new ExperimentsPropertiesController();

        // refresh events
        autorefresh = new QTimer();
        autorefresh->setInterval(1000);
        connect(autorefresh, SIGNAL(timeout()), this, SLOT(refresh()));
        connect(this->ui->checkBox, SIGNAL(stateChanged(int)), this, SLOT(toggleRefresh()));
        connect(ui->pbRefresh,SIGNAL(clicked()),this,SLOT(refresh()));
        connect(ui->twResults,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_btnLoad_clicked()));

        connect(ui->pbEditExperiment,SIGNAL(clicked()),this,SLOT(openExperimentPropertiesController()));
        connect(ui->pbNewExperiment,SIGNAL(clicked()),this,SLOT(newExperiment()));

        setEnabled(false);
    }

    void ExperimentCtrl::connectToInspectorInputManager(InspectorsInputManager * iim) {

        epc->connectToInspectorInputManager(iim);
        connect(iim,SIGNAL(sLoadExperiment(Experiment*)),this,SLOT(loadExperiment(Experiment*)));
        connect(this,SIGNAL(sLoadResult(Result*)),iim,SLOT(loadResult(Result*)));
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
        Tools::clearTreeWidget(this->ui->twResults);

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
}
