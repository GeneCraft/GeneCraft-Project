#ifndef BRAINPROPERTIESCONTROLLER_H
#define BRAINPROPERTIESCONTROLLER_H

#include <QWidget>

#include "bodyitems.h"
#include "genelabcoreclasses.h"

using namespace GeneLabCore;

namespace Ui {
    class BrainPropertiesController;
}

class BrainPropertiesController : public QWidget
{
    Q_OBJECT

public:
    explicit BrainPropertiesController(QWidget *parent = 0);
    ~BrainPropertiesController();

public slots:
    void selectSensorFixation();
    void setBrainSize();
    void clearSensors();
    void clearEffectors();
    void computeMinimalOuts();

    void setEntity(Entity *entity);
    void setBrainViz(PlugGridVisualizer* brainViz);
    void setBrainDesignViz(PlugGridDesignVisualizer* brainViz);

private:
    Ui::BrainPropertiesController *ui;
    Entity *entity;

    PlugGridVisualizer* brainViz;
    PlugGridDesignVisualizer* brainDezViz;
};

#endif // BRAINPROPERTIESCONTROLLER_H
