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

#ifndef BRAINFUNCTIONAL_H
#define BRAINFUNCTIONAL_H

#include "genecraftcoreclasses.h"
#include "brain.h"
#include "brainnode.h"

#include <QMap>
#include <QVariant>
#include <QList>

namespace GeneCraftCore {
class BrainFunctional : public Brain
{

public:
    explicit BrainFunctional(QObject *parent = 0);
    BrainFunctional(QVariant data);
    ~BrainFunctional();

    void addOut(BrainOut* out);
    void removeOut(BrainOut* out);

    QList<BrainNodeIn*> getBrainNodeIn() {
        return brainins;
    }

    static QString createRandomFunc(int depth, StructuralList* nodesList = NULL);

    virtual QVariant serialize();

    virtual void step();

protected:
    void doNode(QList<BrainNode*> tree, BrainOut* out);
    btScalar apply(QList<BrainNode*>::iterator& it, QList<BrainNode*>::const_iterator end);

    QList<BrainOut*> outputs;
    QList<QList<BrainNode*> > trees;

    QList<BrainNodeIn*> brainins;

    PlugGridVisualizer * viz;

};
}

#endif // BRAINFUNCTIONAL_H
