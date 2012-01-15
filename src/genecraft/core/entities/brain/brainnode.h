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

#ifndef BRAINNODE_H
#define BRAINNODE_H

#include <QObject>
#include "genecraftcoreclasses.h"

#include <QDebug>


namespace GeneCraftCore {

enum NodeType {
    // Input
    INPUT,
    CONSTANT,

    // 2 operands
    SUM,
    PRODUCT,
    DIVIDE,
    ATAN,
    // 2 operands + decisions
    THRESOLD,
    GT,
    // 3 operands
    IFELSE,

    // 1 operand
    COS,
    SIN,
    ABS,
    SIGN_OF,
    LOG,
    EXP,
    SIGM,

    // Memory
    INTEGRATE,
    INTERPOLATE,
    DIFFERENTIATE,
    MEMORY,
    SMOOTH,
    MIN,
    MAX,
    SINUS,
    WAVE,

    // MemorySpace used by all memory node
    MEMORY_SPACE,
    BAD_TYPE

};

QString fromType(NodeType type);
NodeType fromString(QString string);

class BrainNode : public QObject {

public:
    explicit BrainNode() {}

    explicit BrainNode(NodeType type) {
        this->type = type;
    }

    NodeType type;


protected:
    QList<BrainNode*> childs;

};

class BrainNodeIn : public BrainNode {

public:
    explicit BrainNodeIn(btScalar x, btScalar y) : BrainNode(INPUT) {
        this->x = x;
        this->y = y;
    }

    btScalar x, y;

};

class BrainNodeConst : public BrainNode {

public:
    explicit BrainNodeConst(btScalar constant) : BrainNode(CONSTANT) {
        this->value = constant;
    }

    btScalar value;

};


class BrainMemory : public BrainNode {

public:
    explicit BrainMemory(int size);
    void insert(btScalar value);
    ~BrainMemory() {
    }

    int size;
    int cpt;
    QList<btScalar> mem;

};

}

#endif // BRAINNODE_H
