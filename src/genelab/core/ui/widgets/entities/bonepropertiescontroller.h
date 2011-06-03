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

class BonePropertiesController : public QWidget
{
    Q_OBJECT

public:
    explicit BonePropertiesController(QWidget *parent = 0);
    ~BonePropertiesController();

public slots:

    void setBone(Bone * bone);

private:
    Ui::BonePropertiesController *ui;

    Bone *bone;

private slots:

    void saveChanges();
    void deleteBone();
    void randomValues();
    void resetMotors();
    void setOutFrom();
};

#endif // BONEPROPERTIESCONTROLLER_H
