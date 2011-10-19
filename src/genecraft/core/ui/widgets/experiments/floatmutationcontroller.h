#ifndef FLOATMUTATIONCONTROLLER_H
#define FLOATMUTATIONCONTROLLER_H

#include <QWidget>
#include "genecraftcoreclasses.h"

namespace Ui {
    class FloatMutationController;
}

class FloatMutationController : public QWidget
{
    Q_OBJECT

public:
    FloatMutationController(GeneCraftCore::FloatMutation *mutation, QString name, QWidget *parent = 0);
    ~FloatMutationController();

    void createForm(QString name);
    GeneCraftCore::FloatMutation *mutation;

public slots:

    void save();
    void nameToggled(bool checked);
    void probabilityChanged(int value);
    void sigmaChanged(int value);
    void meanChanged(int value);


private:
    Ui::FloatMutationController *ui;

};

#endif // FLOATMUTATIONCONTROLLER_H
