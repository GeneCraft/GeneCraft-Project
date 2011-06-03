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
    Q_OBJECT
public:
    explicit BrainFunctional(int plugGridSize, QObject *parent = 0);

    void addOut(BrainOut* out, QString treeFunc);
    QString createRandomFunc(int depth);


signals:

public slots:
    virtual void step();

protected:
    void doNode(QList<BrainNode*> tree, BrainOut* out);
    float apply(QList<BrainNode*>::iterator it, QList<BrainNode*>::const_iterator end);

    QList<BrainOut*> outputs;
    QList<QList<BrainNode*> > trees;

    PlugGridVisualizer * viz;

};
}

#endif // BRAINFUNCTIONAL_H
