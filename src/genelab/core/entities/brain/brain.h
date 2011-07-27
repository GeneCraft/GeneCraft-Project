#ifndef BRAIN_H
#define BRAIN_H

#include <QObject>
#include "genecraftcoreclasses.h"

#include <QVariant>

namespace GeneCraftCore {
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

    virtual void step() = 0;

    // Frequency
    int getFrequency() { return frequency; }
    void setFrequency(int frequency) { this->frequency = frequency; }


protected:
    BrainPlugGrid* plugGrid;
    int frequency;
};
}

#endif // BRAIN_H
