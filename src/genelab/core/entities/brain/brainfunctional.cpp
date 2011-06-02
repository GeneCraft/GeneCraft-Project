#include "brainfunctional.h"
#include "brainnode.h"
#include "brainout.h"
#include "brainpluggrid.h"

#include <math.h>
#include <cstdlib>

#include <QStringList>

#include <QDebug>


namespace GeneLabCore {

float sigmoid(float x)
{
     float exp_value;
     float return_value;

     /*** Exponential calculation ***/
     exp_value = exp((double) -3*x);

     /*** Final sigmoid value ***/
     return_value = 1 / (1 + exp_value);

     return return_value;
}


    BrainFunctional::BrainFunctional(int plugGridSize, QObject *parent) :
        Brain(plugGridSize, parent)
    {
    }

    void BrainFunctional::addOut(BrainOut *out, QString treeData) {
        QList<BrainNode*> tree = QList<BrainNode*>();
        QStringList nodes = treeData.split(",", QString::SkipEmptyParts);
        for(int i = 0; i < nodes.length(); i++) {
            QString node = nodes[i];
            QStringList nodePart = node.split(" ", QString::SkipEmptyParts);
            NodeType t = fromString(nodePart[0]);
            qDebug() << t;
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
                tree.append(new BrainNodeConst(nodePart[1].toFloat()));
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

        for(int i = 0; i < tree.size(); i++) {
            qDebug() << fromType(tree[i]->type);
        }
        this->trees.append(tree);
        this->outputs.append(out);
    }

    void BrainFunctional::step() {
        this->plugGrid->beforeStep();
        for(int i = 0; i < trees.size(); i++) {
            this->doNode(trees[i], outputs[i]);
        }
        this->plugGrid->afterStep();

    }

    void BrainFunctional::doNode(QList<BrainNode*> tree, BrainOut* out) {
        QList<BrainNode*>::iterator it = tree.begin();
        float value = apply(it, tree.end());
        //if(value != 0)
        //    qDebug() << value;
        out->setValue(value);
    }

    float BrainFunctional::apply(QList<BrainNode*>::iterator it, QList<BrainNode*>::const_iterator end) {
        if(it == end) {
            return 0;
        }

        BrainNode* n = *it;
        BrainMemory* m;
        it++;
        float min, max, a, b, first, second, c;
        switch(n->type) {
        // 2 operands
        case SUM:
            return apply(it, end) + apply(it, end);

        case PRODUCT:
            return apply(it, end) * apply(it, end);

        case DIVIDE:
            a = apply(it, end);
            b = apply(it, end);

            if(b != 0)
                return a/b;
            else
                return -999;

        case ATAN:
            return atan2(apply(it, end), apply(it, end));

        // 2 operands + decisions
        case THRESOLD:
            a = apply(it, end);
            b = apply(it, end);
            if(b > a)
                return b;

            return 0;

        case GT:
            a = apply(it, end);
            b = apply(it, end);
            c = apply(it, end);

            if(a > b)
                return c;

            return 0;

        // 3 operands
        case IFELSE:
            a = apply(it, end);
            b = apply(it, end);
            c = apply(it, end);

            if(a > 0)
                return b;
            else
                return c;

        // 1 operand
        case COS:
            return cos(apply(it, end));

        case SIN:
            return sin(apply(it, end));

        case ABS:
            return qAbs(apply(it, end));

        case SIGN_OF:
            a = apply(it, end);

            if(a == 0)
                return 0;

            return qAbs(a)/a;

        case LOG:
            a = apply(it, end);
            return log(a);

        case EXP:
            a = apply(it, end);
            return exp(a);

        case SIGM:
            return sigmoid(apply(it, end));

        case IN:
            return plugGrid->getValue(((BrainNodeIn*)n)->x, ((BrainNodeIn*)n)->y);

        case CONST:
            return ((BrainNodeConst*)n)->value;

        case INTEGRATE:
            m = (BrainMemory*)(*it);
            it++;
            m->insert(apply(it, end));
            a = 0;
            for(int i = 0; i < m->mem.size(); i++) {
                a += m->mem[i];
            }
            return a;

        case INTERPOLATE:
            m = (BrainMemory*)(*it);
            it++;
            m->insert(apply(it, end));
            min = m->mem.first();
            max = m->mem.last();
            return (min + max) / 2;

        case DIFFERENTIATE:
            m = (BrainMemory*)(*it);
            it++;
            m->insert(apply(it, end));
            first = m->mem.first();
            second = m->mem.last();
            return second - first;

        case MEMORY:
            m = (BrainMemory*)(*it);
            it++;
            m->insert(apply(it, end));
            return m->mem.first();

        case SMOOTH:
            m = (BrainMemory*)(*it);
            it++;
            m->insert(apply(it, end));
            first = m->mem.first();
            second = m->mem.last();
            if(first > second)
                return first - (first - second)/10;
            else
                return second - (second - first)/10;

        case MIN:
            m = (BrainMemory*)(*it);
            it++;
            m->insert(apply(it, end));
            min = m->mem.first();
            for(int i = 0; i < m->size; i++) {
                if(m->mem[i] < min) {
                    min = m->mem[i];
                }
            }
            return min;
        case MAX:
            m = (BrainMemory*)(*it);
            it++;
            m->insert(apply(it, end));
            max = m->mem.first();
            for(int i = 0; i < m->size; i++) {
                if(m->mem[i] > max) {
                    max = m->mem[i];
                }
            }
            return max;

        case SINUS:
            m = (BrainMemory*)(*it);
            it++;
            max = m->mem.last();
            max++;
            m->mem.append(max);
            return sin(max * M_PI / 180.);
            break;
        case MEMORY_SPACE:
            return 0;
        case BAD_TYPE:
            return 0;
        default:
            return 0;
        }
        return 0;

    }

    QString BrainFunctional::createRandomFunc(int depth) {
        QString func;

        int rand = qrand()%100;
        if(rand < 50 && depth > 1) {
            func += "+ ,";
            func += this->createRandomFunc(depth -1);
            func += this->createRandomFunc(depth -1);
        }
        else if(rand > 50 && rand < 60) {
            func += "SINUS,";
            //func += QString::number(((float)qrand())/RAND_MAX) + ",";
        }
        else {
            func += "IN ";
            int x = qrand()%plugGrid->getSize();
            int y = qrand()%plugGrid->getSize();
            func += QString::number(x) + " " + QString::number(y) + ",";
        }

        return func;
    }

}
