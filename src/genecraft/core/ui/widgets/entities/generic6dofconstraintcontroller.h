/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

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
