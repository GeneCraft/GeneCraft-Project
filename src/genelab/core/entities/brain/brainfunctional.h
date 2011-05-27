#ifndef BRAINFUNCTIONAL_H
#define BRAINFUNCTIONAL_H

#include "genelabcoreclasses.h"
#include "brain.h"

namespace GeneLabCore {
class BrainFunctional : public Brain
{
    Q_OBJECT
public:
    explicit BrainFunctional(int plugGridSize, QObject *parent = 0);

signals:

public slots:

protected:


};
}

#endif // BRAINFUNCTIONAL_H
