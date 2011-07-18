#include "experiment.h"

#include "mutation/mutationsmanager.h"

#define EXP_FORMAT_VERSION 0.1

namespace GeneLabCore {

    Experiment::Experiment() : ressource(NULL){

        // information
        id = "NoId";
        description = "";
        author = "";
        comments = "";
        dateOfCreation = QDateTime::currentDateTime();

        // simulation
        onlyIfEntityIsStable = true;
        timeToWaitForStability = 300;
        duration = 1200;
        stopIfEntityIsNotInOnePiece = true;

        // mutations
        mutationsManager = new MutationsManager();

        // seed
        seedInfo.insert("type", "family");
        seedInfo.insert("familyName", "ant");
    }

    Experiment::Experiment(QVariant data) {

        QVariantMap map = data.toMap();

        // TODO
        //if(map["version"].toString().compare(EXP_FORMAT_VERSION) != 0)
        //  throw new FormatVersionError("Exp", map["version"]);

        // information
        id          = map["id"].toString();
        description = map["description"].toString();
        author      = map["author"].toString();
        comments    = map["comments"].toString();
        dateOfCreation = QDateTime::fromString(map["dateOfCreation"].toString(),"yyyy-MM-dd hh:mm:ss");

        // simulation
        duration = 1;//map["duration"].toInt();
        timeToWaitForStability = map["timeToWaitForStability"].toInt();
        onlyIfEntityIsStable = map["onlyIfEntityIsStable"].toBool();
        stopIfEntityIsNotInOnePiece = map["stopIfEntityIsNotInOnePiece"].toBool();

        // mutations
        mutationsManager = new MutationsManager(map["mutations"]);

        // seed TODO
        seedInfo = map["seedInfo"].toMap();
    }

    QVariant Experiment::serialize() {
        QVariantMap map;

        // version
        map.insert("version",EXP_FORMAT_VERSION);

        // information
        map.insert("id",id);
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

        map.insert("seedInfo", seedInfo);
        return map;
    }
}
