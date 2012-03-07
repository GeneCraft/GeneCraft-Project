#include "link.h"


namespace GeneCraftCore {

    Link::Link(Linked* p, Linked* g)
    {
        this->physicalNode  = p;
        this->graphicalNode = g;
    }


    bool Link::operator==(Link b) const {
        return this->physicalNode == b.physicalNode && this->graphicalNode == b.graphicalNode;
    }

}
