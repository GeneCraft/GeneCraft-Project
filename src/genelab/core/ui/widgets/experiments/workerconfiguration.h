#ifndef WORKERCONFIGURATION_H
#define WORKERCONFIGURATION_H

#include <QWidget>

namespace Ui {
    class WorkerConfiguration;
}

class WorkerConfiguration : public QWidget
{
    Q_OBJECT

public:
    explicit WorkerConfiguration(QWidget *parent = 0);
    ~WorkerConfiguration();

    QVariant getWorkerData();

private:
    Ui::WorkerConfiguration *ui;
};

#endif // WORKERCONFIGURATION_H
