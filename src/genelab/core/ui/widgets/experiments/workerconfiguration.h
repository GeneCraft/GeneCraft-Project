#ifndef WORKERCONFIGURATION_H
#define WORKERCONFIGURATION_H

#include <QVariantMap>
#include <QWidget>

namespace Ui {
    class WorkerConfiguration;
}

class WorkerConfiguration : public QWidget
{
    Q_OBJECT

public:
    explicit WorkerConfiguration(QVariant worker, QWidget *parent = 0);
    ~WorkerConfiguration();

    QVariant getWorkerData();
    bool isValidated();

public slots:
    void valid();
    void reset();

private:

    void init(QVariantMap worker);
    Ui::WorkerConfiguration *ui;
    bool validated;
};

#endif // WORKERCONFIGURATION_H
