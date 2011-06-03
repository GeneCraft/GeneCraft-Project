#include "bonepropertiescontroller.h"
#include "ui_bonepropertiescontroller.h"

// Entity
#include "entity.h"

// Shape
#include "bone.h"
#include "fixation.h"
#include "treeshape.h"

// Sensors
#include "sensor.h"
#include "positionsensor.h"
#include "gyroscopicsensor.h"
#include "accelerometersensor.h"

// Effector
#include "rotationalmotorsmodifier.h"

BonePropertiesController::BonePropertiesController(QWidget *parent) :
    QWidget(parent), ui(new Ui::BonePropertiesController), bone(0)
{
    ui->setupUi(this);

    connect(this->ui->pbSaveChanges,SIGNAL(pressed()),this,SLOT(saveChanges()));
    connect(this->ui->pbDelete,SIGNAL(pressed()),this,SLOT(deleteBone()));
    //connect(this->ui->pbRandomValues,SIGNAL(pressed()),this,SLOT(randomValues()));
    //connect(this->ui->pbResetMotors,SIGNAL(pressed()),this,SLOT(resetMotors()));
    connect(this->ui->rbOutFrom_Random,SIGNAL(clicked()),this,SLOT(setOutFrom()));
    connect(this->ui->rbOutFrom_Brain,SIGNAL(clicked()),this,SLOT(setOutFrom()));
    connect(this->ui->rbOutFrom_Disable,SIGNAL(clicked()),this,SLOT(setOutFrom()));
    connect(this->ui->rbOutFrom_NormalPosition,SIGNAL(clicked()),this,SLOT(setOutFrom()));

    connect(this->ui->dEulerRotY,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
    connect(this->ui->dEulerRotZ,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));

    connect(this->ui->dAngularLowerLimitX,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
    connect(this->ui->dAngularLowerLimitY,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
    connect(this->ui->dAngularLowerLimitZ,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));

    connect(this->ui->dAngularUpperLimitX,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
    connect(this->ui->dAngularUpperLimitY,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
    connect(this->ui->dAngularUpperLimitZ,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
}

void BonePropertiesController::setOutFrom()
{
    if(ui->rbOutFrom_Random->isChecked())
        bone->setRandomMotors();
    else if(ui->rbOutFrom_Brain->isChecked())
        bone->setBrainMotors();
    else if(ui->rbOutFrom_Disable->isChecked())
        bone->disableMotors();
    else if(ui->rbOutFrom_NormalPosition->isChecked())
        bone->setNormalPositionMotors();

    // enable only for disabled outputs
    this->ui->gbMotorsTest->setEnabled(ui->rbOutFrom_Disable->isChecked());

    // update fields
    setBone(bone);
}

BonePropertiesController::~BonePropertiesController()
{
    delete ui;
}

void BonePropertiesController::deleteBone()
{
    delete bone;
    bone = 0;
}

void BonePropertiesController::randomValues()
{
    if(bone != 0)
    {
        bone->setRandomMotors();
        setBone(bone);
    }
}

void BonePropertiesController::resetMotors()
{
    if(bone != 0)
    {
        bone->resetMotors();
        setBone(bone);
    }
}

void BonePropertiesController::saveChanges()
{
    if(bone != 0)
    {
        btGeneric6DofConstraint *constraint = bone->getParentConstraint();


//        constraint->getFrameOffsetA().getBasis().setEulerZYX(this->ui->leEulerRotX->text().toFloat(),
//                                                                   this->ui->leEulerRotY->text().toFloat(),
//                                                                   this->ui->leEulerRotZ->text().toFloat());
        bone->setyAxis(this->ui->dEulerRotY->value() / 100.0);
        bone->setZAxis(this->ui->dEulerRotZ->value() / 100.0);

        this->ui->lInitRot_Yaw->setText(QString::number(this->ui->dEulerRotY->value() / 100.0));
        this->ui->lInitRot_Roll->setText(QString::number(this->ui->dEulerRotZ->value() / 100.0));

//        constraint->getFrameOffsetA().getBasis().setEulerZYX(this->ui->dEulerRotX->value() / 100.0,
//                                                                   this->ui->dEulerRotY->value() / 100.0,
//                                                                   this->ui->dEulerRotZ->value() / 100.0);


        btRotationalLimitMotor *motor;
        for(int i=0;i<3;i++)
        {
            motor = constraint->getRotationalLimitMotor(i);

            switch(i)
            {
                case 0 :

                    motor->m_enableMotor = this->ui->cbEnable_m1->isChecked();
                    motor->m_targetVelocity = this->ui->leTargetVelocity_m1->text().toFloat();
                    motor->m_maxMotorForce = this->ui->leMaxMotorForce_m1->text().toFloat();
//                    motor->m_maxLimitForce = this->ui->leMaxLimitForce_m1->text().toFloat();
//                    motor->m_bounce = this->ui->leBounce_m1->text().toFloat();
//                    motor->m_damping = this->ui->leDamping_m1->text().toFloat();

                    motor->m_loLimit = this->ui->dAngularLowerLimitX->value() / 100.0;
                    motor->m_hiLimit = this->ui->dAngularUpperLimitX->value() / 100.0;

                    this->ui->lAngularLowerLimitX->setText(QString::number(motor->m_loLimit));
                    this->ui->lAngularUpperLimitX->setText(QString::number(motor->m_hiLimit));

                    break;

                case 1 :
                    motor->m_enableMotor = this->ui->cbEnable_m2->isChecked();
                    motor->m_targetVelocity = this->ui->leTargetVelocity_m2->text().toFloat();
                    motor->m_maxMotorForce = this->ui->leMaxMotorForce_m2->text().toFloat();
//                    motor->m_maxLimitForce = this->ui->leMaxLimitForce_m2->text().toFloat();
//                    motor->m_bounce = this->ui->leBounce_m2->text().toFloat();
//                    motor->m_damping = this->ui->leDamping_m2->text().toFloat();

                    motor->m_loLimit = this->ui->dAngularLowerLimitY->value() / 100.0;
                    motor->m_hiLimit = this->ui->dAngularUpperLimitY->value() / 100.0;

                    this->ui->lAngularLowerLimitY->setText(QString::number(motor->m_loLimit));
                    this->ui->lAngularUpperLimitY->setText(QString::number(motor->m_hiLimit));

                    break;

                case 2 :
                    motor->m_enableMotor = this->ui->cbEnable_m3->isChecked();
                    motor->m_targetVelocity = this->ui->leTargetVelocity_m3->text().toFloat();
                    motor->m_maxMotorForce = this->ui->leMaxMotorForce_m3->text().toFloat();
//                    motor->m_maxLimitForce = this->ui->leMaxLimitForce_m3->text().toFloat();
//                    motor->m_bounce = this->ui->leBounce_m3->text().toFloat();
//                    motor->m_damping = this->ui->leDamping_m3->text().toFloat();

                    motor->m_loLimit = this->ui->dAngularLowerLimitZ->value() / 100.0;
                    motor->m_hiLimit = this->ui->dAngularUpperLimitZ->value() / 100.0;

                    this->ui->lAngularLowerLimitZ->setText(QString::number(motor->m_loLimit));
                    this->ui->lAngularUpperLimitZ->setText(QString::number(motor->m_hiLimit));

                    break;
            }
        }
    }
}

void BonePropertiesController::setBone(Bone * bone)
{
    this->bone = bone;

    if(bone != 0)
    {
        btGeneric6DofConstraint *constraint = bone->getParentConstraint();

        // Local transform
        disconnect(this->ui->dEulerRotY,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
        disconnect(this->ui->dEulerRotZ,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));

        btScalar eulerYaw,eulerRoll,eulerPitch;
        constraint->getFrameOffsetA().getBasis().getEulerZYX(eulerYaw,eulerRoll,eulerPitch);
        // this->ui->leEulerRotX->setText(QString().setNum(eulerPitch));
        // this->ui->leEulerRotY->setText(QString().setNum(eulerRoll));
        // this->ui->leEulerRotZ->setText(QString().setNum(eulerYaw));
        this->ui->dEulerRotY->setValue(bone->getYAxis() * 100/*eulerRoll * 100*/);
        this->ui->dEulerRotZ->setValue(bone->getZAxis() * 100/*eulerYaw * 100*/);

        this->ui->lInitRot_Yaw->setText(QString::number(bone->getYAxis()));
        this->ui->lInitRot_Roll->setText(QString::number(bone->getZAxis()));

        connect(this->ui->dEulerRotY,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
        connect(this->ui->dEulerRotZ,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));

        // Motors Effector
        if(!bone->getRotationalMotorsModifier()->isDisable())
        {
            switch(bone->getRotationalMotorsModifier()->getOutPutsFrom())
            {
            case 1 /*RotationalMotorsModifier::OUTPUTS_FROM_BRAIN*/ : this->ui->rbOutFrom_Brain->setChecked(true);  break;
            case 2 /*RotationalMotorsModifier::OUTPUTS_FROM_RANDOM*/: this->ui->rbOutFrom_Random->setChecked(true); break;
            case 0 /*RotationalMotorsModifier::OUTPUTS_FROM_NORMAL_POSITION*/ : this->ui->rbOutFrom_NormalPosition->setChecked(true); break;
            }
        }
        else
            this->ui->rbOutFrom_Disable->setChecked(true);

        // enable only for disabled outputs
        this->ui->gbMotorsTest->setEnabled(bone->getRotationalMotorsModifier()->isDisable());

        // Angular Limit Motors
        btRotationalLimitMotor *motor;
        for(int i=0;i<3;i++)
        {
            motor = constraint->getRotationalLimitMotor(i);

            switch(i)
            {
            case 0 :

                this->ui->cbEnable_m1->setChecked(motor->m_enableMotor);
                this->ui->leTargetVelocity_m1->setText(QString().setNum(motor->m_targetVelocity));
                this->ui->leMaxMotorForce_m1->setText(QString().setNum(motor->m_maxMotorForce));
//                this->ui->leMaxLimitForce_m1->setText(QString().setNum(motor->m_maxLimitForce));
//                this->ui->leBounce_m1->setText(QString().setNum(motor->m_bounce));
//                this->ui->leDamping_m1->setText(QString().setNum(motor->m_damping));

                // Init motor X
                disconnect(this->ui->dAngularLowerLimitX,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
                disconnect(this->ui->dAngularUpperLimitX,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
                this->ui->dAngularLowerLimitX->setValue(btNormalizeAngle(motor->m_loLimit) * 100);
                this->ui->dAngularUpperLimitX->setValue(btNormalizeAngle(motor->m_hiLimit) * 100);
                this->ui->lAngularLowerLimitX->setText(QString::number(motor->m_loLimit));
                this->ui->lAngularUpperLimitX->setText(QString::number(motor->m_hiLimit));
                connect(this->ui->dAngularLowerLimitX,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
                connect(this->ui->dAngularUpperLimitX,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));

                break;
            case 1 :
                this->ui->cbEnable_m2->setChecked(motor->m_enableMotor);
                this->ui->leTargetVelocity_m2->setText(QString().setNum(motor->m_targetVelocity));
                this->ui->leMaxMotorForce_m2->setText(QString().setNum(motor->m_maxMotorForce));
//                this->ui->leMaxLimitForce_m2->setText(QString().setNum(motor->m_maxLimitForce));
//                this->ui->leBounce_m2->setText(QString().setNum(motor->m_bounce));
//                this->ui->leDamping_m2->setText(QString().setNum(motor->m_damping));

                // Init motor Y
                disconnect(this->ui->dAngularLowerLimitY,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
                disconnect(this->ui->dAngularUpperLimitY,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
                this->ui->dAngularLowerLimitY->setValue(btNormalizeAngle(motor->m_loLimit) * 100);
                this->ui->dAngularUpperLimitY->setValue(btNormalizeAngle(motor->m_hiLimit) * 100);
                this->ui->lAngularLowerLimitY->setText(QString::number(motor->m_loLimit));
                this->ui->lAngularUpperLimitY->setText(QString::number(motor->m_hiLimit));
                connect(this->ui->dAngularLowerLimitY,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
                connect(this->ui->dAngularUpperLimitY,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));

                break;
            case 2 :
                this->ui->cbEnable_m3->setChecked(motor->m_enableMotor);
                this->ui->leTargetVelocity_m3->setText(QString().setNum(motor->m_targetVelocity));
                this->ui->leMaxMotorForce_m3->setText(QString().setNum(motor->m_maxMotorForce));
//                this->ui->leMaxLimitForce_m3->setText(QString().setNum(motor->m_maxLimitForce));
//                this->ui->leBounce_m3->setText(QString().setNum(motor->m_bounce));
//                this->ui->leDamping_m3->setText(QString().setNum(motor->m_damping));

                // Init motor Z
                disconnect(this->ui->dAngularLowerLimitZ,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
                disconnect(this->ui->dAngularUpperLimitZ,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
                this->ui->dAngularLowerLimitZ->setValue(btNormalizeAngle(motor->m_loLimit) * 100);
                this->ui->dAngularUpperLimitZ->setValue(btNormalizeAngle(motor->m_hiLimit) * 100);
                this->ui->lAngularLowerLimitZ->setText(QString::number(motor->m_loLimit));
                this->ui->lAngularUpperLimitZ->setText(QString::number(motor->m_hiLimit));
                connect(this->ui->dAngularLowerLimitZ,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
                connect(this->ui->dAngularUpperLimitZ,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
                break;
            }
        }

        // init promoted fixation properties
        ui->fixationProperties->setFixation(bone->getEndFixation());
        ui->fixationProperties->setFormTitle("End fixation controller");
    }
}

