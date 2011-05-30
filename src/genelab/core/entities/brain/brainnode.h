#ifndef BRAINNODE_H
#define BRAINNODE_H

#include <QObject>
#include "genelabcoreclasses.h"



namespace GeneLabCore {


enum NodeType {
    IN,
    SUM,
    PRODUCT,
    DIVIDE,
    THRESOLD,
    GT,
    LT,
    SIGN_OF,
    MIN,
    MAX,
    ABS,
    IF,
    INTERPOLATE,
    SIN,
    COS,
    ATAN,
    LOG,
    EXPT,
    SIGMOIDE,
    INTEGRATE,
    DIFFERENTIATE,
    SMOOTH,
    MEMORY,
    OSCILLATE_WAV,
    OSCILLATE_SAW,
    SINUS
};

class BrainNode : public QObject {
    Q_OBJECT
public:
    explicit BrainNode() {}

    explicit BrainNode(NodeType type,
                       QList<BrainNode*> operands) {
        this->type = type;
        this->childs = operands;
    }

    NodeType type;

signals:

public slots:

protected:
    QList<BrainNode*> childs;

};

class BrainNodeIn : BrainNode {
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

}

#endif // BRAINNODE_H
