#include "workerctrl.h"
#include "ui_workerctrl.h"

#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QProcess>

#include "ressources/jsonfile.h"
#include "events/inspectorsinputmanager.h"

namespace GeneLabCore {

    WorkerCtrl::WorkerCtrl(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::WorkerCtrl)
    {
        ui->setupUi(this);
        process = NULL;
        exp = NULL;

        setEnabled(false);
    }

    WorkerCtrl::~WorkerCtrl()
    {
        if(process && process->state() == QProcess::Running) {
            process->kill();
            delete process;
        }
        delete ui;
    }

    void WorkerCtrl::connectToInspectorInputManager(InspectorsInputManager * iim) {

        connect(iim,SIGNAL(sLoadExperiment(Experiment*)),this,SLOT(setExperiment(Experiment*)));
    }

    void WorkerCtrl::setExperiment(Experiment *exp) {
        this->exp = exp;

        setEnabled((bool)exp);

        if(exp) {
            this->ui->label->setText("Experiment : " + exp->getId());
        }
    }

    void WorkerCtrl::on_btnStart_clicked()
    {
        if(!this->exp)
            return;

        if(this->process) {
            this->process->kill();
            this->process->deleteLater();
            this->process = NULL;
            this->ui->btnStart->setText("Start worker");
            return;
        }


        QString workerExe = "./genecraft_worker.exe";
        //QString workerExe = "/Users/cyprienhuissoud/Desktop/genelab/genelab/src/genelab_worker-build-desktop/genelab_worker";
        QFile workerFile(workerExe);
        if(!workerFile.exists()) {
            QString workerExe  = QFileDialog::getOpenFileName(this, "Select the worker binary","genelab_worker");
            workerFile.setFileName(workerExe);
        }

        QString expFile;
        if(exp->isOnline()) {
            expFile = exp->getId();
        } else if(exp->hasRessource()) {
            expFile = QFileInfo(((JsonFile*)exp->getRessource())->filename).absoluteFilePath();
        } else {
            expFile = QFileDialog::getOpenFileName(this, "Select the experience file","Experience (*.exp)");
        }

        process = new QProcess();
        connect(process, SIGNAL(readyReadStandardError()), this, SLOT(readyRead()));
        QFileInfo workerFileInfo(workerFile);
        QStringList params;
        params << "--gui" << expFile;
        QDir workerDir = QDir(".");//workerFileInfo.absoluteDir();
        process->setWorkingDirectory(workerDir.absolutePath());
        process->setReadChannel(QProcess::StandardError);
        process->start(workerFileInfo.absoluteFilePath(), params);
        this->ui->btnStart->setText("Stop worker");
    }

    void WorkerCtrl::readyRead() {
        // Suppression au bout d'un moment
        // TODO : Remove static
        static int readyRead = 0;
        readyRead++;
        if(readyRead%200 == 0) {
            this->ui->txtOut->clear();
        }
        // Ajout du text Ã  la sortie de la console
        if(!process)
            return;
        QString data = process->readAllStandardError();
        this->ui->txtOut->append(data.left(data.size()-1));
    }

}
