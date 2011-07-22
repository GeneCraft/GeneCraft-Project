#ifndef ROTATIONALMOTORS_H
#define ROTATIONALMOTORS_H

#include <QString>
#include "genelabcoreclasses.h"
#include "effector.h"
#include "brain/brainout.h"
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"

#define MIN_CONTRACTION 0.0f
#define MAX_CONTRACTION 1.0f
#define MIN_EXPANSION 0.0f
#define MAX_EXPANSION 1.0f


namespace GeneLabCore {

/**
  * Internal class to box motor brain outputs
  */
class BrainOutMotor
{
public:

    BrainOutMotor(btRotationalLimitMotor * motor,
                  float min_Contraction = MIN_CONTRACTION, float max_Contraction = MAX_CONTRACTION,
                  float min_Expansion = MIN_EXPANSION, float max_Expansion = MAX_EXPANSION) : motor(motor)
    {
        boMaxMotorForce = new BrainOut(min_Contraction,max_Contraction);
        boTargetVelocity = new BrainOut(min_Expansion,max_Expansion);
    }
    ~BrainOutMotor() {
        delete this->boMaxMotorForce;
        delete this->boTargetVelocity;
    }

    BrainOutMotor(QVariant data, btRotationalLimitMotor* motor) : motor(motor){
        QVariantMap outMap = data.toMap();

        // new version
        if(outMap.contains("contractionOutput")) {
            boMaxMotorForce = new BrainOut(outMap["contractionOutput"]);
            boTargetVelocity = new BrainOut(outMap["expansionOutput"]);
        }
        // old version
        else {
            QVariantList dataL = outMap["brainOuts"].toList();
            boMaxMotorForce = new BrainOut(dataL[0]);
            boTargetVelocity = new BrainOut(dataL[1]);
        }
    }

    QVariant serialize()  {

        QVariantMap data;

        // old version
        // QVariantList outs;
        // outs.append(boMaxMotorForce->serialize());
        // outs.append(boTargetVelocity->serialize());
        // data.insert("brainOuts", (QVariantList)outs);

        // new version
        data.insert("contractionOutput",boMaxMotorForce->serialize());
        data.insert("expansionOutput",boTargetVelocity->serialize());

        return data;
    }

    // To generate an empty version
    static QVariant generateEmpty(){

        QVariantMap data;
        BrainOut boContraction(MIN_CONTRACTION,MAX_CONTRACTION);
        BrainOut boExpansion(MIN_EXPANSION,MAX_EXPANSION);
        data.insert("contractionOutput",boContraction.serialize());
        data.insert("expansionOutput",boExpansion.serialize());
        return data;
    }

    void update()
    {
        motor->m_maxMotorForce
                = (boMaxMotorForce->getValue() + boTargetVelocity->getValue())*20000;
        motor->m_targetVelocity
                = (boTargetVelocity->getValue() - boMaxMotorForce->getValue())*5;
    }

    btRotationalLimitMotor * motor;
    BrainOut * boMaxMotorForce;
    BrainOut * boTargetVelocity;
};

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * A rotational motors is an effector to allows entities to move.
 *
 * This effector contains 3 motors (one for each axis). This element is connected to
 * a bone.
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class RotationalMotorsEffector : public Effector
{
public:

    RotationalMotorsEffector(Bone * bone, btGeneric6DofConstraint * constraint);
    RotationalMotorsEffector(QVariant data, Bone * bone, btGeneric6DofConstraint* ct);
    ~RotationalMotorsEffector();

    // To connect to brain
    void connectMotor(int i);

    // To disconnect from brain
    void disconnectMotor(int i);

    // To know if the motor is disabled
    bool isDisable()        { return m_isDisable; }

    // To know the origins of motors actions
    int getOutPutsFrom()    { return outputsFrom; }

    // To get bone
    Bone *getBone() { return bone; }

    BrainOutMotor *getBrainOutputs(int i) { return brainMotorOutputs[i]; }

    // To get a seralised representation of effector
    virtual QVariant serialize();

//    static const int OUTPUTS_FROM_NORMAL_POSITION;
//    static const int OUTPUTS_FROM_BRAIN;
//    static const int OUTPUTS_FROM_RANDOM;


    // used to set the origins of motors actions
    void setOutputsFrom(int outputsFrom);

    // used to disable effector
    void disable();

    // used to update motors
    void step();

private:

    // bone
    Bone *bone;

    // origin of motor
    btGeneric6DofConstraint * constraint;

    // effector is active
    bool m_isDisable;

    // motor action define by : random, brain or normal position
    int outputsFrom;

    // used for random outputs
    SinusIn* sinusIn[2];

    // Three motors by muscle (X,Y,Z)
    BrainOutMotor * brainMotorOutputs[3];

    // Stabilisation properties
    btScalar normalPositionMaxError;
    btScalar normalPositionFactor;
};

//const int RotationalMotorsModifier::OUTPUTS_FROM_NORMAL_POSITION = 0;
//const int RotationalMotorsModifier::OUTPUTS_FROM_BRAIN = 1;
//const int RotationalMotorsModifier::OUTPUTS_FROM_RANDOM = 2;

}

#endif // ROTATIONALMOTORS_H
