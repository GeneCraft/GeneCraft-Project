#ifndef BULLETSCENE_H
#define BULLETSCENE_H

#include <QObject>
#include "classes.h"

namespace GeneLabOgreBullet {
    class BulletScene : QObject
    {
        Q_OBJECT
    public:
        explicit BulletScene(QObject *parent = 0);

    signals:

    public slots:

    };
}

#endif // BULLETSCENE_H
