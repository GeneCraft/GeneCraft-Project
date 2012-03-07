#ifndef LINK_H
#define LINK_H

#include "genecraftcoreclasses.h"
#include "node.h"

namespace GeneCraftCore {

    class Link
    {
    public:
        Link(Linked* physicalNode, Linked* graphicalNode);
        Linked* physicalNode;
        Linked* graphicalNode;
        bool operator==(Link b) const;
    };

}

#endif // LINK_H
