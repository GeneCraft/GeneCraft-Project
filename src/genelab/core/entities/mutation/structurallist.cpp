#include "structurallist.h"

#include "tools.h"
#include <QDebug>

namespace GeneLabCore {

StructuralList::StructuralList()
{
}

MutationElement *StructuralList::pickOne()
{
    // Compute the sum of weights
    float totalWeight = 0.f;
    foreach(MutationElement *element, elements)
        totalWeight += element->weight;

    // get a random value in range
    float rand = Tools::random(0.f,totalWeight);

    // find the element
    float sum = 0.f;
    for(int i=0;i< elements.count();++i){

        if(sum > rand) // not possible at the first iteration
            return elements.at(i-1);

        MutationElement *element = elements.at(i);
        sum += element->weight;
    }

    // normally, it will not happen...
    return elements.last();
}

}
