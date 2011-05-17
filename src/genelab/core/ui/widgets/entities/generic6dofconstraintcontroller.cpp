#include "generic6dofconstraintcontroller.h"
#include "ui_generic6dofconstraintcontroller.h"

Generic6DofConstraintController::Generic6DofConstraintController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Generic6DofConstraintController)
{
    ui->setupUi(this);

    connect(this->ui->pbSaveChanges,SIGNAL(clicked()),this,SLOT(saveChanges()));
}

Generic6DofConstraintController::~Generic6DofConstraintController()
{
    delete ui;
}

void Generic6DofConstraintController::saveChanges()
{
    this->constraint->getFrameOffsetA().getBasis().setEulerZYX(this->ui->leEulerRotX->text().toFloat(),
                                                               this->ui->leEulerRotY->text().toFloat(),
                                                               this->ui->leEulerRotZ->text().toFloat());

    btRotationalLimitMotor *motor;
    for(int i=0;i<3;i++)
    {
        motor = this->constraint->getRotationalLimitMotor(i);

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

void Generic6DofConstraintController::setConstraint(btGeneric6DofConstraint * ct)
{
    this->constraint = ct;

    // Local transform
    btScalar eulerYaw,eulerRoll,eulerPitch;
    this->constraint->getFrameOffsetA().getBasis().getEulerZYX(eulerYaw,eulerRoll,eulerPitch);
    this->ui->leEulerRotX->setText(QString().setNum(eulerPitch));
    this->ui->leEulerRotY->setText(QString().setNum(eulerRoll));
    this->ui->leEulerRotZ->setText(QString().setNum(eulerYaw));

    // Angular Limit Motors
    btRotationalLimitMotor *motor;
    for(int i=0;i<3;i++)
    {
        motor = this->constraint->getRotationalLimitMotor(i);

        switch(i)
        {
            case 0 :
                this->ui->cbEnable_m1->setChecked(motor->m_enableMotor);
                this->ui->leTargetVelocity_m1->setText(QString().setNum(motor->m_targetVelocity));
                this->ui->leMaxMotorForce_m1->setText(QString().setNum(motor->m_maxMotorForce));
                this->ui->leMaxLimitForce_m1->setText(QString().setNum(motor->m_maxLimitForce));
                this->ui->leBounce_m1->setText(QString().setNum(motor->m_bounce));
                this->ui->leDamping_m1->setText(QString().setNum(motor->m_bounce));

                this->ui->leAngularLowerLimit_x->setText(QString().setNum(btNormalizeAngle(motor->m_loLimit)));
                this->ui->leAngularUpperLimit_x->setText(QString().setNum(btNormalizeAngle(motor->m_hiLimit)));

                break;
            case 1 :
                this->ui->cbEnable_m2->setChecked(motor->m_enableMotor);
                this->ui->leTargetVelocity_m2->setText(QString().setNum(motor->m_targetVelocity));
                this->ui->leMaxMotorForce_m2->setText(QString().setNum(motor->m_maxMotorForce));
                this->ui->leMaxLimitForce_m2->setText(QString().setNum(motor->m_maxLimitForce));
                this->ui->leBounce_m2->setText(QString().setNum(motor->m_bounce));
                this->ui->leDamping_m2->setText(QString().setNum(motor->m_bounce));

                this->ui->leAngularLowerLimit_y->setText(QString().setNum(btNormalizeAngle(motor->m_loLimit)));
                this->ui->leAngularUpperLimit_y->setText(QString().setNum(btNormalizeAngle(motor->m_hiLimit)));
            break;
            case 2 :
                this->ui->cbEnable_m3->setChecked(motor->m_enableMotor);
                this->ui->leTargetVelocity_m3->setText(QString().setNum(motor->m_targetVelocity));
                this->ui->leMaxMotorForce_m3->setText(QString().setNum(motor->m_maxMotorForce));
                this->ui->leMaxLimitForce_m3->setText(QString().setNum(motor->m_maxLimitForce));
                this->ui->leBounce_m3->setText(QString().setNum(motor->m_bounce));
                this->ui->leDamping_m3->setText(QString().setNum(motor->m_bounce));

                this->ui->leAngularLowerLimit_z->setText(QString().setNum(btNormalizeAngle(motor->m_loLimit)));
                this->ui->leAngularUpperLimit_z->setText(QString().setNum(btNormalizeAngle(motor->m_hiLimit)));
            break;
        }
    }
}
