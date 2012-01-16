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

#include "experiment.h"

#include "mutation/mutationsmanager.h"
#include "btworldfactory.h"

#define EXP_FORMAT_VERSION 0.1
#define DEFAULT_NB_RUN 3

namespace GeneCraftCore {

Experiment::Experiment() : ressource(NULL){

        // information
        id = "aNewExp";
        description = "No description";
        author = "You certainly";
        comments = "";
        dateOfCreation = QDateTime::currentDateTime();
        online = false;

        // simulation
        onlyIfEntityIsStable = true;
        timeToWaitForStability = 300;
        duration = 1200;
        stopIfEntityIsNotInOnePiece = true;

        // mutations
        mutationsManager = new MutationsManager();

        // world
        worldDataMap = btWorldFactory::createSimpleWorld().toMap();

        // seed
        seedInfo.insert("type", "family");
        seedInfo.insert("family", "spider");

        evalFunction  = QString("(function() {")+
                                    QString("return entity.rootDistance.value; ")+
                                    QString("})");

        validityFunction = "(function() {return true; })";
        endFunction     = "(function(actualStep) { return false; })";
        dieFunction     = "(function() { return false; })";


        nbRun = DEFAULT_NB_RUN;
        if(nbRun > 1) {
            spawnNoise = true;
        } else {
            spawnNoise = false;
        }

    }

    Experiment::~Experiment() {
        delete mutationsManager;
    }

    Experiment::Experiment(QVariant data) : ressource(NULL) {

        QVariantMap map = data.toMap();
        online = false;

        // TODO
        //if(map["version"].toString().compare(EXP_FORMAT_VERSION) != 0)
        //  throw new FormatVersionError("Exp", map["version"]);

        // information
        id              = map["_id"].toString();
        if(id == "" && map.contains("id")) {
            id = map["id"].toString(); // Old version
        }

        description     = map["description"].toString();
        author          = map["author"].toString();
        comments        = map["comments"].toString();
        dateOfCreation  = QDateTime::fromString(map["dateOfCreation"].toString(),"yyyy-MM-dd hh:mm:ss");

        // simulation
        duration = map["duration"].toInt();
        timeToWaitForStability = map["timeToWaitForStability"].toInt();
        onlyIfEntityIsStable = map["onlyIfEntityIsStable"].toBool();
        stopIfEntityIsNotInOnePiece = map["stopIfEntityIsNotInOnePiece"].toBool();

        // mutations
        mutationsManager = new MutationsManager(map["mutations"]);

        // world
        worldDataMap = map["world"].toMap();

        // seed TODO
        seedInfo = map["seedInfo"].toMap();

        if(map.contains("evalFunction")) {
            evalFunction     = map["evalFunction"].toString();
        }
        else {
            evalFunction = "(function() {return -1;})";
        }

        if(map.contains("validityFunction"))
            validityFunction  = map["validityFunction"].toString();
        else
            validityFunction = "";

        if(validityFunction == "") {
            qDebug() << "no validity check function found, will always return true";

            validityFunction = "(function() {return true;})";
        }

        if(map.contains("endFunction"))
            endFunction = map["endFunction"].toString();
        else
            endFunction = "";

        if(endFunction == "") {
            qDebug() << "no end function found, will stop when maxStep occur";

            endFunction = "(function(int step) {return step <"+QString::number(this->duration)+";})";
        }

        if(map.contains("dieFunction"))
            dieFunction = map["dieFunction"].toString();
        else
            dieFunction = "";

        if(dieFunction =="") {
            qDebug() << "no die function found, will always return false";

            dieFunction = "(function() {return false;})";
        }

        // Number of evaluation for each individual
        nbRun = DEFAULT_NB_RUN;
        if(map.contains("nbRun")) {
            nbRun = map["nbRun"].toInt();
        }

        if(map.contains("spawnNoise")) {
            spawnNoise = map["spawnNoise"].toBool();
        } else {
            spawnNoise = false;
        }
    }

    QVariant Experiment::serialize() {
        QVariantMap map;

        // version
        map.insert("version",EXP_FORMAT_VERSION);

        // information
        map.insert("_id",id);
        map.insert("description",description);
        map.insert("author",author);
        map.insert("comments",comments);
        map.insert("dateOfCreation",dateOfCreation.toString("yyyy-MM-dd hh:mm:ss"));

        // Simulation
        map.insert("onlyIfEntityIsStable",onlyIfEntityIsStable);
        map.insert("timeToWaitForStability",timeToWaitForStability);
        map.insert("duration",duration);
        map.insert("stopIfEntityIsNotInOnePiece",stopIfEntityIsNotInOnePiece);

        // mutations
        map.insert("mutations",mutationsManager->serialize());

        // world
        map.insert("world",worldDataMap);

        map.insert("seedInfo", seedInfo);

        map.insert("endFunction", endFunction);
        map.insert("evalFunction", evalFunction);
        map.insert("validityFunction", validityFunction);
        map.insert("dieFunction", dieFunction);
        map.insert("nbRun", this->nbRun);
        map.insert("spawnNoise", this->spawnNoise);

        return map;
    }
}
