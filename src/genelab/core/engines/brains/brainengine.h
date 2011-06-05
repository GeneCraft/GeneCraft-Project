#ifndef BRAINENGINE_H
#define BRAINENGINE_H

#include <QObject>

#include "genelabcoreclasses.h"
#include "engine.h"
namespace GeneLabCore {

    class BrainEngine : public Engine
    {
        Q_OBJECT
    public:
        explicit BrainEngine(QObject *parent = 0);

        bool isRenderable() {
            return true;
        }

        /*void addPlugGridDez(PlugGridDesignVisualizer* dez) {
            this->gridDezVisualizers.append(dez);
        }

        PlugGrid* getRenderWidget(QWidget* parent);
        QList<BrainPlugGrid*> getGrids();
        QList<Brain*> getBrains();*/

    signals:

    public slots:
        BrainPlugGrid* createGrid(int size);
        void addGrid(BrainPlugGrid* grid);

        void beforeStep();
        void step();
        void afterStep();

    private:

    };
}

#endif // BRAINENGINE_H
