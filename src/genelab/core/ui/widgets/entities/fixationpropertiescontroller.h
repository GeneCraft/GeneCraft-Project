#ifndef FIXATIONPROPERTIESCONTROLLER_H
#define FIXATIONPROPERTIESCONTROLLER_H

#include <QWidget>
#include <QListWidgetItem>

#include "genelabcoreclasses.h"
#include "sensors/sensor.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

using namespace GeneLabCore;

namespace Ui {
    class FixationPropertiesController;
}

class FixationPropertiesController : public QWidget
{
    Q_OBJECT

public:
    explicit FixationPropertiesController(QWidget *parent = 0);
    ~FixationPropertiesController();
    void connectToInspectorInputManager(InspectorsInputManager *iim);

signals:

    void rigidBodySelected(btRigidBody *);
    void sBoneDeleted(Bone* bone);
    void sBoneSelected(Bone *);
    void sFixationUpdated(Fixation *fixation);

public slots:

    void setFixation(Fixation *fixation);

    void addBone();
    void addSensor();
    void addEffector();

    void selectBone();

    void removeSelectedBone();
    void removeSelectedSensor();
    void removeSelectedEffector();

    void fixInTheAir();
    void changeRadiusFromSlider(int value);
    void changeRadiusFromButton();

    // Notifications
    void boneSelected(Bone *);
    void fixationDeleted(Fixation * fixation);
    void entityDeleted(Entity *entity);

private:
    Ui::FixationPropertiesController *ui;

    Fixation *fixation;
};

#endif // FIXATIONPROPERTIESCONTROLLER_H
