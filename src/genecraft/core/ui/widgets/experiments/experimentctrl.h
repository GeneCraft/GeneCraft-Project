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
