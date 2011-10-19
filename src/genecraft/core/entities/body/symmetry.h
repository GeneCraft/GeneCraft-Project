#ifndef SYMMETRY_H
#define SYMMETRY_H

#include <QObject>
#include <QList>
#include "genome/genomemodifier.h"
#include "btBulletCollisionCommon.h"
#include "body/bone.h"

namespace GeneCraftCore {

    class Symmetry : public QObject
    {
        Q_OBJECT
    public:
        explicit Symmetry(QObject *parent = 0);

        btScalar physSymmetry;
        btScalar neuralSymmetry;
        Bone*    model;
        Bone*    copy;
        QList<GenomeModifier*> modifiers;

    signals:

    public slots:

    };
}

#endif // SYMMETRY_H
