#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QList>

#include "genelabcoreclasses.h"

namespace GeneLabCore {

/**
 * (c) GeneLab 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * A sensor is attached to a fixation and contrains a collection of brain inputs.
 * Its step method is used to update the value of their brain inputs.
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo & Cyprien Huissoud
 */
class Sensor : public QObject
{
    Q_OBJECT

public:
    explicit Sensor(Fixation * fixation, QObject *parent = 0);

    inline const QString &getTypeName() { return typeName; }

signals:

public slots:

    /**
     * Used to update brain inputs values.
     */
    virtual void step() = 0;

protected:

    QString typeName;

    Fixation * fixation;
    QList<BrainIn *> brainInputs;

};

}
#endif // SENSOR_H
