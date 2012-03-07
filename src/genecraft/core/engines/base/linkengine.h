#ifndef LINKENGINE_H
#define LINKENGINE_H

#include "genecraftcoreclasses.h"
#include "engine.h"
#include <QList>
#include "link.h"

namespace GeneCraftCore {

    class LinkEngine : public Engine
    {
        Q_OBJECT
    public:
        explicit LinkEngine(QObject *parent = 0);

    signals:

    public:
        void addLink(Linked* physicalNode, Linked* graphicalNode);
        void removeLink(Linked* physicalNode, Linked* graphicalNode);
        virtual void step();

    private:
        QList<Link> links;
    };

}

#endif // LINKENGINE_H
