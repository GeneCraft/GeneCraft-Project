#ifndef WORKERCTRL_H
#define WORKERCTRL_H

#include <QWidget>
#include <QProcess>

namespace Ui {
    class WorkerCtrl;
}

class WorkerCtrl : public QWidget
{
    Q_OBJECT

public:
    explicit WorkerCtrl(QWidget *parent = 0);
    ~WorkerCtrl();

private:
    Ui::WorkerCtrl *ui;
    QProcess* process;

private slots:
    void on_btnStart_clicked();
    void readyRead();

};

#endif // WORKERCTRL_H
