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

    // To connect inspector input manager to be notified if the entity is deleted
    void connectToInspectorInputManager(InspectorsInputManager *iim);

public slots:

    void setEntity(Entity *entity);
    void updateStats();
    void resetAllStats();
    void resetSelectedStat();

    void entityDeleted(Entity *entity);

private:
    Ui::StatisticsPropertiesController *ui;

    Entity *entity;

    QTimer *statsTimer;
};

#endif // STATISTICSPROPERTIESCONTROLLER_H
