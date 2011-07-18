#include "workerctrl.h"
#include "ui_workerctrl.h"

#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QProcess>

WorkerCtrl::WorkerCtrl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkerCtrl)
{
    ui->setupUi(this);
    process = NULL;
}

WorkerCtrl::~WorkerCtrl()
{
    if(process && process->state() == QProcess::Running) {
        process->kill();
        delete process;
    }
    delete ui;
}

void WorkerCtrl::on_btnStart_clicked()
{
    if(this->process)
        return;

    //QString workerExe = "/Users/cyprienhuissoud/Desktop/genelab/genelab/src/genelab_worker-build-desktop/genelab_worker";
    QString workerExe  = QFileDialog::getOpenFileName(this, "Select the worker binary","genelab_worker");
    QString expFile    = QFileDialog::getOpenFileName(this, "Select the experience file","Experience (*.exp)");
    QString workerParams = QFileDialog::getOpenFileName(this, "Select the worker file","Worker (*.worker)");
    qDebug() << workerExe << expFile << workerParams;
    process = new QProcess();
    connect(process, SIGNAL(readyReadStandardError()), this, SLOT(readyRead()));
    QFile workerFile(workerExe);
    QFileInfo workerFileInfo(workerFile);
    QStringList params;
    params << expFile << workerParams;
    QDir workerDir = workerFileInfo.absoluteDir();
    process->setWorkingDirectory(workerDir.absolutePath());
    process->setReadChannel(QProcess::StandardError);
    process->start(workerExe, params);
    qDebug() << process->state();
    this->ui->btnStart->setEnabled(false);
}
void WorkerCtrl::readyRead() {
    // Suppression au bout d'un moment
    static int readyRead = 0;
    readyRead++;
    if(readyRead%200 == 0) {
        this->ui->txtOut->clear();
    }
    // Ajout du text à la sortie de la console
    QString data = process->readAllStandardError();
    this->ui->txtOut->append(data.left(data.size()-1));
}
