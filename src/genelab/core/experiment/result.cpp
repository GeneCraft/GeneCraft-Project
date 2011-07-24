#include "result.h"
#include "experiment.h"
#include <QDate>
#include <QDateTime>

#include <QVariantMap>

namespace GeneLabCore {

    // To sort result, descending
    bool myLessThan( const Result *a, const Result *b )
    {
       return !((*a) < (*b));
    }

    /**
      * Broadcast a result -> save it to the ressource
      */
    void Result::save(Ressource * r) {
        ressource = r;

        ressource->save(this->serialize());
    }

    QVariant Result::serialize() {

        QVariantMap resultData;
        resultData.insert("type", "result");
        resultData.insert("experiment", exp);
        resultData.insert("fitness", (double)this->fitness);
        resultData.insert("genome", this->genome);
        resultData.insert("date", date);
        resultData.insert("worker", worker);
        resultData.insert("statistics", statistics);
        resultData.insert("stable", stableTime);

        return resultData;
    }

    int cptResult = 0;
    // Basic constructor
    Result::Result() {
        this->fitness = 0;
        this->ressource = NULL;
        this->exp = "";
        this->date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        this->genome = QVariant();
        this->worker = "";
        this->broadcasted = false;
        this->statistics = QVariant();
        this->stableTime = 0;
    }

    Result::~Result() {
        if(ressource)
            delete ressource;
    }

    /**
      * A result is a fitness for a genome, and the ressource where this result is stored
      * If it come from a parent result (mutation, etc..) the ressource of the parent is attached
      */
    Result::Result(QString expId, btScalar fitness, int stableTime, QVariant genome,
           QString worker, QString date) {
        this->exp = expId;
        this->fitness = fitness;
        this->genome = genome;
        this->ressource = NULL;
        this->date = date;
        this->worker = worker;
        this->broadcasted = false;
        this->statistics = QVariant();
        this->stableTime = stableTime;
    }

    /**
      * Copy constructor
      */
    Result::Result(const Result& r) {
        this->exp = r.exp;
        this->fitness = r.fitness;
        this->genome = r.genome;
        this->ressource = NULL;
        this->date = r.date;
        this->worker = r.worker;
        this->broadcasted = r.broadcasted;
        this->statistics = r.statistics;
        this->stableTime = r.stableTime;
    }


    /**
      * Copy affectation
      */
    void Result::operator=(const Result& r) {
        this->exp = r.exp;
        this->fitness = r.fitness;
        this->genome = r.genome;
        this->ressource = NULL;
        this->date = r.date;
        this->worker = r.worker;
        this->broadcasted = r.broadcasted;
        this->statistics = r.statistics;
        this->stableTime = r.stableTime;
    }

    Result* Result::loadResult(QVariant data, bool& ok) {
        ok = true;

        QVariantMap dataMap = data.toMap();

        btScalar fitness = dataMap["fitness"].toFloat(&ok);
        if(!ok)
            return new Result();

        if(!dataMap.contains("genome")) {
            ok = false;
            return new Result();
        }

        if(!dataMap.contains("experiment")) {
            ok = false;
            return new Result();
        }

        if(!dataMap.contains("date")) {
            ok = false;
            return new Result();
        }

        QString worker;
        if(!dataMap.contains("worker")) {
            worker = "OldResult";
        } else {

            worker = dataMap["worker"].toString();
        }

        QVariant statistics = QVariant();
        if(dataMap.contains("statistics")) {
            statistics = dataMap["statistics"];
        }

        int stableTime = 0;
        if(dataMap.contains("stable")) {
            stableTime = dataMap["stable"].toInt();
        }

        QVariantMap genome = dataMap["genome"].toMap();
        QString exp        = dataMap["experiment"].toString();
        QString date       = dataMap["date"].toString();
        Result* r = new Result(exp, fitness, stableTime, genome, worker, date);
        r->setStatistics(statistics);
        return r;
    }
}
