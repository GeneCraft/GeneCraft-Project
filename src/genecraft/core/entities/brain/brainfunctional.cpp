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


namespace GeneCraftCore {

btScalar sigmoid(btScalar x)
{
     btScalar exp_value;
     btScalar return_value;

     /*** Exponential calculation ***/
     exp_value = exp((double) -3*x);

     /*** Final sigmoid value ***/
     return_value = 1 / (1 + exp_value);

     return return_value;
}


    BrainFunctional::BrainFunctional(QObject *parent) :
        Brain(parent)
    {
    }

    BrainFunctional::BrainFunctional(QJsonObject data) : Brain(data) {

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
            case INPUT:
                {
                    BrainNodeIn* in =  new BrainNodeIn(nodePart[1].toDouble(), nodePart[2].toDouble());
                    tree.append(in);
                    this->brainins.append(in); // display purpose
                }
                break;
            case CONSTANT:
                tree.append(new BrainNodeConst(nodePart[1].toDouble()));
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
            case WAVE:
                tree.append(new BrainNode(WAVE));
                tree.append(new BrainNodeConst(nodePart[1].toDouble()));
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
        btScalar value = apply(it, tree.end());
        if(value != value) {
            qDebug() << "NAN ! " << value << out->getConnexionInfo().toString();
        } else {
            out->setValue(value);
        }
    }

    btScalar BrainFunctional::apply(QList<BrainNode*>::iterator& it, QList<BrainNode*>::const_iterator end) {
        if(it == end) {
            return 0;
        }

        BrainNode* n = *it;
        BrainMemory* m;
        btScalar min, max, a, b, first, second, c;
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

        case INPUT: {
            btScalar v = plugGrid->getValue(((BrainNodeIn*)n)->x, ((BrainNodeIn*)n)->y);
            return v;
            }
        case CONSTANT:
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
            return sin(max * SIMD_PI / 180.);
            break;
        case WAVE:
            a = ((BrainNodeConst*)(*it))->value;
            it++;
            m = (BrainMemory*)(*it);
            it++;
            max = m->mem.last();
            max+=a;

            if(max != max) // do not store a nan !
                max = 0.;

            if(max > 360) {
                max -= 360;
            }
            else if(max < -360) {
                max += 360;
            }

            m->insert(max);
            return sin(max * SIMD_PI / 180.);
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
            default:
                qDebug() << "should not happend" << __LINE__ << __FILE__;
            }
        } else if(rand < 30) {
            func += "CONST ";
            btScalar x = Tools::random(-10.0, 10.0) ; //  -10..
            func += QString::number(x) + ",";
        }
        else if(rand < 70) {
            func += "IN ";
            btScalar x = ((btScalar)qrand())/RAND_MAX; //  0.0 to 1.0
            btScalar y = ((btScalar)qrand())/RAND_MAX; //  0.0 to 1.0
            func += QString::number(x) + " " + QString::number(y) + ",";
        } else {
            func.append("WAVE");
            func.append(" " + QString::number(Tools::random(-10.0, 10.0)) + ",");
        }


        return func;
    }

    QJsonObject BrainFunctional::serialize() {
        QJsonObject data = Brain::serialize();
        return data;
    }
}
