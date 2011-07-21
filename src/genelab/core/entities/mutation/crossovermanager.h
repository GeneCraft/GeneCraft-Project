#ifndef CROSSOVERMANAGER_H
#define CROSSOVERMANAGER_H

#include <QVariant>

namespace GeneLabCore {

    class CrossoverManager
    {
    public:
        CrossoverManager();
        static QVariant onePointCross(QVariant a, QVariant b);
        static QVariant twoPointCross(QVariant a, QVariant b);
        static QVariant uniformCross (QVariant a, QVariant b);
    };

}

#endif // CROSSOVERMANAGER_H
