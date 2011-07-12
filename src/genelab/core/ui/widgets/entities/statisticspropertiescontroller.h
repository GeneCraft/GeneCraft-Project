#ifndef STATISTICSPROPERTIESCONTROLLER_H
#define STATISTICSPROPERTIESCONTROLLER_H

#include <QWidget>
#include <QTimer>
#include "genelabcoreclasses.h"

using namespace GeneLabCore;

namespace Ui {
    class StatisticsPropertiesController;
}

class StatisticsPropertiesController : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsPropertiesController(QWidget *parent = 0);
    ~StatisticsPropertiesController();

public slots:

    void setEntity(Entity *entity);
    void updateStats();
    void resetAllStats();
    void resetSelectedStat();

private:
    Ui::StatisticsPropertiesController *ui;

    Entity *entity;

    QTimer *statsTimer;
};

#endif // STATISTICSPROPERTIESCONTROLLER_H
