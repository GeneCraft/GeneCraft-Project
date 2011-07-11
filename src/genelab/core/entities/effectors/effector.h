#ifndef EFFECTOR_H
#define EFFECTOR_H

#include <QObject>
#include <QString>
#include "genelabcoreclasses.h"

namespace GeneLabCore {

enum EffectorType { rotationalMotor };

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * An effector is an element that allows entities to interact with the world.
 *
 * The stucture is used to interpret brain outputs.
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class Effector : public QObject
{

public:

    // To create
    explicit Effector(QObject *parent = 0);

    // To create from serialization data
    Effector(QVariant data);

    // To serialize
    virtual QVariant serialize();

    // To get the type name
    const QString &getTypeName() { return typeName; }

    // To get brain outputs
    const QList<BrainOut*> getOutputs() { return outs; }

    // To update world.
    virtual void step() = 0;

protected:
    QString typeName;
    QList<BrainOut*> outs;

};
}
#endif // EFFECTOR_H
