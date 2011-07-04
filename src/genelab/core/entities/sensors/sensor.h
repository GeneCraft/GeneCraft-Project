#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QList>

#include "genelabcoreclasses.h"
#include "brain/brainin.h"

namespace GeneLabCore {

enum SensorType { gyroscopic, accelerometer, position };

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * A sensor is attached to a fixation and contrains a collection of brain inputs.
 * Its step method is used to update the value of their brain inputs. *
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class Sensor : public QObject
{
    Q_OBJECT

public:

    // To create a sensor
    explicit Sensor(Fixation * fixation, QObject *parent = 0);

    // To create a sensor from serialization data
    Sensor(QVariant data, Fixation* fixation);

    // To delete the sensor
    ~Sensor() {

        // delete all brain inputs
        foreach(BrainIn* i, this->brainInputs)
            delete i;
    }

    // To serialize
    virtual QVariant serialize();

    // To get the type name
    const QString &getTypeName() { return typeName; }

    // To get brain inputs
    const QList<BrainIn *> getInputs() { return brainInputs; }

    // To get the fixation where the sensor is attached
    inline Fixation *getFixation() { return fixation; }

signals:

public slots:

    // To update brain inputs values
    virtual void step() = 0;

protected:

    QString typeName;
    SensorType type;

    Fixation * fixation;
    QList<BrainIn *> brainInputs;

};

}
#endif // SENSOR_H
