/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "result.h"
#include "experiment.h"
#include <QDate>
#include <QDateTime>

#include <QVariantMap>

namespace GeneCraftCore {

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

    QJsonObject Result::serialize() {

        QJsonObject resultData;
        resultData.insert("type", "result");
        resultData.insert("experiment", exp);
        resultData.insert("fitness", (double)this->fitness);
        resultData.insert("genome", this->genome);
        resultData.insert("date", date);
        resultData.insert("worker", worker);
        resultData.insert("statistics", statistics);
        resultData.insert("stable", stableTime);
        resultData.insert("nbRun", nbRun);

        return resultData;
    }

    int cptResult = 0;
    // Basic constructor
    Result::Result() {
        this->fitness = 0;
        this->ressource = NULL;
        this->exp = "";
        this->date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        this->genome = QJsonObject();
        this->worker = "";
        this->broadcasted = false;
        this->statistics = QJsonObject();
        this->stableTime = 0;
        this->nbRun = 0;
    }

    Result::~Result() {
        if(ressource)
            delete ressource;
    }

    /**
      * A result is a fitness for a genome, and the ressource where this result is stored
      * If it come from a parent result (mutation, etc..) the ressource of the parent is attached
      */
    Result::Result(QString expId, btScalar fitness, int nbRun, int stableTime, QJsonObject genome,
           QString worker, QString date) {
        this->exp = expId;
        if(nbRun == 0) {
            this->fitness = 0;
            this->nbRun = 0;
        }
        else {
            this->nbRun = nbRun;
            this->fitness = fitness;
        }
        this->genome = genome;
        this->ressource = NULL;
        this->date = date;
        this->worker = worker;
        this->broadcasted = false;
        this->statistics = QJsonObject();
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
        this->nbRun = r.nbRun;
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
        this->nbRun = r.nbRun;
    }

    Result* Result::loadResult(QJsonObject data, bool& ok) {
        ok = true;


        if(!data.contains("fitness")) {
            return new Result();
        }
        btScalar fitness = data["fitness"].toDouble();

        if(!data.contains("genome")) {
            ok = false;
            return new Result();
        }
        QJsonObject genome = data["genome"].toObject();

        if(!data.contains("experiment")) {
            ok = false;
            return new Result();
        }

        QString exp        = data["experiment"].toString();
        if(!data.contains("date")) {
            ok = false;
            return new Result();
        }

        QString date       = data["date"].toString();
        QString worker;
        if(!data.contains("worker")) {
            worker = "OldResult";
        } else {

            worker = data["worker"].toString();
        }

        QJsonObject statistics = QJsonObject();
        if(data.contains("statistics")) {
            statistics = data["statistics"].toObject();
        }

        int stableTime = 0;
        if(data.contains("stable")) {
            stableTime = data["stable"].toInt();
        }

        int nbRun = 1;
        if(data.contains("nbRun")) {
            nbRun = data["nbRun"].toInt();
        }

        Result* r = new Result(exp, fitness, nbRun, stableTime, genome, worker, date);
        r->setStatistics(statistics);

        return r;
    }
}
