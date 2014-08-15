/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QList>

#include "genecraftcoreclasses.h"
#include "brain/brainin.h"

namespace GeneCraftCore {

enum SensorType { gyroscopicSensor, accelerometerSensor, positionSensor, contactSensor, boxSmellSensor, distanceSensor };

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

public:

    // To create a sensor
    explicit Sensor(Fixation * fixation, QObject *parent = 0);

    // To create a sensor from serialization data
    Sensor(QVariant data, Fixation* fixation);

    // To generate empty sensor
    static QVariant generateEmpty(QString typeName, int type);

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
