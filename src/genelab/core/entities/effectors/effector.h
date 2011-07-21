#ifndef EFFECTOR_H
#define EFFECTOR_H

#include <QString>
#include <QVariant>
#include "genelabcoreclasses.h"

namespace GeneLabCore {

enum EffectorType { rotationalMotorEffector = 0, gripperEffector, flyingEffector };

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
class Effector
{

public:

    // To create
    Effector(QString typeName, EffectorType type);

    // To create from serialization data
    Effector(QVariant data);

    // To serialize
    virtual QVariant serialize();

    // To get the type name
    const QString &getTypeName() { return typeName; }

    // To get brain outputs
    const QList<BrainOut*> getOutputs() { return brainOutputs; }

    // To update world.
    virtual void step() = 0;

protected:
    QString typeName;
    EffectorType type;
    QList<BrainOut*> brainOutputs;

};
}
#endif // EFFECTOR_H
