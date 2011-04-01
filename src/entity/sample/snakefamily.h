#ifndef SNAKEBUILDER_H
#define SNAKEBUILDER_H

#include "classes.h"
#include "entity/ogrebulletentityfamily.h"
#include "entity.h"

namespace GeneLabOgreBullet {
    class SnakeFamily : OgreBulletEntityFamily
    {
        Q_OBJECT
    public:
        explicit SnakeFamily(QVariant data, QObject *parent = 0);

        OgreBulletEntity* build();

        virtual GeneLabCore::Entity* createEntity() {
            return (GeneLabCore::Entity*)build();
        }

        QVariant serialize();
        void load(QVariant data);

    signals:

    public slots:

    private:
        int length;
        float pieceLength;

    };
}
#endif // SNAKEBUILDER_H
