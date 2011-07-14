#ifndef FLOATMUTATIONCONTROLLER_H
#define FLOATMUTATIONCONTROLLER_H

#include <QWidget>

namespace Ui {
    class FloatMutationController;
}

class FloatMutationController : public QWidget
{
    Q_OBJECT

public:
    explicit FloatMutationController(QString name, QWidget *parent = 0);
    ~FloatMutationController();
public slots:
    void probabilityChanged(int value);
    void minFactorChanged(int value);
    void maxFactorChanged(int value);
    void minValueChanged(int value);
    void maxValueChanged(int value);

private:
    Ui::FloatMutationController *ui;
};

#endif // FLOATMUTATIONCONTROLLER_H
