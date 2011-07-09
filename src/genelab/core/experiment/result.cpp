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
        QVariantMap resultData;
        resultData.insert("experiment", exp->getId());
        resultData.insert("fitness", (float)this->fitness);
        resultData.insert("genome", this->genome);
        resultData.insert("date", QDateTime::currentDateTime().toString());

        ressource->save(resultData);
    }

    /**
      * Load a result -> take it from the ressource
      */
    void Result::load(Ressource * r) {
        QVariantMap map = ressource->load().toMap();
        this->fitness = map["fitness"].toFloat();
    }
}
