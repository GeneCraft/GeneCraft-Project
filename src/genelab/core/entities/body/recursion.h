#ifndef RECURSION_H
#define RECURSION_H

#include <QObject>
#include <QList>

#include "genome/genomemodifier.h"
#include "btBulletCollisionCommon.h"

namespace GeneCraftCore {

    class Bone;

    class Recursion : public QObject
    {
        Q_OBJECT
    public:
        explicit Recursion(QObject *parent = 0);

        btScalar        physScale;
        btScalar        neuralAlpha;
        btScalar        neuralDelta;
        int             depth;
        QList<Bone*>    tail;
        QList<Bone*>    childs;
        Bone*           model;
        QList<GenomeModifier*> modifiers;

    signals:

    public slots:

    };

}

#endif // RECURSION_H
