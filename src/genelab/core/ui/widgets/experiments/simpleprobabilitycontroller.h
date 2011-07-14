#ifndef SIMPLEPROBABILITYCONTROLLER_H
#define SIMPLEPROBABILITYCONTROLLER_H

#include <QWidget>

#include "genelabcoreclasses.h"

namespace Ui {
    class SimpleProbabilityController;
}

class SimpleProbabilityController : public QWidget
{
    Q_OBJECT

public:
    explicit SimpleProbabilityController(GeneLabCore::SimpleProbabilityMutation *mutation,QString name, QWidget *parent = 0);
    ~SimpleProbabilityController();

public slots:
    void save();
    void nameToggled(bool checked);
    void probabilityChanged(int value);

private:
    Ui::SimpleProbabilityController *ui;

    GeneLabCore::SimpleProbabilityMutation *mutation;
};

#endif // SIMPLEPROBABILITYCONTROLLER_H
