#ifndef ENTITYFAMILY_H
#define ENTITYFAMILY_H

#include <QObject>
#include "genelabcoreclasses.h"

namespace GeneLabCore {

    class EntityFamily : public QObject
    {
        Q_OBJECT
    public:
        explicit EntityFamily(QObject *parent = 0);

        virtual Entity* createEntity() = 0;

        virtual QVariant serialize() = 0;

    signals:

    public slots:

    };
}
#endif // ENTITYFAMILY_H
