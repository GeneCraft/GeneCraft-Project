#ifndef BRAINPROPERTIESCONTROLLER_H
#define BRAINPROPERTIESCONTROLLER_H

#include <QWidget>

#include "bodyitems.h"
#include "genecraftcoreclasses.h"

using namespace GeneCraftCore;

namespace Ui {
    class BrainPropertiesController;
}

class BrainPropertiesController : public QWidget
{
    Q_OBJECT

public:
    explicit BrainPropertiesController(QWidget *parent = 0);
    ~BrainPropertiesController();
    void connectToInspectorInputManager(InspectorsInputManager *iim);


public slots:

    void selectSensorFixation();
    void setBrainFrequency();
    void clearSensors();
    void clearEffectors();
    void computeMinimalOuts();

    void setEntity(Entity *entity);
    void entityUpdated(Entity *entity);
    void entityDeleted(Entity *entity);

    void refresh();
    void sensorsSelected(QList<Sensor*>);

    void setBrainViz(PlugGridVisualizer* brainViz);
    void setBrainDesignViz(PlugGridDesignVisualizer* brainViz);

signals:

    void sEntityUpdated(Entity *entity);
    void sFixationSelected(Fixation *fixation);
    void sFixationUpdated(Fixation *fixation);
    void sBoneSelected(Bone *bone);

private:
    Ui::BrainPropertiesController *ui;
    Entity *entity;

    PlugGridVisualizer* brainViz;
    PlugGridDesignVisualizer* brainDezViz;
};

#endif // BRAINPROPERTIESCONTROLLER_H
