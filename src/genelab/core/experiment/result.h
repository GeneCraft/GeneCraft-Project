#ifndef RESULT_H
#define RESULT_H

#include "factories/ressources/ressource.h"
#include <QVariant>
#include <QDateTime>
#include "LinearMath/btScalar.h"

namespace GeneCraftCore {

    class Result;
    bool myLessThan( const Result *a, const Result *b );

    class Result
    {
    public:
        // Basic constructor
        Result();

        /**
          * A result is a fitness for a genome, and the ressource where this result is stored
          * If it come from a parent result (mutation, etc..) the ressource of the parent is attached
          */
        Result(QString expId, btScalar fitness, int nbRun, int stableTime, QVariant genome,
               QString workerName = "Anonymous",
               QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
               );

        /** Copy constructor */
        Result(const Result& r);

        ~Result();

        /**
          * Result with higher fitness are bether !
          */
        bool operator<(const Result& r) const {
            return this->fitness < r.fitness;
        }

        /**
          * Copy affectation
          */
        void operator=(const Result& r);

        /**
          * Broadcast a result -> save it to the ressource
          */
        void save(Ressource * r);
        QVariant serialize();

        static Result* loadResult(QVariant data, bool& ok);

        btScalar getFitness() const {
            if(nbRun > 0)
                return fitness/nbRun;
            else
                return -1;
        }

        QVariant getGenome() const {
            return genome;
        }

        Ressource* getRessource() const {
            return ressource;
        }

        QString getExperienceId() const {
            return exp;
        }

        QString getDate() const {
            return date;
        }

        void setFitness(btScalar fitness) {
            this->nbRun++;
            this->fitness += fitness;
        }

        void setGenome(QVariant genome) {
            this->genome = genome;
        }

        void setRessource(Ressource *r) {
            this->ressource = r;
        }

        void setExperienceId(QString expId) {
            this->exp = expId;
        }

        void setDate(QString date) {
            this->date = date;
        }

        QString getWorker() {
            return worker;
        }

        void setBroadcasted(bool broadcasted) {
            this->broadcasted = broadcasted;
        }

        bool isBroadcasted() {
            return this->broadcasted;
        }

        void setStatistics(QVariant statistics) {
            this->statistics = statistics;
        }

        QVariant getStatistics() {
            return this->statistics;
        }

        void setStableAt(int cpt) {
            this->stableTime = cpt;
        }

        int getStable() {
            return this->stableTime;
        }

        void setWorker(QString worker) {
            this->worker = worker;
        }

        int getNbRun() {
            return this->nbRun;
        }

        void setNbRun(int nbRun) {
            this->nbRun = nbRun;
        }

        void resetFitness() {
            this->nbRun = 0;
            this->fitness = 0;
        }

    protected:
        // Score
        btScalar fitness;
        // Entity
        QVariant genome;
        // Where to store it
        Ressource* ressource;
        // The attached experimentation
        QString exp;
        // The date
        QString date;
        // The executant
        QString worker;
        // Broadcasted online already ?
        bool broadcasted;
        // The entity statistics
        QVariant statistics;
        // Stability reached at
        int stableTime;
        // Nb Time tested
        int nbRun;
    };
}

#endif // RESULT_H
