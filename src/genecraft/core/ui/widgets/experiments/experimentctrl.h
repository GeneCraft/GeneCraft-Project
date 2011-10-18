#ifndef EXPERIMENTCTRL_H
#define EXPERIMENTCTRL_H

#include <QWidget>
#include "experiment/experiment.h"
#include "experiment/resultsmanager.h"
#include "experiment/result.h"
#include <QTimer>
#include <QMutex>
#include "experimentspropertiescontroller.h"
#include "conversionctrl.h"

namespace Ui {
    class ExperimentCtrl;
}

namespace GeneCraftCore {

    class ExperimentCtrl : public QWidget
    {
        Q_OBJECT

    public:
        explicit ExperimentCtrl(QWidget *parent = 0);
        ~ExperimentCtrl();

        void connectToInspectorInputManager(GeneCraftCore::InspectorsInputManager * iim);

    signals:
        void sAddEntity(QVariantMap genome, Ressource* r);
        void sLoadResult(Result*);
        void newDataAvailable();

    public slots:

        void loadExperiment(Experiment*);

    protected slots:

        void refresh();
        void refreshUI();
        void toggleRefresh();
        void refreshInProgress();
        void openExperimentPropertiesController();
        void newExperiment();
        void deleteAllResults();
        void openConvertWidget();

    private:
        Ui::ExperimentCtrl *ui;
        Experiment* experiment;
        ResultsManager* resultsManager;
        ResultsManager* oldResultsManager;
        QList<Result*> results;
        QTimer* autorefresh;
        bool loaded;
        QMutex lock;

        ConversionCtrl *conversionCtrl;

        ExperimentsPropertiesController *epc;

    private slots:
    void on_btnHelp_clicked();
    void on_btnAdd_clicked();
    void on_btnLoad_clicked();
};

}

#endif // EXPERIMENTCTRL_H