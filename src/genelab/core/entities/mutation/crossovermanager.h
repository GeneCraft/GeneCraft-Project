#ifndef CROSSOVERMANAGER_H
#define CROSSOVERMANAGER_H

#include <QVariant>

namespace GeneLabCore {

    class CrossoverManager
    {
    public:
        CrossoverManager();
        QVariant onePointCross(QVariant a, QVariant b);
        QVariant twoPointCross(QVariant a, QVariant b);
        QVariant uniformCross (QVariant a, QVariant b);
    };

}

#endif // CROSSOVERMANAGER_H
