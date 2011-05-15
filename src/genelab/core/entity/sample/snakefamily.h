#ifndef SNAKEBUILDER_H
#define SNAKEBUILDER_H

#include "classes.h"
#include "core/entity/ogrebulletentityfamily.h"
#include "core/entity/entity.h"

namespace GeneLabCore {
    class SnakeFamily : OgreBulletEntityFamily
    {
        Q_OBJECT
    public:
        explicit SnakeFamily(QVariant data, QObject *parent = 0);

        OgreBulletEntity* createOgreBulletEntity();

        virtual Entity* createEntity() {
            return (Entity*) createOgreBulletEntity();
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
