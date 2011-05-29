#ifndef BONEPROPERTIESCONTROLLER_H
#define BONEPROPERTIESCONTROLLER_H

#include <QWidget>
#include <QListWidgetItem>
#include "genelabcoreclasses.h"
#include "sensor.h"

using namespace GeneLabCore;

namespace Ui {
    class BonePropertiesController;
}


class SensorListWidgetItem : public QListWidgetItem
{
public:

    SensorListWidgetItem(Sensor * sensor)
    {
        this->sensor = sensor;
        this->setText(sensor->getTypeName());
    }

    Sensor *sensor;
};

class BonePropertiesController : public QWidget
{
    Q_OBJECT

public:
    explicit BonePropertiesController(QWidget *parent = 0);
    ~BonePropertiesController();

    void setBone(Bone * bone);

private:
    Ui::BonePropertiesController *ui;

    Bone *bone;

private slots:

    void saveChanges();
    void deleteBone();
    void randomValues();
    void resetMotors();

    void addBone();
    void addSensor();
    void fixInTheAir();
    void setPosition();

};

#endif // BONEPROPERTIESCONTROLLER_H
