#include "experiment.h"

#include "mutation/mutationsmanager.h"

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

        // information
        id          = map["id"].toString();
        description = map["description"].toString();
        author      = map["author"].toString();
        comments    = map["comments"].toString();
        dateOfCreation = QDateTime::fromString(map["dateOfCreation"].toString(),"yyyy-MM-dd hh:mm:ss");

        // simulation
        duration = map["duration"].toInt();
        timeToWaitForStability = map["timeToWaitForStability"].toInt();
        onlyIfEntityIsStable = map["onlyIfEntityIsStable"].toBool();
        stopIfEntityIsNotInOnePiece = map["stopIfEntityIsNotInOnePiece"].toBool();

        // mutations
        mutationsManager = new MutationsManager(map["mutations"]);

        // seed TODO
        seedInfo.insert("type", "family");
        seedInfo.insert("familyName", "spider");
    }

    QVariant Experiment::serialize() {
        QVariantMap map;

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

        return map;
    }
}
