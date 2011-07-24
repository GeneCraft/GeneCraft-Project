#ifndef BRAINFUNCTIONAL_H
#define BRAINFUNCTIONAL_H

#include "genelabcoreclasses.h"
#include "brain.h"
#include "brainnode.h"

#include <QMap>
#include <QVariant>
#include <QList>

namespace GeneLabCore {
class BrainFunctional : public Brain
{

public:
    explicit BrainFunctional(QObject *parent = 0);
    BrainFunctional(QVariant data);
    ~BrainFunctional();

    void addOut(BrainOut* out);
    void removeOut(BrainOut* out);

    QList<BrainNodeIn*> getBrainNodeIn() {
        return brainins;
    }

    static QString createRandomFunc(int depth, StructuralList* nodesList = NULL);

    virtual QVariant serialize();

    virtual void step();

protected:
    void doNode(QList<BrainNode*> tree, BrainOut* out);
    btScalar apply(QList<BrainNode*>::iterator& it, QList<BrainNode*>::const_iterator end);

    QList<BrainOut*> outputs;
    QList<QList<BrainNode*> > trees;

    QList<BrainNodeIn*> brainins;

    PlugGridVisualizer * viz;

};
}

#endif // BRAINFUNCTIONAL_H
