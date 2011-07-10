#ifndef EXPERIMENTMANAGER_H
#define EXPERIMENTMANAGER_H

#include "experiment.h"
#include "mutation/mutationsmanager.h"

class SelectionManager;

namespace GeneLabCore {
    class ExperimentManager
    {
    public:
        ExperimentManager(btFactory* factory, Experiment* exp) {
            this->factory = factory;
            this->exp = exp;
        }

        ExperimentManager(QVariant expData) {
            this->exp = new Experiment(Ressource::load(expData));
        }

        ExperimentManager() {
            this->exp = new Experiment(QVariant());
        }

        void experiment();

    private:
        Experiment* exp;
        MutationsManager* mutations;
        SelectionManager* selections;
        btFactory* factory;
    };
}

#endif // EXPERIMENTMANAGER_H
