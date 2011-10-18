#ifndef INTEGERMUTATIONCONTROLLER_H
#define INTEGERMUTATIONCONTROLLER_H

#include <QWidget>

#include "genecraftcoreclasses.h"

namespace Ui {
    class IntegerMutationController;
}

class IntegerMutationController : public QWidget
{
    Q_OBJECT

public:
    explicit IntegerMutationController(QString name, QWidget *parent = 0);
    IntegerMutationController(GeneCraftCore::IntegerMutation *mutation, QString name, QWidget *parent = 0);
    ~IntegerMutationController();
public slots:

    void save();
    void nameToggled(bool checked);
    void probabilityChanged(int value);
    void minFactorChanged(int value);
    void maxFactorChanged(int value);
//    void minValueChanged(int value);
//    void maxValueChanged(int value);

private:
    Ui::IntegerMutationController *ui;

    void createForm(QString name);

    GeneCraftCore::IntegerMutation *mutation;
};

#endif // INTEGERMUTATIONCONTROLLER_H