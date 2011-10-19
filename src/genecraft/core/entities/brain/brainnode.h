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
