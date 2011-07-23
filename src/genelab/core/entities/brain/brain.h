#ifndef BRAIN_H
#define BRAIN_H

#include <QObject>
#include "genelabcoreclasses.h"

#include <QVariant>

namespace GeneLabCore {
class Brain : public QObject
{

public:
    explicit Brain(QObject *parent = 0);
    Brain(QVariant data);

    BrainPlugGrid* getPlugGrid() {
        return this->plugGrid;
    }

    void setPlugGrid(BrainPlugGrid* plugGrid) {
        this->plugGrid = plugGrid;
    }

    virtual QVariant serialize();

    //static int randomPlugGridSize();

    virtual void step() = 0;
    int getFrequency() {
        return frequency;
    }

protected:
    BrainPlugGrid* plugGrid;
    int frequency;
};
}

#endif // BRAIN_H
