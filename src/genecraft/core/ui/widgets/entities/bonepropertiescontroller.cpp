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

#include "bonepropertiescontroller.h"
#include "ui_bonepropertiescontroller.h"

#include <cmath>

// Entity
#include "entity.h"

// Shape
#include "body/bone.h"
#include "body/fixation.h"
#include "body/treeshape.h"

// Brain
#include "brain/brainout.h"

// Sensors
#include "sensors/sensor.h"
#include "sensors/positionsensor.h"
#include "sensors/gyroscopicsensor.h"
#include "sensors/accelerometersensor.h"

// Effectors
#include "effectors/rotationalmotorseffector.h"

#include "events/inspectorsinputmanager.h"

#include <QTimer>


btScalar roundPrecision(btScalar n, int precision = 2)
{
      int precision_pow10 = pow(10,precision);
      n*=precision_pow10;
      n = ceil(n);
      n/=precision_pow10;
      return n;
}

BonePropertiesController::BonePropertiesController(QWidget *parent) :
    QWidget(parent), ui(new Ui::BonePropertiesController), bone(0)
{
    ui->setupUi(this);

    // -----------------
    // -- Connections --
    // -----------------

    // Delete
    connect(this->ui->pbDeleteBone,SIGNAL(pressed()),this,SLOT(deleteBone()));
    connect(this->ui->pbDeleteOnlyThisBone,SIGNAL(pressed()),this,SLOT(deleteBoneAndAttachChildrenToParent()));

    // Rotation
    connect(this->ui->dInitRot_Yaw,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
    connect(this->ui->dInitRot_Roll,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));

    // Angular limits
    connect(this->ui->dAngularLowerLimitX,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
    connect(this->ui->dAngularLowerLimitY,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
    connect(this->ui->dAngularLowerLimitZ,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
    connect(this->ui->dAngularUpperLimitX,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
    connect(this->ui->dAngularUpperLimitY,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
    connect(this->ui->dAngularUpperLimitZ,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
    connect(this->ui->pbValidateAngularInputs,SIGNAL(pressed()),this,SLOT(validateAngularInputs()));

    // Outputs from & Motors
    connect(this->ui->rbOutFrom_Random,SIGNAL(clicked()),this,SLOT(setOutFrom()));
    connect(this->ui->rbOutFrom_Brain,SIGNAL(clicked()),this,SLOT(setOutFrom()));
    connect(this->ui->rbOutFrom_Disable,SIGNAL(clicked()),this,SLOT(setOutFrom()));
    connect(this->ui->rbOutFrom_NormalPosition,SIGNAL(clicked()),this,SLOT(setOutFrom()));
    connect(this->ui->pbValidateMotorsValues,SIGNAL(pressed()),this,SLOT(saveChanges()));

    // Size
    connect(this->ui->sLength,SIGNAL(valueChanged(int)),this,SLOT(changeLengthFromSlider(int)));
    connect(this->ui->sRadius,SIGNAL(valueChanged(int)),this,SLOT(changeRadiusFromSlider(int)));
    connect(this->ui->pbApplySize,SIGNAL(pressed()),this,SLOT(changeSize()));

    // Effectors
    connect(this->ui->cbEffectorX,SIGNAL(stateChanged(int)),this,SLOT(cbEffectorX_stateChanged(int)));
    connect(this->ui->cbEffectorY,SIGNAL(stateChanged(int)),this,SLOT(cbEffectorY_stateChanged(int)));
    connect(this->ui->cbEffectorZ,SIGNAL(stateChanged(int)),this,SLOT(cbEffectorZ_stateChanged(int)));

    // Update
    //connect(this->ui->fixationProperties,SIGNAL(rigidBodySelected(btRigidBody*)),this,SLOT(rigidBodySelectedFromFix(btRigidBody*)));

    this->setEnabled(false);

    QTimer* timer = new QTimer();
    timer->setInterval(100);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

void BonePropertiesController::connectToInspectorInputManager(InspectorsInputManager *iim)
{
    // notifications
    connect(iim,SIGNAL(sBoneSelected(Bone*)),this,SLOT(setBone(Bone *)));
    connect(iim,SIGNAL(sBoneDeleted(Bone *)),this,SLOT(boneDeleted(Bone *)),Qt::DirectConnection);
    connect(iim,SIGNAL(sEntityDeleted(Entity *)),this,SLOT(entityDeleted(Entity *)),Qt::DirectConnection);

    // emission
    connect(this,SIGNAL(sBoneDeleted(Bone *)),iim,SLOT(boneDeleted(Bone *)),Qt::DirectConnection);
    //connect(this,SIGNAL(sBoneUpdated(Bone *)),iim,SLOT(boneUpdated(Bone*)));
}

void BonePropertiesController::boneDeleted(Bone *bone){
    if(bone == this->bone)
        setBone(NULL);
}

void BonePropertiesController::entityDeleted(Entity *) {

    setBone(NULL);
}

void BonePropertiesController::update() {
    if(this->bone != NULL) {
        // X
        BrainOutMotor* muscle = this->bone->getRotationalMotorsEffector()->getBrainOutputs(0);
        if(muscle) {
            this->ui->lblContractX->setText(QString::number(muscle->boMaxMotorForce->getValue(), 10, 2));
            this->ui->lblExpandX->setText(QString::number(muscle->boTargetVelocity->getValue(), 10, 2));
        } else {
            this->ui->lblContractX->setText(QString::number(0));
            this->ui->lblExpandX->setText(QString::number(0));
        }
        // Y
        muscle = this->bone->getRotationalMotorsEffector()->getBrainOutputs(1);
        if(muscle) {
            this->ui->lblContractY->setText(QString::number(muscle->boMaxMotorForce->getValue(), 10, 2));
            this->ui->lblExpandY->setText(QString::number(muscle->boTargetVelocity->getValue(), 10, 2));
        } else {
            this->ui->lblContractY->setText(QString::number(0));
            this->ui->lblExpandY->setText(QString::number(0));
        }
        // Z
        muscle = this->bone->getRotationalMotorsEffector()->getBrainOutputs(2);
        if(muscle) {
            this->ui->lblContractZ->setText(QString::number(muscle->boMaxMotorForce->getValue(), 10, 2));
            this->ui->lblExpandZ->setText(QString::number(muscle->boTargetVelocity->getValue(), 10, 2));
        } else {
            this->ui->lblContractZ->setText(QString::number(0));
            this->ui->lblExpandZ->setText(QString::number(0));
        }
    }
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
    if(bone->getParentFixation() != NULL)
        bone->getParentFixation()->removeBone(bone);

    Bone *old = bone;
    bone->remove();
    emit sBoneDeleted(bone); // will set bone to NULL
    delete old;
}

void BonePropertiesController::deleteBoneAndAttachChildrenToParent()
{
    if(bone->getParentFixation() != NULL)
        bone->getParentFixation()->removeBone(bone);

    Bone *old = bone;
    bone->removeOnly();
    emit sBoneDeleted(bone); // will set bone to NULL
    delete old;
}

void BonePropertiesController::changeSize()
{
    bone->setSize(this->ui->leRadius->text().toDouble(),this->ui->leLength->text().toDouble());
}

void BonePropertiesController::randomValues()
{
    if(bone)
    {
        bone->setRandomMotors();
        setBone(bone);
    }
}

void BonePropertiesController::resetMotors()
{
    if(bone)
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
    if(bone)
    {
        btGeneric6DofConstraint *constraint = bone->getParentConstraint();

        // ANGULAR PARAMETERS

        // Local transform (Yaw / Roll)
        bone->setyAxis(this->ui->dInitRot_Yaw->value() / 100.0);
        bone->setZAxis(this->ui->dInitRot_Roll->value() / 100.0);
        this->ui->lInitRot_Yaw->setText(QString::number(this->ui->dInitRot_Yaw->value() / 100.0));
        this->ui->lInitRot_Roll->setText(QString::number(this->ui->dInitRot_Roll->value() / 100.0));

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

    if(bone)
    {
        this->setEnabled(true);

        // Bone outputs
        // X
        BrainOutMotor* muscle = this->bone->getRotationalMotorsEffector()->getBrainOutputs(0);
        if(muscle) {
            this->ui->txtContractX->setText(muscle->boMaxMotorForce->getConnexionInfo().toString());
            this->ui->lblContractX->setText(QString::number(muscle->boMaxMotorForce->getValue(), 10, 2));
            this->ui->txtExpandX->setText(muscle->boTargetVelocity->getConnexionInfo().toString());
            this->ui->lblExpandX->setText(QString::number(muscle->boTargetVelocity->getValue(), 10, 2));
        } else {
            this->ui->txtContractX->setText("No muscle");
            this->ui->txtExpandX->setText("No muscle");
            this->ui->lblContractX->setText(QString::number(0));
            this->ui->lblExpandX->setText(QString::number(0));
        }
        // Y
        muscle = this->bone->getRotationalMotorsEffector()->getBrainOutputs(1);
        if(muscle) {
            this->ui->txtContractY->setText(muscle->boMaxMotorForce->getConnexionInfo().toString());
            this->ui->lblContractY->setText(QString::number(muscle->boMaxMotorForce->getValue(), 10, 2));
            this->ui->txtExpandY->setText(muscle->boTargetVelocity->getConnexionInfo().toString());
            this->ui->lblExpandY->setText(QString::number(muscle->boTargetVelocity->getValue(), 10, 2));
        } else {
            this->ui->txtContractY->setText("No muscle");
            this->ui->txtExpandY->setText("No muscle");
            this->ui->lblContractY->setText(QString::number(0));
            this->ui->lblExpandY->setText(QString::number(0));
        }
        // Z
        muscle = this->bone->getRotationalMotorsEffector()->getBrainOutputs(2);
        if(muscle) {
            this->ui->txtContractZ->setText(muscle->boMaxMotorForce->getConnexionInfo().toString());
            this->ui->lblContractZ->setText(QString::number(muscle->boMaxMotorForce->getValue(), 10, 2));
            this->ui->txtExpandZ->setText(muscle->boTargetVelocity->getConnexionInfo().toString());
            this->ui->lblExpandZ->setText(QString::number(muscle->boTargetVelocity->getValue(), 10, 2));
        } else {
            this->ui->txtContractZ->setText("No muscle");
            this->ui->txtExpandZ->setText("No muscle");
            this->ui->lblContractZ->setText(QString::number(0));
            this->ui->lblExpandZ->setText(QString::number(0));
        }

        // ANGULAR PARAMETERS
        btGeneric6DofConstraint *constraint = bone->getParentConstraint();

        // Local transform (Yaw / Roll)
        disconnect(this->ui->dInitRot_Yaw,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
        disconnect(this->ui->dInitRot_Roll,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));

        btScalar eulerYaw,eulerRoll,eulerPitch;
        constraint->getFrameOffsetA().getBasis().getEulerZYX(eulerYaw,eulerRoll,eulerPitch);
        this->ui->dInitRot_Yaw->setValue(bone->getYAxis() * 100);
        this->ui->dInitRot_Roll->setValue(bone->getZAxis() * 100);
        this->ui->lInitRot_Yaw->setText(QString::number(roundPrecision(bone->getYAxis())));
        this->ui->lInitRot_Roll->setText(QString::number(roundPrecision(bone->getZAxis())));

        connect(this->ui->dInitRot_Yaw,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
        connect(this->ui->dInitRot_Roll,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));

        // MOTOR EFFECTOR
        if(!bone->getRotationalMotorsEffector()->isDisable())
        {
            for(int i=0;i<3;++i) {

                bool checked = bone->getRotationalMotorsEffector()->getBrainOutputs(i) != NULL;

                switch(i) {
                case 0 :

                    disconnect(this->ui->cbEffectorX,SIGNAL(stateChanged(int)),this,SLOT(cbEffectorX_stateChanged(int)));
                    this->ui->cbEffectorX->setChecked(checked);
                    connect(this->ui->cbEffectorX,SIGNAL(stateChanged(int)),this,SLOT(cbEffectorX_stateChanged(int)));
                    break;

                case 1 :

                    disconnect(this->ui->cbEffectorY,SIGNAL(stateChanged(int)),this,SLOT(cbEffectorY_stateChanged(int)));
                    this->ui->cbEffectorY->setChecked(checked);
                    connect(this->ui->cbEffectorY,SIGNAL(stateChanged(int)),this,SLOT(cbEffectorY_stateChanged(int)));
                    break;

                case 2 :

                    disconnect(this->ui->cbEffectorZ,SIGNAL(stateChanged(int)),this,SLOT(cbEffectorZ_stateChanged(int)));
                    this->ui->cbEffectorZ->setChecked(checked);
                    connect(this->ui->cbEffectorZ,SIGNAL(stateChanged(int)),this,SLOT(cbEffectorZ_stateChanged(int)));
                    break;
                }
            }

            switch(bone->getRotationalMotorsEffector()->getOutPutsFrom()) {
            case 1 /*RotationalMotorsModifier::OUTPUTS_FROM_BRAIN*/ : this->ui->rbOutFrom_Brain->setChecked(true);  break;
            case 2 /*RotationalMotorsModifier::OUTPUTS_FROM_RANDOM*/: this->ui->rbOutFrom_Random->setChecked(true); break;
            case 0 /*RotationalMotorsModifier::OUTPUTS_FROM_NORMAL_POSITION*/ : this->ui->rbOutFrom_NormalPosition->setChecked(true); break;
            }
        }
        else
            this->ui->rbOutFrom_Disable->setChecked(true);

        // enable only for disabled outputs
        this->ui->gbMotorsTest->setEnabled(bone->getRotationalMotorsEffector()->isDisable());

        // Angular Limit Motors
        btRotationalLimitMotor *motor;
        for(int i=0;i<3;i++)
        {
            motor = constraint->getRotationalLimitMotor(i);

            switch(i)
            {
            case 0 :

                this->ui->cbEnable_m1->setChecked(motor->m_enableMotor);
                this->ui->leTargetVelocity_m1->setText(QString().number(roundPrecision(motor->m_targetVelocity)));
                this->ui->leMaxMotorForce_m1->setText(QString().number(roundPrecision(motor->m_maxMotorForce)));

                // Init motor X
                disconnect(this->ui->dAngularLowerLimitX,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
                disconnect(this->ui->dAngularUpperLimitX,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
                this->ui->dAngularLowerLimitX->setValue(btNormalizeAngle(motor->m_loLimit) * 100);
                this->ui->dAngularUpperLimitX->setValue(btNormalizeAngle(motor->m_hiLimit) * 100);
                this->ui->lAngularLowerLimitX->setText(QString::number(roundPrecision(motor->m_loLimit)));
                this->ui->lAngularUpperLimitX->setText(QString::number(roundPrecision(motor->m_hiLimit)));
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
                this->ui->lAngularLowerLimitY->setText(QString::number(roundPrecision(motor->m_loLimit)));
                this->ui->lAngularUpperLimitY->setText(QString::number(roundPrecision(motor->m_hiLimit)));
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
                this->ui->lAngularLowerLimitZ->setText(QString::number(roundPrecision(motor->m_loLimit)));
                this->ui->lAngularUpperLimitZ->setText(QString::number(roundPrecision(motor->m_hiLimit)));
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
//        ui->fixationProperties->setFixation(bone->getEndFixation());
//        ui->fixationProperties->setFormTitle("End fixation controller");
    }
    else{
        this->setEnabled(false);
    }
}

void BonePropertiesController::validateAngularInputs()
{
    if(bone)
    {

        btGeneric6DofConstraint *constraint = bone->getParentConstraint();

        // ANGULAR PARAMETERS

        // Local transform (Yaw / Roll)
        bone->setyAxis(this->ui->lInitRot_Yaw->text().toDouble());
        bone->setZAxis(this->ui->lInitRot_Roll->text().toDouble());

        // update dials
        disconnect(this->ui->dInitRot_Yaw,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
        disconnect(this->ui->dInitRot_Roll,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
        this->ui->dInitRot_Yaw->setValue(bone->getYAxis() * 100);
        this->ui->dInitRot_Roll->setValue(bone->getZAxis() * 100);
        connect(this->ui->dInitRot_Yaw,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
        connect(this->ui->dInitRot_Roll,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));

        // Limits & motor effector
        btRotationalLimitMotor *motor;
        for(int i=0;i<3;i++)
        {
            motor = constraint->getRotationalLimitMotor(i);

            switch(i)
            {
                case 0 :

                    // update motor
                    motor->m_loLimit = this->ui->lAngularLowerLimitX->text().toDouble();
                    motor->m_hiLimit = this->ui->lAngularUpperLimitX->text().toDouble();

                    // update dials
                    disconnect(this->ui->dAngularLowerLimitX,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
                    disconnect(this->ui->dAngularUpperLimitX,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
                    this->ui->dAngularLowerLimitX->setValue(motor->m_loLimit * 100);
                    this->ui->dAngularUpperLimitX->setValue(motor->m_hiLimit * 100);
                    connect(this->ui->dAngularLowerLimitX,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
                    connect(this->ui->dAngularUpperLimitX,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));

                    if(motor->m_loLimit == motor->m_hiLimit)
                    {
                        ui->cbEffectorX->setChecked(false);
                        // delete rotational motor if exists

                    }
                    else
                    {
                        ui->cbEffectorX->setChecked(true);
                        // create rotational motor if not exists
                    }


                    break;

                case 1 :

                    // update motor
                    motor->m_loLimit = this->ui->lAngularLowerLimitY->text().toDouble();
                    motor->m_hiLimit = this->ui->lAngularUpperLimitY->text().toDouble();

                    // update dials
                    disconnect(this->ui->dAngularLowerLimitY,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
                    disconnect(this->ui->dAngularUpperLimitY,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
                    this->ui->dAngularLowerLimitY->setValue(motor->m_loLimit * 100);
                    this->ui->dAngularUpperLimitY->setValue(motor->m_hiLimit * 100);
                    connect(this->ui->dAngularLowerLimitY,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
                    connect(this->ui->dAngularUpperLimitY,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));


                    if(motor->m_loLimit == motor->m_hiLimit)
                    {
                        ui->cbEffectorY->setChecked(false);
                        // delete rotational motor if exists

                    }
                    else
                    {
                        ui->cbEffectorY->setChecked(true);
                        // create rotational motor if not exists
                    }

                    break;

                case 2 :

                    // update motor
                    motor->m_loLimit = this->ui->lAngularLowerLimitZ->text().toDouble();
                    motor->m_hiLimit = this->ui->lAngularUpperLimitZ->text().toDouble();

                    // update dials
                    disconnect(this->ui->dAngularLowerLimitZ,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
                    disconnect(this->ui->dAngularUpperLimitZ,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
                    this->ui->dAngularLowerLimitZ->setValue(motor->m_loLimit * 100);
                    this->ui->dAngularUpperLimitZ->setValue(motor->m_hiLimit * 100);
                    connect(this->ui->dAngularLowerLimitZ,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
                    connect(this->ui->dAngularUpperLimitZ,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));

                    if(motor->m_loLimit == motor->m_hiLimit)
                    {
                        ui->cbEffectorZ->setChecked(false);
                        // delete rotational motor if exists

                    }
                    else
                    {
                        ui->cbEffectorZ->setChecked(true);
                        // create rotational motor if not exists
                    }

                    break;
            }
        }
    }
}

void BonePropertiesController::cbEffectorX_stateChanged(int value)
{
    if(value == Qt::Checked)
        bone->connectMotor(0);
    else
        bone->disconnectMotor(0);
}

void BonePropertiesController::cbEffectorY_stateChanged(int value)
{
    if(value == Qt::Checked)
        bone->connectMotor(1);
    else
        bone->disconnectMotor(1);
}

void BonePropertiesController::cbEffectorZ_stateChanged(int value)
{
    if(value == Qt::Checked)
        bone->connectMotor(2);
    else
        bone->disconnectMotor(2);
}
