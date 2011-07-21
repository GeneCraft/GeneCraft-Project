#include "brainfunctional.h"
#include "brainnode.h"
#include "brainout.h"
#include "brainpluggrid.h"
#include "sinusin.h"

#include <math.h>
#include <cstdlib>

#include <QStringList>
#include "mutation/structurallist.h"

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

    BrainFunctional::BrainFunctional(QVariant data) : Brain(data) {

    }

    BrainFunctional::~BrainFunctional() {
        foreach(QList<BrainNode*> tree, trees) {
            foreach(BrainNode* n, tree) {
                delete n;
            }
        }

        delete plugGrid;
    }

    void BrainFunctional::addOut(BrainOut *out) {
        QString treeData = out->getConnexionInfo().toString();
        QList<BrainNode*> tree = QList<BrainNode*>();
        QStringList nodes = treeData.split(",", QString::SkipEmptyParts);

        for(int i = 0; i < nodes.length(); i++) {
            QString node = nodes[i];
            QStringList nodePart = node.split(" ", QString::SkipEmptyParts);
            NodeType t = fromString(nodePart[0]);
            switch(t) {
            // 2 operands
            case SUM:
            case PRODUCT:
            case DIVIDE:
            case ATAN:
            // 2 operands + decisions
            case THRESOLD: // --------> THRESHOLD ;)
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
                tree.append(new BrainNodeIn(nodePart[1].toFloat(), nodePart[2].toFloat()));
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

        this->trees.append(tree);
        this->outputs.append(out);
    }

    void BrainFunctional::removeOut(BrainOut* out)
    {
        qDebug() << Q_FUNC_INFO;

        int iOut = outputs.indexOf(out);
        if(iOut != -1)
        {
            foreach(BrainNode* node, trees.at(iOut)) {
                delete node;
            }

            outputs.removeAt(iOut);
            trees.removeAt(iOut);
        }
    }

    void BrainFunctional::step() {
        for(int i = 0; i < trees.size(); i++) {
            this->doNode(trees[i], outputs[i]);
        }
    }

    void BrainFunctional::doNode(QList<BrainNode*> tree, BrainOut* out) {
        QList<BrainNode*>::iterator it = tree.begin();
        float value = apply(it, tree.end());
        if(value != value) {
            qDebug() << "NAN ! " << value << out->getConnexionInfo().toString();
            qDebug() << this->plugGrid->getSize();
        } else {
            out->setValue(value);
        }
    }

    float BrainFunctional::apply(QList<BrainNode*>::iterator& it, QList<BrainNode*>::const_iterator end) {
        if(it == end) {
            return 0;
        }

        BrainNode* n = *it;
        BrainMemory* m;
        float min, max, a, b, first, second, c;
        it++;
        switch(n->type) {
        // 2 operands
        case SUM:
            return apply(it, end) + apply(it, end);

        case PRODUCT:
            a = apply(it, end);
            b = apply(it, end);
            return a*b;

        case DIVIDE:
            a = apply(it, end);
            b = apply(it, end);

            c = 1./b;

            if(c != c) // nan or infinity
                c = 0.;

            return a;

        case ATAN:
            a = atan2(apply(it, end), apply(it, end));

            return a;

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

            a= qAbs(a)/a; // TODO Sign

            if(a!=a)
                return 0;

            return qAbs(a)/a    ;

        case LOG:
            a = apply(it, end);
            // To avoid strange logarithms values
            if(a <= 1) {
                return 0;
            }
            a = log(a);

            return a;

        case EXP:
            a = apply(it, end);
            a = a*a;

            if(a!=a)
                return 0;

            return a;

        case SIGM:
            return sigmoid(apply(it, end));

        case IN: {
            float v = plugGrid->getValue(((BrainNodeIn*)n)->x, ((BrainNodeIn*)n)->y);
            return v;
            }
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
            a = apply(it, end);
            c = apply(it, end);
            max = m->mem.last();
            max+=a;

            if(max != max) // do not store a nan !
                max = 0.;

            m->insert(max);
            //max *= a;
            max += c;
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

    QString BrainFunctional::createRandomFunc(int depth, StructuralList* nodesList) {
        QString func;

        int rand = qrand() % 100;
        int maxmem = qrand() % 100 + 1;
        if(depth > 1 && nodesList) {
            int nodeType = nodesList->pickOne()->type;
            switch(nodeType) {
            case 0:
                func.append("+,");
                func += createRandomFunc(depth -1);
                func += createRandomFunc(depth -1);
                break;
            case 1:
                func.append("*,");
                func += createRandomFunc(depth -1);
                func += createRandomFunc(depth -1);
                break;
            case 2:
                func.append("/,");
                func += createRandomFunc(depth -1);
                func += createRandomFunc(depth -1);
                break;
            case 3:
                func.append("ATAN,");
                func += createRandomFunc(depth -1);
                func += createRandomFunc(depth -1);
                break;
            case 4:
                func.append("T,");
                func += createRandomFunc(depth -1);
                func += createRandomFunc(depth -1);
                break;
            case 5:
                func.append(">,");
                func += createRandomFunc(depth -1);
                func += createRandomFunc(depth -1);
                func += createRandomFunc(depth -1);
                break;
            case 6:
                func.append("IF,");
                func += createRandomFunc(depth -1);
                func += createRandomFunc(depth -1);
                func += createRandomFunc(depth -1);
                break;
            case 7:
                func.append("COS,");
                func += createRandomFunc(depth -1);
                break;
            case 8:
                func.append("SIN,");
                func += createRandomFunc(depth -1);
                break;
            case 9:
                func.append("ABS,");
                func += createRandomFunc(depth -1);
                break;
            case 10:
                func.append("SIGN,");
                func += createRandomFunc(depth -1);
                break;
            case 11:
                func.append("LOG,");
                func += createRandomFunc(depth -1);
                break;
            case 12:
                func.append("EXP,");
                func += createRandomFunc(depth -1);
                break;
            case 13:
                func.append("SIGM,");
                func += createRandomFunc(depth -1);
                break;
            case 14:
                func.append("SINUS,");
                func += createRandomFunc(depth -1);
                func += createRandomFunc(depth -1);
                break;
            case 15:
                func.append("MEM ");
                func.append(" " + QString::number(maxmem) + ",");
                func += createRandomFunc(depth -1);
                break;
            case 16:
                func.append("SMOOTH");
                func.append(" " + QString::number(maxmem) + ",");
                func += createRandomFunc(depth -1);
                break;
            case 17:
                func.append("INT");
                func.append(" " + QString::number(maxmem) + ",");
                func += createRandomFunc(depth -1);
                break;
            case 18:
                func.append("INTERPOLATE");
                func.append(" " + QString::number(maxmem) + ",");
                func += createRandomFunc(depth -1);
                break;
            case 19:
                func.append("MAX");
                func.append(" " + QString::number(maxmem) + ",");
                func += createRandomFunc(depth -1);
                break;
            case 20:
                func.append("MIN");
                func.append(" " + QString::number(maxmem) + ",");
                func += createRandomFunc(depth -1);
                break;
            case 21:
                func.append("DIFF");
                func.append(" " + QString::number(maxmem) + ",");
                func += createRandomFunc(depth -1);
                break;
            }
        } else if(rand < 30) {
            func += "CONST ";
            float x = ((float)qrand())/RAND_MAX*20 - 10; //  0.0 to 1.0
            func += QString::number(x) + ",";
        }
        else {
            func += "IN ";
            float x = ((float)qrand())/RAND_MAX; //  0.0 to 1.0
            float y = ((float)qrand())/RAND_MAX; //  0.0 to 1.0
            func += QString::number(x) + " " + QString::number(y) + ",";
        }

        return func;
    }

    QVariant BrainFunctional::serialize() {
        QVariantMap data = Brain::serialize().toMap();
        return data;
    }
}
