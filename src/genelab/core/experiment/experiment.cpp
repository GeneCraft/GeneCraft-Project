#include "experiment.h"

#include "mutation/mutationsmanager.h"
#include "factories/btworldfactory.h"
#include "btoworldfactory.h"

#define EXP_FORMAT_VERSION 0.1

namespace GeneLabCore {

Experiment::Experiment() : ressource(NULL){

        // information
        id = "NoId";
        description = "";
        author = "";
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
        seedInfo.insert("family", "ant");

        evalFunction  = QString("(function() {")+
                                    QString("return entity.bodyHeight.mean * entity.rootRelVelocity.sum ")+
                                    QString("- entity.bodySensors.sum + entity.bodyBrainSize.value")+
                                    QString("})");

        validityFunction = "(function() {return entity.bodySensors.max < 3; })";
        endFunction     = "(function(int actualStep) { return entity.brainActivity.sum > 200; })";
        dieFunction     = "(function() { return entity.rootYRelVelocity.sum < 0; })";


    }

    Experiment::Experiment(QVariant data) : ressource(NULL) {

        QVariantMap map = data.toMap();

        // TODO
        //if(map["version"].toString().compare(EXP_FORMAT_VERSION) != 0)
        //  throw new FormatVersionError("Exp", map["version"]);

        // information
        id              = map["id"].toString();
        description     = map["description"].toString();
        author          = map["author"].toString();
        comments        = map["comments"].toString();
        online          = map["online"].toBool();
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
        map.insert("online", online);

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
        return map;
    }
}
