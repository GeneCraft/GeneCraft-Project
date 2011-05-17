#ifndef FIXATIONPROPERTIES_H
#define FIXATIONPROPERTIES_H

#include <QWidget>
#include "genelabcoreclasses.h"

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

public slots:

    void addBone();
    void fixInTheAir();
    void setPosition();

private:
    Ui::FixationProperties *ui;

    Fixation *fixation;
};

#endif // FIXATIONPROPERTIES_H
