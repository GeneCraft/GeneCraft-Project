#ifndef RESULT_H
#define RESULT_H

#include "factories/ressources/ressource.h"
#include <QVariant>


namespace GeneLabCore {
    class Experiment;

    class Result
    {
    public:
        // Basic constructor
        Result() {
            this->fitness = 0;
            this->ressource = NULL;
            this->exp = NULL;
        }

        /**
          * A result is a fitness for a genome, and the ressource where this result is stored
          * If it come from a parent result (mutation, etc..) the ressource of the parent is attached
          */
        Result(Experiment* exp, float fitness, QVariant genome) {
            this->exp = exp;
            this->fitness = fitness;
            this->genome = genome;
            this->ressource = NULL;
        }

        /**
          * Copy constructor
          */
        Result(const Result& r) {
            this->exp = r.exp;
            this->fitness = r.fitness;
            this->genome = r.genome;
            this->ressource = r.ressource;
        }

        /**
          * Result with higher fitness are bether !
          */
        bool operator<(const Result& r) const {
            return this->fitness < r.fitness;
        }

        /**
          * Copy affectation
          */
        void operator=(const Result& r) {
            this->exp = r.exp;
            this->fitness = r.fitness;
            this->genome = r.genome;
            this->ressource = r.ressource;
        }

        /**
          * Broadcast a result -> save it to the ressource
          */
        void save(Ressource * r);

        /**
          * Load a result -> take it from the ressource
          */
        void load(Ressource * r);

    private:
        // Score
        float fitness;
        // Entity
        QVariant genome;
        // Where to store it
        Ressource* ressource;
        // The attached experimentation
        Experiment* exp;
    };
}

#endif // RESULT_H
