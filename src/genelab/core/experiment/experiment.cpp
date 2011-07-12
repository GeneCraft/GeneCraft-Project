#include "experiment.h"

namespace GeneLabCore {
    Experiment::Experiment(QVariant data) {
        QVariantMap map = data.toMap();
        this->id = "experience1";//map["id"].toString();
        this->description = map["description"].toString();
        this->expData = map;
        this->resultsDirectory = QDir(id+"/results");
        if(!this->resultsDirectory.exists()) {
            this->resultsDirectory.mkpath(".");
        }
        this->maxGen = 10;
        this->popSize = 10;
        this->expTime = 1800;

        seedInfo.insert("type", "family");
        seedInfo.insert("familyName", "spider");
    }
}
