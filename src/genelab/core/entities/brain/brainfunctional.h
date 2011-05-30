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

    void addOut(BrainOut* out, QVariantMap treeData);

signals:

public slots:
    virtual void step();

protected:
    void doNode(BrainNode* node, BrainOut* out);
    float value(BrainNode* node);

    QList<BrainOut*> outputs;
    QList<BrainNode*> nodes;

};
}

#endif // BRAINFUNCTIONAL_H
