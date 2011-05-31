#ifndef BRAINNODE_H
#define BRAINNODE_H

#include <QObject>
#include "genelabcoreclasses.h"



namespace GeneLabCore {

enum NodeType {
    // Input
    IN,
    CONST,

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

    // MemorySpace used by all memory node
    MEMORY_SPACE,
    BAD_TYPE

};

QString fromType(NodeType type);
NodeType fromString(QString string);

class BrainNode : public QObject {
    Q_OBJECT
public:
    explicit BrainNode() {}

    explicit BrainNode(NodeType type) {
        this->type = type;
    }

    NodeType type;

signals:

public slots:

protected:
    QList<BrainNode*> childs;

};

class BrainNodeIn : public BrainNode {
    Q_OBJECT
public:
    explicit BrainNodeIn(int x, int y) {
        this->type = IN;
        this->x = x;
        this->y = y;
    }

    NodeType type;
    int x, y;

signals:

public slots:
};

class BrainNodeConst : public BrainNode {
    Q_OBJECT
public:
    explicit BrainNodeConst(float constant) {
        this->type = CONST;
        this->value = constant;
    }

    NodeType type;
    float value;

signals:

public slots:
};


class BrainMemory : public BrainNode {
    Q_OBJECT
public:
    explicit BrainMemory(int size) {
        this->type = MEMORY_SPACE;
        this->size = size;
        this->mem = new float[size];
    }
    ~BrainMemory() {
        delete this->mem;
    }

    NodeType type;
    int size;
    float* mem;

signals:

public slots:
};

}

#endif // BRAINNODE_H
