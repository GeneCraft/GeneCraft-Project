#include "brainfunctional.h"
#include "brainnode.h"
#include <QStringList>

#include <QDebug>

namespace GeneLabCore {
    BrainFunctional::BrainFunctional(int plugGridSize, QObject *parent) :
        Brain(plugGridSize, parent)
    {
    }

    void BrainFunctional::addOut(BrainOut *out, QString treeData) {
        QList<BrainNode*> tree = QList<BrainNode*>();
        QStringList nodes = treeData.split(",");
        for(int i = 0; i < nodes.length(); i++) {
            QString node = nodes[i];
            QStringList nodePart = node.split(" ");
            NodeType t = fromString(nodePart[0]);
            switch(t) {
            // 2 operands
            case SUM:
            case PRODUCT:
            case DIVIDE:
            case ATAN:
            // 2 operands + decisions
            case THRESOLD:
            case GT:
            // 3 operands
            case IFELSE:

            // 1 operand
            case COS:
            case SIN:
            case ABS:
            case SIGN_OF:
            case LOG:
            case EXP:
            case SIGM:
                tree.append(new BrainNode(t));
                break;
            case IN:
                tree.append(new BrainNodeIn(nodePart[1].toInt(), nodePart[2].toInt()));
                break;
            case CONST:
                tree.append(new BrainNodeConst(nodePart[1].toInt()));
                break;
            case INTEGRATE:
            case INTERPOLATE:
            case DIFFERENTIATE:
            case MEMORY:
            case SMOOTH:
            case MIN:
            case MAX:
                tree.append(new BrainNode(t));
                tree.append(new BrainMemory(nodePart[1].toInt()));
                break;
            case SINUS:
                tree.append(new BrainNode(SINUS));
                tree.append(new BrainMemory(1));
                break;
            case MEMORY_SPACE:
            case BAD_TYPE:
                qDebug() << "SHOULD NOT BE IN STRING memoryspace or badtype !!";
                break;

            }
        }
    }

    void BrainFunctional::step() {

    }

    void BrainFunctional::doNode(QList<BrainNode*> tree, BrainOut* out) {

    }

    float BrainFunctional::value(BrainNode *node) {

    }

}
