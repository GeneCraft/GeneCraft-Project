#include "brainengine.h"
#include "pluggridvisualizer.h"
#include "brainpluggrid.h"
#include "brain.h"

#include <QLabel>

namespace GeneLabCore {

    BrainEngine::BrainEngine(QObject *parent) :
        Engine(parent)
    {
    }

    QWidget* BrainEngine::getRenderWidget(QWidget* parent) {
        PlugGridVisualizer* w = new PlugGridVisualizer(this);
        this->gridVisualizers.append(w);
        return w;
    }

    void BrainEngine::beforeStep() {
        // Filling the interconnexion layer
        foreach(BrainPlugGrid* n, this->grids) {
            n->beforeStep();
        }
    }

    void BrainEngine::step() {
        // Using the interconnexion layer
        foreach(Brain* brain, this->brains) {
            brain->step();
        }

        foreach(PlugGridVisualizer* viz, this->gridVisualizers) {
            viz->step();
        }
    }

    void BrainEngine::afterStep() {
        // Reseting the interconnexion layer
        foreach(BrainPlugGrid* n, this->grids) {
            n->afterStep();
        }
    }

    BrainPlugGrid* BrainEngine::createGrid(int size) {
        BrainPlugGrid* n = new BrainPlugGrid(size);
        this->grids.append(n);
        return n;
    }

    void BrainEngine::addGrid(BrainPlugGrid* grid) {
        this->grids.append(grid);
    }

    QList<BrainPlugGrid*> BrainEngine::getGrids() {
        return this->grids;
    }

    QList<Brain*> BrainEngine::getBrains() {
        return brains;
    }

}

