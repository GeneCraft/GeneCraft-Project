#ifndef BONEPROPERTIESCONTROLLER_H
#define BONEPROPERTIESCONTROLLER_H

#include <QWidget>
#include "bodyitems.h"
#include "genelabcoreclasses.h"
#include "sensors/sensor.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

using namespace GeneLabCore;

namespace Ui {
    class BonePropertiesController;
}

class BonePropertiesController : public QWidget
{
    Q_OBJECT

public:
    explicit BonePropertiesController(QWidget *parent = 0);
    ~BonePropertiesController();
    void connectToInspectorInputManager(InspectorsInputManager * iim);

signals:

    void rigidBodySelected(btRigidBody *);
    void sBoneDeleted(Bone *);

public slots:

    void setBone(Bone * bone);
    void boneDeleted(Bone *bone);
    void entityDeleted(Entity *entity);
    void update();

private:
    Ui::BonePropertiesController *ui;

    Bone *bone;

private slots:

    void saveChanges();
    void deleteBone();
    void randomValues();
    void resetMotors();
    void setOutFrom();
    void changeSize();
    void changeLengthFromSlider(int value);
    void changeRadiusFromSlider(int value);
    void rigidBodySelectedFromFix(btRigidBody*);
    void validateAngularInputs();

    void cbEffectorX_stateChanged(int value);
    void cbEffectorY_stateChanged(int value);
    void cbEffectorZ_stateChanged(int value);
};

#endif // BONEPROPERTIESCONTROLLER_H
