#include "spawn.h"

#include "tools.h"

#include <QVariantMap>
#include <QDebug>

namespace GeneLabCore {


    Spawn::Spawn(QVariant data) {
        QVariantMap dMap = data.toMap();
        this->type = (SpawnType)dMap["type"].toInt();
        switch(type) {
        case Position:
            this->position = btVector3(dMap["x"].toFloat(),
                                       dMap["y"].toFloat(),
                                       dMap["z"].toFloat());
            qDebug() << "Spawn créé : "<< this->type << this->position.getX() << this->position.getY() << this->position.getZ();
            break;
        case Zone:
            this->minPosition = btVector3(dMap["minX"].toFloat(),
                                          dMap["minY"].toFloat(),
                                          dMap["minZ"].toFloat());

            this->maxPosition = btVector3(dMap["maxX"].toFloat(),
                                          dMap["maxY"].toFloat(),
                                          dMap["maxZ"].toFloat());
            qDebug() << "Zone créé : "<< this->type << this->minPosition.getX() << this->minPosition.getY() << this->minPosition.getZ();
            qDebug() << "          : "<< this->type << this->maxPosition.getX() << this->maxPosition.getY() << this->maxPosition.getZ();
            break;
        }
    }

    Spawn::Spawn(SpawnType type, btVector3 position) {
        this->type = type;
        this->position = position;
    }

    Spawn::Spawn(SpawnType type, btVector3 topleftCorner, btVector3 bottomRightCorner) {
        this->type = type;
        this->minPosition = topleftCorner;
        this->maxPosition = bottomRightCorner;
    }

    btVector3 Spawn::getSpawnPosition() {
        switch(type) {

        case Position:
            return this->position;

        case Zone:
            btVector3 spawn = btVector3();
            spawn.setX(Tools::random(minPosition.x(), maxPosition.x()));
            spawn.setY(Tools::random(minPosition.y(), maxPosition.y()));
            spawn.setZ(Tools::random(minPosition.z(), maxPosition.z()));
            return spawn;
        }
    }

}
