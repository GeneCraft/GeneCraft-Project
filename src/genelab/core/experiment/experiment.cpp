#include "experiment.h"

namespace GeneLabCore {
    Experiment::Experiment(QVariant data) {
        QVariantMap map = data.toMap();
        this->id = "WalkingSpider";//map["id"].toString();
        this->description = map["description"].toString();
        this->expData = map;

        this->expTime = 1200;

        seedInfo.insert("type", "family");
        seedInfo.insert("familyName", "spider");
    }

}
