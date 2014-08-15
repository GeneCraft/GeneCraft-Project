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

#include "brainnode.h"

namespace GeneCraftCore {
QString fromType(NodeType type) {
    switch(type) {
        // Input
        case INPUT :
        return "IN";
        case CONSTANT:
        return "CONST";

        // 2 operands
        case SUM:
        return "+";
        case PRODUCT:
        return "*";
        case DIVIDE:
        return "/";
        case ATAN:
        return "ATAN";
        // 2 operands + decisions
        case THRESOLD:
        return "T";
        case GT:
        return ">";
        // 3 operands
        case IFELSE:
        return "IF";

        // 1 operand
        case COS:
        return "COS";
        case SIN:
        return "SIN";
        case ABS:
        return "ABS";
        case SIGN_OF:
        return "SIGN";
        case LOG:
        return "LOG";
        case EXP:
        return "EXP";
        case SIGM:
        return "SIGM";
        case SINUS:
        return "SINUS";
        case WAVE:
        return "WAVE";

        // Memory
        case INTEGRATE:
        return "INT";
        case INTERPOLATE:
        return "INTERPOLATE";
        case DIFFERENTIATE:
        return "DIFF";
        case MEMORY:
        return "MEM";
        case SMOOTH:
        return "SMOOTH";
        case MIN:
        return "MIN";
        case MAX:
        return "MAX";

        // MemorySpace used by all memory node
        case MEMORY_SPACE:
        return "SHOULD_NOT_BE_HERE!";
        case BAD_TYPE:
        return "BAD_TYPE!";
    }

    return "BAD_TYPE!";
}

NodeType fromString(QString string) {
    // Input
    if(string == "IN")
        return INPUT;
    if(string == "CONST")
        return CONSTANT;
    if(string == "+")
        return SUM;
    if(string == "*")
        return PRODUCT;
    if(string == "/")
        return DIVIDE;
    if(string == "ATAN")
        return ATAN;
    if(string == "T")
        return THRESOLD;
    if(string == ">")
        return GT;
    if(string == "IF")
        return IFELSE;

    if(string == "COS")
        return COS;
    if(string == "SIN")
        return SIN;
    if(string == "ABS")
        return ABS;

    if(string == "SIGN")
        return SIGN_OF;
    if(string == "LOG")
        return LOG;
    if(string == "EXP")
        return EXP;
    if(string =="SIGM")
        return SIGM;

    if(string =="MEM")
        return MEMORY;
    if(string =="INT")
        return INTEGRATE;
    if(string =="INTERPOLATE")
        return INTERPOLATE;
    if(string =="DIFF")
        return DIFFERENTIATE;
    if(string =="SMOOTH")
        return SMOOTH;
    if(string =="MIN")
        return MIN;
    if(string =="MAX")
        return MAX;
    if(string =="SINUS")
        return SINUS;
    if(string =="WAVE")
        return WAVE;

    return BAD_TYPE;
}

BrainMemory::BrainMemory(int size) : BrainNode(MEMORY_SPACE){
    if(size <= 0) {
        qDebug() << "size of 0 or less ! bad" << size;
        size = 1;
    }
    this->size = size;
    for(int i = 0; i < size; i++) {
        this->insert(0);
    }
}

void BrainMemory::insert(btScalar value) {
    mem.append(value);
    if(mem.size() > size)
        mem.removeFirst();
}

}
