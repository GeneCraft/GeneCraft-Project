#ifndef FLOATMUTATIONCONTROLLER_H
#define FLOATMUTATIONCONTROLLER_H

#include <QWidget>
#include "genelabcoreclasses.h"

namespace Ui {
    class FloatMutationController;
}

class FloatMutationController : public QWidget
{
    Q_OBJECT

public:
    FloatMutationController(GeneLabCore::FloatMutation *mutation, QString name, QWidget *parent = 0);
    ~FloatMutationController();

    void createForm(QString name);

//    void setProbability(float probability);
//    float getProbability();

//    void setMinFactor(float minFactor);
//    float getMinFactor();

//    void setMaxFactor(float maxFactor);
//    float getMaxFactor();

public slots:

    void save();
    void nameToggled(bool checked);
    void probabilityChanged(int value);
    void minFactorChanged(int value);
    void maxFactorChanged(int value);
//    void minValueChanged(int value);
//    void maxValueChanged(int value);

private:
    Ui::FloatMutationController *ui;

    GeneLabCore::FloatMutation *mutation;
};

#endif // FLOATMUTATIONCONTROLLER_H
