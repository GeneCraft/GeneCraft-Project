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

#ifndef STRUCTURALMUTATIONCONTROLLER_H
#define STRUCTURALMUTATIONCONTROLLER_H

#include <QWidget>
#include "genecraftcoreclasses.h"

#include "mutationelementcontroller.h"

namespace Ui {
    class StructuralMutationController;
}

class StructuralMutationController : public QWidget
{
    Q_OBJECT

public:
    explicit StructuralMutationController(GeneCraftCore::StructuralMutation *mutation,QString name,
                                          GeneCraftCore::StructuralList *list = NULL, QWidget *parent = 0);
    ~StructuralMutationController();

public slots:

    void save();
    void nameToggled(bool checked);
    void addProbabilityChanged(int value);
    void removeProbabilityChanged(int value);
    void replaceProbabilityChanged(int value);

private:
    Ui::StructuralMutationController *ui;

    GeneCraftCore::StructuralMutation *mutation;
    GeneCraftCore::StructuralList *list;
    QList<MutationElementController *> mecs;
};

#endif // STRUCTURALMUTATIONCONTROLLER_H
