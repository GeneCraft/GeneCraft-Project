#include "experimentctrl.h"
#include "ui_experimentctrl.h"
#include "experiment/result.h"

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

        this->ui->checkBox->setChecked(true);
        this->autorefresh->start();
    }

    void ExperimentCtrl::refresh() {
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
        this->ui->treeWidget->clear();

        foreach(Result* r, results) {
            QTreeWidgetItem* item = new QTreeWidgetItem();
            item->setText(0, QString::number(r->getFitness(), 10, 2));
            item->setText(1, r->getWorker());
            item->setText(2, r->getDate());

            this->ui->treeWidget->addTopLevelItem(item);
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
