#ifndef SPAWN_H
#define SPAWN_H

#include <QObject>
#include "genelabcoreclasses.h"

#include "LinearMath/btVector3.h"

#include <QVariant>

namespace GeneLabCore {


    class Spawn : public QObject
    {
        Q_OBJECT
    public:
        enum SpawnType {
            Zone,
            Position,
        };

        Spawn(QVariant data);
        Spawn(SpawnType type, btVector3 position);
        Spawn(SpawnType type, btVector3 topleftCorner, btVector3 bottomRightCorner);

        btVector3 getSpawnPosition();

        SpawnType getType() { return this->type; }
        btVector3 getMinPos() { return this->minPosition; }
        btVector3 getMaxPos() { return this->maxPosition; }

    signals:

    public slots:

    protected:
        SpawnType type;
        // Position
        btVector3 position;
        // Zone
        btVector3 minPosition;
        btVector3 maxPosition;


    };

}

#endif // SPAWN_H
