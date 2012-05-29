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

#ifndef EFFECTOR_H
#define EFFECTOR_H

#include <QString>
#include <QVariant>
#include "genecraftcoreclasses.h"

namespace GeneCraftCore {

enum EffectorType { rotationalMotorEffector = 0, gripperEffector, flyingEffector, legEffector };

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

    // To create empty sensor serialization data
    static QVariant generateEmpty(QString typeName, int type);

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
