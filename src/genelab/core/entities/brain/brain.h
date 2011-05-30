#ifndef BRAIN_H
#define BRAIN_H

#include <QObject>
#include "genelabcoreclasses.h"

namespace GeneLabCore {
class Brain : public QObject
{
    Q_OBJECT
public:
    explicit Brain(int plugGridSize, QObject *parent = 0);

    BrainPlugGrid* getPlugGrid() {
        return this->plugGrid;
    }

    void setPlugGrid(BrainPlugGrid* plugGrid) {
        this->plugGrid = plugGrid;
    }

signals:

public slots:
    virtual void step() = 0;

protected:
    BrainPlugGrid* plugGrid;
};
}

#endif // BRAIN_H
