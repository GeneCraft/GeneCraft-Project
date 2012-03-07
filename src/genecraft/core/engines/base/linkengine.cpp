#include "linkengine.h"

#include "link.h"
#include "node.h"

namespace GeneCraftCore {

    LinkEngine::LinkEngine(QObject *parent) :
        Engine(parent)
    {
    }

    void LinkEngine::addLink(Linked* physicalNode, Linked* graphicalNode) {
        this->links.append(Link(physicalNode, graphicalNode));
    }

    void LinkEngine::removeLink(Linked* physicalNode, Linked* graphicalNode) {
        this->links.removeAll(Link(physicalNode, graphicalNode));
    }

    void LinkEngine::step() {
        foreach(Link link, this->links) {
            link.graphicalNode->setPosition( link.physicalNode->getPosition() );
        }
    }
}
