#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include "genelabcoreclasses.h"

namespace GeneLabCore {
    class World : public QObject
    {
        Q_OBJECT
    public:
        explicit World(QObject *parent = 0);

    signals:

    public slots:
        virtual void setup() = 0;

    };
}

#endif // WORLD_H
