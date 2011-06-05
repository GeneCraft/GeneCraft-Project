#ifndef FIXATIONPROPERTIES_H
#define FIXATIONPROPERTIES_H

#include <QWidget>
#include <QListWidgetItem>

#include "genelabcoreclasses.h"
#include "sensor.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

using namespace GeneLabCore;

namespace Ui {
    class FixationProperties;
}

class FixationProperties : public QWidget
{
    Q_OBJECT

public:
    explicit FixationProperties(QWidget *parent = 0);
    ~FixationProperties();

    void setFixation(Fixation *fixation);
    void setFormTitle(QString title);

signals:

    void rigidBodySelected(btRigidBody *);

public slots:

    void addBone();
    void addSensor();
    void fixInTheAir();
    void setPosition();

private:
    Ui::FixationProperties *ui;

    Fixation *fixation;
};

#endif // FIXATIONPROPERTIES_H
