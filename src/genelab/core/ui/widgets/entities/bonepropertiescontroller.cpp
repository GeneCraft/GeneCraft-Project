#include "bonepropertiescontroller.h"
#include "ui_bonepropertiescontroller.h"
#include "bone.h"
#include "fixation.h"
#include "generic6dofconstraintcontroller.h"
#include "sensor.h"
#include "positionsensor.h"
#include "entity.h"
#include "treeshape.h"

BonePropertiesController::BonePropertiesController(QWidget *parent) :
    QWidget(parent), ui(new Ui::BonePropertiesController), bone(0)
{
    ui->setupUi(this);

    connect(this->ui->pbSaveChanges,SIGNAL(pressed()),this,SLOT(saveChanges()));
    connect(this->ui->pbDelete,SIGNAL(pressed()),this,SLOT(deleteBone()));
    connect(this->ui->pbRandomValues,SIGNAL(pressed()),this,SLOT(randomValues()));
    connect(this->ui->pbResetMotors,SIGNAL(pressed()),this,SLOT(resetMotors()));

    connect(this->ui->sEulerRotX,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
    connect(this->ui->sEulerRotY,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
    connect(this->ui->sEulerRotZ,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));

    connect(this->ui->pbAddBone,SIGNAL(pressed()),this,SLOT(addBone()));
    connect(this->ui->pbAddSensor,SIGNAL(pressed()),this,SLOT(addSensor()));
    connect(this->ui->pbFixInTheAir,SIGNAL(pressed()),this,SLOT(fixInTheAir()));
    connect(this->ui->pbSetPosition,SIGNAL(pressed()),this,SLOT(setPosition()));
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

        constraint->getFrameOffsetA().getBasis().setEulerZYX(this->ui->sEulerRotX->value() / 100.0,
                                                                   this->ui->sEulerRotY->value() / 100.0,
                                                                   this->ui->sEulerRotZ->value() / 100.0);


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
                    motor->m_maxLimitForce = this->ui->leMaxLimitForce_m1->text().toFloat();
                    motor->m_bounce = this->ui->leBounce_m1->text().toFloat();
                    motor->m_damping = this->ui->leDamping_m1->text().toFloat();

                    motor->m_loLimit = this->ui->leAngularLowerLimit_x->text().toFloat();
                    motor->m_hiLimit = this->ui->leAngularUpperLimit_x->text().toFloat();
                    break;

                case 1 :
                    motor->m_enableMotor = this->ui->cbEnable_m2->isChecked();
                    motor->m_targetVelocity = this->ui->leTargetVelocity_m2->text().toFloat();
                    motor->m_maxMotorForce = this->ui->leMaxMotorForce_m2->text().toFloat();
                    motor->m_maxLimitForce = this->ui->leMaxLimitForce_m2->text().toFloat();
                    motor->m_bounce = this->ui->leBounce_m2->text().toFloat();
                    motor->m_damping = this->ui->leDamping_m2->text().toFloat();

                    motor->m_loLimit = this->ui->leAngularLowerLimit_y->text().toFloat();
                    motor->m_hiLimit = this->ui->leAngularUpperLimit_y->text().toFloat();
                    break;

                case 2 :
                    motor->m_enableMotor = this->ui->cbEnable_m3->isChecked();
                    motor->m_targetVelocity = this->ui->leTargetVelocity_m3->text().toFloat();
                    motor->m_maxMotorForce = this->ui->leMaxMotorForce_m3->text().toFloat();
                    motor->m_maxLimitForce = this->ui->leMaxLimitForce_m3->text().toFloat();
                    motor->m_bounce = this->ui->leBounce_m3->text().toFloat();
                    motor->m_damping = this->ui->leDamping_m3->text().toFloat();

                    motor->m_loLimit = this->ui->leAngularLowerLimit_z->text().toFloat();
                    motor->m_hiLimit = this->ui->leAngularUpperLimit_z->text().toFloat();
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
        disconnect(this->ui->sEulerRotX,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
        disconnect(this->ui->sEulerRotY,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
        disconnect(this->ui->sEulerRotZ,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));

        btScalar eulerYaw,eulerRoll,eulerPitch;
        constraint->getFrameOffsetA().getBasis().getEulerZYX(eulerYaw,eulerRoll,eulerPitch);
        // this->ui->leEulerRotX->setText(QString().setNum(eulerPitch));
        // this->ui->leEulerRotY->setText(QString().setNum(eulerRoll));
        // this->ui->leEulerRotZ->setText(QString().setNum(eulerYaw));
        this->ui->sEulerRotX->setValue(eulerPitch * 100);
        this->ui->sEulerRotY->setValue(eulerRoll * 100);
        this->ui->sEulerRotZ->setValue(eulerYaw * 100);

        connect(this->ui->sEulerRotX,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
        connect(this->ui->sEulerRotY,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));
        connect(this->ui->sEulerRotZ,SIGNAL(valueChanged(int)),this,SLOT(saveChanges()));

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
                this->ui->leMaxLimitForce_m1->setText(QString().setNum(motor->m_maxLimitForce));
                this->ui->leBounce_m1->setText(QString().setNum(motor->m_bounce));
                this->ui->leDamping_m1->setText(QString().setNum(motor->m_damping));

                this->ui->leAngularLowerLimit_x->setText(QString().setNum(btNormalizeAngle(motor->m_loLimit)));
                this->ui->leAngularUpperLimit_x->setText(QString().setNum(btNormalizeAngle(motor->m_hiLimit)));

                break;
            case 1 :
                this->ui->cbEnable_m2->setChecked(motor->m_enableMotor);
                this->ui->leTargetVelocity_m2->setText(QString().setNum(motor->m_targetVelocity));
                this->ui->leMaxMotorForce_m2->setText(QString().setNum(motor->m_maxMotorForce));
                this->ui->leMaxLimitForce_m2->setText(QString().setNum(motor->m_maxLimitForce));
                this->ui->leBounce_m2->setText(QString().setNum(motor->m_bounce));
                this->ui->leDamping_m2->setText(QString().setNum(motor->m_damping));

                this->ui->leAngularLowerLimit_y->setText(QString().setNum(btNormalizeAngle(motor->m_loLimit)));
                this->ui->leAngularUpperLimit_y->setText(QString().setNum(btNormalizeAngle(motor->m_hiLimit)));
                break;
            case 2 :
                this->ui->cbEnable_m3->setChecked(motor->m_enableMotor);
                this->ui->leTargetVelocity_m3->setText(QString().setNum(motor->m_targetVelocity));
                this->ui->leMaxMotorForce_m3->setText(QString().setNum(motor->m_maxMotorForce));
                this->ui->leMaxLimitForce_m3->setText(QString().setNum(motor->m_maxLimitForce));
                this->ui->leBounce_m3->setText(QString().setNum(motor->m_bounce));
                this->ui->leDamping_m3->setText(QString().setNum(motor->m_damping));

                this->ui->leAngularLowerLimit_z->setText(QString().setNum(btNormalizeAngle(motor->m_loLimit)));
                this->ui->leAngularUpperLimit_z->setText(QString().setNum(btNormalizeAngle(motor->m_hiLimit)));
                break;
            }
        }

        // Sensors
        this->ui->listSensors->clear();
        foreach(Sensor *s, bone->getEndFixation()->getSensors())
            this->ui->listSensors->addItem(new SensorListWidgetItem(s));
    }
}

