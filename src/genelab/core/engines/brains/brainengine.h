#ifndef BRAINENGINE_H
#define BRAINENGINE_H

#include <QObject>

#include "genelabcoreclasses.h"
#include "engine.h"
#include "pluggriddesignvisualizer.h"
namespace GeneLabCore {

    class BrainEngine : public Engine
    {
        Q_OBJECT
    public:
        explicit BrainEngine(QObject *parent = 0);

        bool isRenderable() {
            return true;
        }

        void addPlugGridDez(PlugGridDesignVisualizer* dez) {
            this->gridDezVisualizers.append(dez);
        }

        QWidget* getRenderWidget(QWidget* parent);
        QList<BrainPlugGrid*> getGrids();
        QList<Brain*> getBrains();

    signals:

    public slots:
        BrainPlugGrid* createGrid(int size);
        void addGrid(BrainPlugGrid* grid);

        void beforeStep();
        void step();
        void afterStep();

    private:
        QList<BrainPlugGrid*> grids;
        QList<Brain*> brains;
        QList<PlugGridVisualizer*> gridVisualizers;
        QList<PlugGridDesignVisualizer*> gridDezVisualizers;

    };
}

#endif // BRAINENGINE_H
