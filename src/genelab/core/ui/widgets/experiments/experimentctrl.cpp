#include "experimentctrl.h"
#include "ui_experimentctrl.h"
#include "experiment/result.h"
#include "tools.h"
#include "ressourcesItems.h"

namespace GeneLabCore {

    ExperimentCtrl::ExperimentCtrl(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ExperimentCtrl)
    {
        ui->setupUi(this);
        this->experiment = NULL;
        this->resultsManager = NULL;
        autorefresh = new QTimer();
        autorefresh->setInterval(1000);
        connect(autorefresh, SIGNAL(timeout()), this, SLOT(refresh()));
        connect(this->ui->checkBox, SIGNAL(stateChanged(int)), this, SLOT(toggleRefresh()));
    }

    void ExperimentCtrl::setExperiment(Experiment* experiment) {
        this->ui->lblId->setText(experiment->getId());
        this->ui->lblAuthor->setText(experiment->getAuthor());
        this->ui->lblDate->setText(experiment->getDateOfCreation().toString());
        this->ui->lblDescription->setText(experiment->getDescription());

        this->oldResultsManager = resultsManager;
        this->resultsManager    = new ResultsManager(experiment, 100, 100, "CreatureViewer");

        loaded = false;
        this->refresh();
//        this->autorefresh->start();
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
        if(ui->treeWidget->currentItem())
            selectedResult = ((ResultTreeWidgetItem *) ui->treeWidget->currentItem())->r;

        // clear
        Tools::clearTreeWidget(this->ui->treeWidget);

        // fill
        foreach(Result* r, results) {
            ResultTreeWidgetItem * item = new ResultTreeWidgetItem(r);
            this->ui->treeWidget->addTopLevelItem(item);
        }

        // select previous selected item
        if(selectedResult) {
            int nbItems = ui->treeWidget->topLevelItemCount();
            for(int i=0;i<nbItems; ++i) {
               ResultTreeWidgetItem *item = (ResultTreeWidgetItem *) ui->treeWidget->topLevelItem(i);
               if(selectedResult == item->r) {
                    ui->treeWidget->setCurrentItem(item,0);
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


    void GeneLabCore::ExperimentCtrl::on_btnLoad_clicked()
    {
        if(this->ui->treeWidget->currentIndex().row() > -1) {
            Result* r = this->results[this->ui->treeWidget->currentIndex().row()];
            emit addEntity(r->getGenome().toMap(), NULL);
        }
    }
}
