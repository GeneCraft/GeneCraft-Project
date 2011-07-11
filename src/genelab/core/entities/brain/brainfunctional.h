#ifndef BRAINFUNCTIONAL_H
#define BRAINFUNCTIONAL_H

#include "genelabcoreclasses.h"
#include "brain.h"

#include <QMap>
#include <QVariant>
#include <QList>

namespace GeneLabCore {
class BrainFunctional : public Brain
{

public:
    explicit BrainFunctional(int plugGridSize, QObject *parent = 0);
    BrainFunctional(QVariant data);
    ~BrainFunctional();

    void addOut(BrainOut* out);
    void removeOut(BrainOut* out);

    static QString createRandomFunc(int depth);

    virtual QVariant serialize();

    virtual void step();

protected:
    void doNode(QList<BrainNode*> tree, BrainOut* out);
    float apply(QList<BrainNode*>::iterator& it, QList<BrainNode*>::const_iterator end);

    QList<BrainOut*> outputs;
    QList<QList<BrainNode*> > trees;

    PlugGridVisualizer * viz;

};
}

#endif // BRAINFUNCTIONAL_H
