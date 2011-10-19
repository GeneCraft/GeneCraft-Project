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
