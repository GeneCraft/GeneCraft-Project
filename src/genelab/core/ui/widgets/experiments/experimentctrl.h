#ifndef EXPERIMENTCTRL_H
#define EXPERIMENTCTRL_H

#include <QWidget>
#include "experiment/experiment.h"
#include "experiment/resultsmanager.h"
#include "experiment/result.h"
#include <QTimer>
#include <QMutex>
#include "experimentspropertiescontroller.h"

namespace Ui {
    class ExperimentCtrl;
}

namespace GeneLabCore {

    class ExperimentCtrl : public QWidget
    {
        Q_OBJECT

    public:
        explicit ExperimentCtrl(QWidget *parent = 0);
        ~ExperimentCtrl();

        void connectToInspectorInputManager(GeneLabCore::InspectorsInputManager * iim);

    signals:
        void addEntity(QVariantMap genome, GeneLabCore::Ressource* r);
        void newDataAvailable();

    public slots:

        void loadExperiment(Experiment*);

    protected slots:

        void refresh();
        void refreshUI();
        void toggleRefresh();
        void refreshInProgress();
        void openExperimentPropertiesController();

    private:
        Ui::ExperimentCtrl *ui;
        Experiment* experiment;
        ResultsManager* resultsManager;
        ResultsManager* oldResultsManager;
        QList<Result*> results;
        QTimer* autorefresh;
        bool loaded;
        QMutex lock;

        ExperimentsPropertiesController *epc;

private slots:
    void on_btnLoad_clicked();
};

}

#endif // EXPERIMENTCTRL_H