void BonePropertiesController::addBone()
{
    Fixation *fixation = bone->getEndFixation();

    if(fixation != NULL)
    {
        btTransform local; local.setIdentity();

        Bone *bone = fixation->addBone(local.getRotation(),ui->leAddBoneRadius->text().toFloat(),
                                        ui->leAddBoneLenght->text().toFloat(),
                                        ui->leAddBoneEndFixRadius->text().toFloat(),
                                        btVector3(0,0,0),
                                        btVector3(0,0,0));

        bone->setup();

        setBone(bone);
    }
}

void BonePropertiesController::fixInTheAir()
{
    Fixation *fixation = bone->getEndFixation();

    if(fixation != NULL)
    {
        if(fixation->isFixedInTheAir())
            fixation->unfixInTheAir();
        else
            fixation->fixeInTheAir(btVector3(ui->leX->text().toFloat(),
                                             ui->leY->text().toFloat(),
                                             ui->leZ->text().toFloat()));
    }
}

void BonePropertiesController::setPosition()
{
    Fixation *fixation = bone->getEndFixation();

    if(fixation != NULL)
        fixation->getRigidBody()->getWorldTransform().setOrigin(btVector3(ui->leX->text().toFloat(),
                                                            ui->leY->text().toFloat(),
                                                            ui->leZ->text().toFloat()));
}

void BonePropertiesController::addSensor()
{
    qDebug() << "BonePropertiesController::addSensor";

    Sensor *sensor = NULL;

    switch(this->ui->cbSensors->currentIndex())
    {
        case 0 :

            if(bone->getEntity())
            {
                qDebug() << "BonePropertiesController::addSensor : position";
                sensor = new PositionSensor(bone->getEntity()->getShape()->getRoot(),bone->getEndFixation());
            }
        break;
    }

    if(sensor != NULL)
    {
        this->bone->getEndFixation()->addSensor(sensor);
        setBone(bone); // refresh widget
    }
}
