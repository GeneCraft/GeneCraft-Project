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

#ifndef BRAINOUTMOTOR_H
#define BRAINOUTMOTOR_H

#include <QVariant>

#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"
#include "genecraftcoreclasses.h"

namespace GeneCraftCore {

#define MIN_CONTRACTION 0.0f
#define MAX_CONTRACTION 1.0f
#define MIN_EXPANSION 0.0f
#define MAX_EXPANSION 1.0f

    /**
      * Internal class to box motor brain outputs
      */
    class BrainOutMotor
    {
    public:

        BrainOutMotor(btRotationalLimitMotor * motor,
                      btScalar min_Contraction = MIN_CONTRACTION, btScalar max_Contraction = MAX_CONTRACTION,
                      btScalar min_Expansion = MIN_EXPANSION, btScalar max_Expansion = MAX_EXPANSION);

        ~BrainOutMotor();

        BrainOutMotor(QVariant data, btRotationalLimitMotor* motor);

        QVariant serialize();

        // To generate an empty version
        static QVariant generateEmpty();

        void update();

        btRotationalLimitMotor * motor;
        BrainOut * boMaxMotorForce;
        BrainOut * boTargetVelocity;
    };

}

#endif // BRAINOUTMOTOR_H
