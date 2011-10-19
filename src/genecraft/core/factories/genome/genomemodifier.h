#ifndef GENOMEMODIFIER_H
#define GENOMEMODIFIER_H

#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include "btBulletCollisionCommon.h"

namespace GeneCraftCore {

class GenomeModifier : public QObject
{
    Q_OBJECT
public:
    explicit GenomeModifier(QObject *parent = 0);

    // Set the modifications parameters
    void setPhysicalSymmetry(btScalar alpha);
    void setPhysicalScale   (btScalar scale);
    void setNeuralSymmetry  (btScalar alpha);
    void setNeuralRotation  (btScalar alpha, btScalar delta);

    // The modification will be applied to the bone element and all bone childs
    QVariant modify(QVariant element);

    void applyBoneSymmetry(QVariantMap& element);
    void applyBoneScale   (QVariantMap& element);

    void applyFixSymmetry(QVariantMap& element);
    void applyFixScale(QVariantMap& element);


protected:
    bool isPhysSym;
    bool isPhysScale;
    bool isNeuralSym;
    bool isNeuralRot;

    btScalar physSym;
    btScalar physScale;
    btScalar neuralSym;
    btScalar neuralAlpha;
    btScalar neuralDelta;

signals:

public slots:

};

}
#endif // GENOMEMODIFIER_H
