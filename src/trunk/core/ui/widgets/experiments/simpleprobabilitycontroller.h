#ifndef SIMPLEPROBABILITYCONTROLLER_H
#define SIMPLEPROBABILITYCONTROLLER_H

#include <QWidget>

#include "genecraftcoreclasses.h"

namespace Ui {
    class SimpleProbabilityController;
}

class SimpleProbabilityController : public QWidget
{
    Q_OBJECT

public:
    explicit SimpleProbabilityController(GeneCraftCore::SimpleProbabilityMutation *mutation,QString name, QWidget *parent = 0);
    ~SimpleProbabilityController();

public slots:
    void save();
    void nameToggled(bool checked);
    void probabilityChanged(int value);

private:
    Ui::SimpleProbabilityController *ui;

    GeneCraftCore::SimpleProbabilityMutation *mutation;
};

#endif // SIMPLEPROBABILITYCONTROLLER_H
