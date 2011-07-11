#ifndef BRAINNODE_H
#define BRAINNODE_H

#include <QObject>
#include "genelabcoreclasses.h"

#include <QDebug>


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
    explicit BrainNodeIn(float x, float y) : BrainNode(IN) {
        this->x = x;
        this->y = y;
    }

    float x, y;

};

class BrainNodeConst : public BrainNode {

public:
    explicit BrainNodeConst(float constant) : BrainNode(CONST) {
        this->value = constant;
    }

    float value;

};


class BrainMemory : public BrainNode {

public:
    explicit BrainMemory(int size) : BrainNode(MEMORY_SPACE){
        if(size <= 0) {
            qDebug() << "size of 0 or less ! bad" << size;
            size = 1;
        }
        this->size = size;
        for(int i = 0; i < size; i++) {
            this->insert(0);
        }
    }

    void insert(float value) {
        mem.append(value);
        if(mem.size() > size)
            mem.removeFirst();
    }

    ~BrainMemory() {
    }

    int size;
    int cpt;
    QList<float> mem;

};

}

#endif // BRAINNODE_H


// +, +, IN 3 5, CONST 3.14, INTEGRATE 10, IN 10 10
