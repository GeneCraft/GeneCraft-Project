#include "result.h"
#include "experiment.h"
#include <QDate>
#include <QDateTime>

#include <QVariantMap>

namespace GeneLabCore {
    /**
      * Broadcast a result -> save it to the ressource
      */
    void Result::save(Ressource * r) {
        ressource = r;

        QVariantMap resultData;
        resultData.insert("type", "result");
        resultData.insert("experiment", exp);
        resultData.insert("fitness", (double)this->fitness);
        resultData.insert("genome", this->genome);
        resultData.insert("date", QDateTime::currentDateTime().toString());

        ressource->save(resultData);
    }

    // Basic constructor
    Result::Result() {
        this->fitness = 0;
        this->ressource = NULL;
        this->exp = "";
        this->date = "";
        this->genome = QVariant();
    }

    Result::~Result() {
        if(ressource)
            delete ressource;
    }

    /**
      * A result is a fitness for a genome, and the ressource where this result is stored
      * If it come from a parent result (mutation, etc..) the ressource of the parent is attached
      */
    Result::Result(QString expId, float fitness, QVariant genome,
           QString date) {
        this->exp = expId;
        this->fitness = fitness;
        this->genome = genome;
        this->ressource = NULL;
        this->date = date;
    }

    /**
      * Copy constructor
      */
    Result::Result(const Result& r) {
        this->exp = r.exp;
        this->fitness = r.fitness;
        this->genome = r.genome;
        this->ressource = r.ressource;
        this->date = r.date;
    }


    /**
      * Copy affectation
      */
    void Result::operator=(const Result& r) {
        this->exp = r.exp;
        this->fitness = r.fitness;
        this->genome = r.genome;
        this->ressource = r.ressource;
        this->date = r.date;
    }

    Result* Result::loadResult(QVariant data, bool& ok) {
        ok = true;

        QVariantMap dataMap = data.toMap();

        float fitness = dataMap["fitness"].toFloat(&ok);
        if(!ok)
            return new Result();

        QVariantMap genome = dataMap["genome"].toMap();
        if(genome == QVariant())
            return new Result();

        QString exp = dataMap["experiment"].toString();
        if(!ok || !dataMap.contains("experiment"))
            return new Result();

        QString date = dataMap["date"].toString();
        if(!ok ||!dataMap.contains("date"))
            return new Result();

        return new Result(exp, fitness, genome, date);
    }
}
