#include "crossovermanager.h"

namespace GeneLabCore {

    CrossoverManager::CrossoverManager()
    {
    }


    QVariant CrossoverManager::onePointCross(QVariant a, QVariant b) {
        QVariantMap entityA = a.toMap();
        QVariantMap entityB = b.toMap();
        QVariantMap resultEntity;


        return resultEntity;
    }

    QVariant CrossoverManager::twoPointCross(QVariant a, QVariant b) {
        QVariantMap entityA = a.toMap();
        QVariantMap entityB = b.toMap();
        QVariantMap resultEntity;


        return resultEntity;
    }

    QVariant CrossoverManager::uniformCross (QVariant a, QVariant b) {
        QVariantMap entityA = a.toMap();
        QVariantMap entityB = b.toMap();
        QVariantMap resultEntity;


        return resultEntity;
    }

}
