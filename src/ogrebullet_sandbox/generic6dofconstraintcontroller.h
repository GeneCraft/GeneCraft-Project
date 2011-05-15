#ifndef GENERIC6DOFCONSTRAINTCONTROLLER_H
#define GENERIC6DOFCONSTRAINTCONTROLLER_H

#include <QWidget>
#include <QDebug>
#include "btBulletDynamicsCommon.h"

namespace Ui {
    class Generic6DofConstraintController;
}

class Generic6DofConstraintController : public QWidget
{
    Q_OBJECT

public:
    explicit Generic6DofConstraintController(QWidget *parent = 0);
    ~Generic6DofConstraintController();
    void setConstraint(btGeneric6DofConstraint * ct);

private:
    Ui::Generic6DofConstraintController *ui;

    btGeneric6DofConstraint *constraint;

private slots:
    void saveChanges();
};

#endif // GENERIC6DOFCONSTRAINTCONTROLLER_H
