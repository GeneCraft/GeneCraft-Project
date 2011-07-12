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

class FixationProperties : public QWidget
{
    Q_OBJECT

public:
    explicit FixationProperties(QWidget *parent = 0);
    ~FixationProperties();

    void setFixation(Fixation *fixation);

signals:

    void rigidBodySelected(btRigidBody *);
    void boneDeleted(Bone* bone);
    void fixationDeleted(Fixation* fixation);

public slots:

    void addBone();
    void addSensor();
    void fixInTheAir();
    void setPosition();
    void selectBone();
    void removeSelectedBone();
    void removeSelectedSensor();

    void changeRadiusFromSlider(int value);
    void changeRadiusFromButton();

private:
    Ui::FixationPropertiesController *ui;

    Fixation *fixation;
};

#endif // FIXATIONPROPERTIESCONTROLLER_H
