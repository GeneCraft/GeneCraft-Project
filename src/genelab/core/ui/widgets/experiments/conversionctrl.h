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
