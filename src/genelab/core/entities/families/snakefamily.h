#ifndef SNAKEBUILDER_H
#define SNAKEBUILDER_H

#include "genelabcoreclasses.h"
#include "entityfamily.h"
#include "entity.h"

namespace GeneLabCore {
    class SnakeFamily : EntityFamily
    {
        Q_OBJECT
    public:
        explicit SnakeFamily(QVariant data, QObject *parent = 0);

        Entity* createEntity(btShapesFactory*);


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
