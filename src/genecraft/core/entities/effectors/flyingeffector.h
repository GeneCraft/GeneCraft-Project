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

#ifndef FLYINGEFFECTOR_H
#define FLYINGEFFECTOR_H

#include "genecraftcoreclasses.h"
#include "effector.h"
#include "brain/brainout.h"
#include "LinearMath/btScalar.h"

namespace GeneCraftCore {

class FlyingEffector : public Effector
{
public:

    // To create
    FlyingEffector(Fixation *fixation);

    // To create from data
    FlyingEffector(QJsonObject data, Fixation *fixation);

    // To create empty effector serialization data
    static QJsonObject generateEmpty();

    // To update world.
    void step();

    // To serialize
    QJsonObject serialize();

private:

    Fixation *fixation;
    BrainOut *impulseX, *impulseY, *impulseZ;
};

}

#endif // FLYINGEFFECTOR_H
