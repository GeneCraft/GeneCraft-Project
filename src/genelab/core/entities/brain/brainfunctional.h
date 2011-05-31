#ifndef BRAINFUNCTIONAL_H
#define BRAINFUNCTIONAL_H

#include "genelabcoreclasses.h"
#include "brain.h"

#include <QMap>
#include <QVariant>

namespace GeneLabCore {
class BrainFunctional : public Brain
{
    Q_OBJECT
public:
    explicit BrainFunctional(int plugGridSize, QObject *parent = 0);

    void addOut(BrainOut* out, QString treeData);

signals:

public slots:
    virtual void step();

protected:
    void doNode(QList<BrainNode*> tree, BrainOut* out);
    float value(BrainNode* node);

    QList<BrainOut*> outputs;
    QList<QList<BrainNode*> > trees;

};
}

#endif // BRAINFUNCTIONAL_H
