#ifndef EXPERIMENTMANAGER_H
#define EXPERIMENTMANAGER_H

#include "experiment.h"

namespace GeneLabCore {
    class ExperimentManager
    {
    public:
        ExperimentManager(Experiment* exp) {
            this->exp = exp;
        }

        ExperimentManager(QVariant expData) {
            this->exp = new Experiment(Ressource::load(expData));
        }

    private:
        Experiment* exp;
    };
}

#endif // EXPERIMENTMANAGER_H
