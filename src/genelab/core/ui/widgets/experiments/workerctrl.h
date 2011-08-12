#ifndef WORKERCTRL_H
#define WORKERCTRL_H

#include <QWidget>
#include <QProcess>

#include "experiment/experiment.h"

namespace Ui {
    class WorkerCtrl;
}

namespace GeneCraftCore {

class WorkerCtrl : public QWidget
{
    Q_OBJECT

public:
    explicit WorkerCtrl(QWidget *parent = 0);
    ~WorkerCtrl();

    void connectToInspectorInputManager(InspectorsInputManager * iim);

public slots:
    void setExperiment(Experiment* exp);

private:
    Ui::WorkerCtrl *ui;
    QProcess* process;
    Experiment* exp;

private slots:
    void on_btnStart_clicked();
    void readyRead();

};
}

#endif // WORKERCTRL_H
