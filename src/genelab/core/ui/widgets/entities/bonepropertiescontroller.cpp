#include "bonepropertiescontroller.h"
#include "ui_bonepropertiescontroller.h"

// Entity
#include "entity.h"

// Shape
#include "body/bone.h"
#include "body/fixation.h"
#include "body/treeshape.h"

// Sensors
#include "sensors/sensor.h"
#include "sensors/positionsensor.h"
#include "sensors/gyroscopicsensor.h"
#include "sensors/accelerometersensor.h"

// Effector
#include "modifiers/rotationalmotorsmodifier.h"

BonePropertiesController::BonePropertiesController(QWidget *parent) :
    QWidget(parent), ui(new Ui::BonePropertiesController), bone(0)
{
    ui->setupUi(this);

    connect(this->ui->pbSaveChanges,SIGNAL(pressed()),this,SLOT(saveChanges()));
    //connect(this->ui->pbDelete,SIGNAL(pressed()),this,SLOT(deleteBone()));
    connect(this->ui->pbApplySize,SIGNAL(pressed()),this,SLOT(changeSize()));
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


    connect(this->ui->sLength,SIGNAL(valueChanged(int)),this,SLOT(changeLengthFromSlider(int)));
    connect(this->ui->sRadius,SIGNAL(valueChanged(int)),this,SLOT(changeRadiusFromSlider(int)));

    connect(this->ui->fixationProperties,SIGNAL(rigidBodySelected(btRigidBody*)),this,SLOT(rigidBodySelectedFromFix(btRigidBody*)));
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

void BonePropertiesController::changeLengthFromSlider(int value)
{
    bone->setSize(this->ui->sRadius->value()/1000.0, value/1000.0);

    this->ui->leLength->setText(QString::number(value / 1000.0));
}

void BonePropertiesController::changeRadiusFromSlider(int value)
{
    bone->setSize(value/1000.0, this->ui->sLength->value()/1000.0);

    this->ui->leRadius->setText(QString::number(value / 1000.0));
}

void BonePropertiesController::deleteBone()
{
    //delete bone;
    //bone = 0;
}

void BonePropertiesController::changeSize()
{
    bone->setSize(this->ui->leRadius->text().toDouble(),this->ui->leLength->text().toDouble());
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

void BonePropertiesController::rigidBodySelectedFromFix(btRigidBody *rigidBody)
{
    emit rigidBodySelected(rigidBody);
}

void BonePropertiesController::saveChanges()
{
    if(bone != 0)
    {

        btGeneric6DofConstraint *constraint = bone->getParentConstraint();

        // ANGULAR PARAMETERS

        // Local transform (Yaw / Roll)
        bone->setyAxis(this->ui->dEulerRotY->value() / 100.0);
        bone->setZAxis(this->ui->dEulerRotZ->value() / 100.0);
        this->ui->lInitRot_Yaw->setText(QString::number(this->ui->dEulerRotY->value() / 100.0));
        this->ui->lInitRot_Roll->setText(QString::number(this->ui->dEulerRotZ->value() / 100.0));

        // Limits & motor effector
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
                    motor->m_loLimit = this->ui->dAngularLowerLimitX->value() / 100.0;
                    motor->m_hiLimit = this->ui->dAngularUpperLimitX->value() / 100.0;
                    this->ui->lAngularLowerLimitX->setText(QString::number(motor->m_loLimit));
                    this->ui->lAngularUpperLimitX->setText(QString::number(motor->m_hiLimit));
                    break;

                case 1 :
                    motor->m_enableMotor = this->ui->cbEnable_m2->isChecked();
                    motor->m_targetVelocity = this->ui->leTargetVelocity_m2->text().toFloat();
                    motor->m_maxMotorForce = this->ui->leMaxMotorForce_m2->text().toFloat();
                    motor->m_loLimit = this->ui->dAngularLowerLimitY->value() / 100.0;
                    motor->m_hiLimit = this->ui->dAngularUpperLimitY->value() / 100.0;
                    this->ui->lAngularLowerLimitY->setText(QString::number(motor->m_loLimit));
                    this->ui->lAngularUpperLimitY->setText(QString::number(motor->m_hiLimit));

                    break;

                case 2 :
                    motor->m_enableMotor = this->ui->cbEnable_m3->isChecked();
                    motor->m_targetVelocity = this->ui->leTargetVelocity_m3->text().toFloat();
                    motor->m_maxMotorForce = this->ui->leMaxMotorForce_m3->text().toFloat();
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
        // ANGULAR PARAMETERS
        btGeneric6DofConstraint *constraint = bone->getParentConstraint();

        // Local transform (Yaw / Roll)
        disconnect(this->ui->dEulerRotY,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
        disconnect(this->ui->dEulerRotZ,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));

        btScalar eulerYaw,eulerRoll,eulerPitch;
        constraint->getFrameOffsetA().getBasis().getEulerZYX(eulerYaw,eulerRoll,eulerPitch);
        this->ui->dEulerRotY->setValue(bone->getYAxis() * 100);
        this->ui->dEulerRotZ->setValue(bone->getZAxis() * 100);
        this->ui->lInitRot_Yaw->setText(QString::number(bone->getYAxis()));
        this->ui->lInitRot_Roll->setText(QString::number(bone->getZAxis()));

        connect(this->ui->dEulerRotY,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
        connect(this->ui->dEulerRotZ,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));

        // MOTOR EFFECTOR
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


        // TOOLS

        // Bone Size
        this->ui->leLength->setText(QString::number(bone->getLength()));
        this->ui->leRadius->setText(QString::number(bone->getRadius()));

        disconnect(this->ui->sLength,SIGNAL(valueChanged(int)),this,SLOT(changeLengthFromSlider(int)));
        disconnect(this->ui->sRadius,SIGNAL(valueChanged(int)),this,SLOT(changeRadiusFromSlider(int)));
        this->ui->sLength->setValue(bone->getLength() * 1000);
        this->ui->sRadius->setValue(bone->getRadius() * 1000);
        connect(this->ui->sLength,SIGNAL(valueChanged(int)),this,SLOT(changeLengthFromSlider(int)));
        connect(this->ui->sRadius,SIGNAL(valueChanged(int)),this,SLOT(changeRadiusFromSlider(int)));



        // SUB-WIDGET

        // init promoted fixation properties
        ui->fixationProperties->setFixation(bone->getEndFixation());
        ui->fixationProperties->setFormTitle("End fixation controller");
    }
}

