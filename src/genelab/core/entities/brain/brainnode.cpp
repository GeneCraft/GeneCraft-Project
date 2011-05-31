#include "brainnode.h"

namespace GeneLabCore {
QString fromType(NodeType type) {
    switch(type) {
        // Input
        case IN :
        return "IN";
        case CONST:
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
        return IN;
    if(string == "CONST")
        return CONST;
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

    return BAD_TYPE;
}

}
