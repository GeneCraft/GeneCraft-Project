#include "creatureviewerwindow.h"
#include "ui_creatureviewerwindow.h"
#include <QDebug>
#include "fixation.h"
#include "bone.h"
#include "entity.h"
#include "rigidbodyorigin.h"
#include "fixationproperties.h"
#include "bonepropertiescontroller.h"
#include "entitypropertiescontroller.h"

#include <QLabel>

CreatureViewerWindow::CreatureViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreatureViewer)
{
    ui->setupUi(this);

    // Connection to Inspectors
    //connect(Entity::getInspectorWidget(),SIGNAL(rigidBodySelected(btRigidBody*)),this,SLOT(rigidBodySelected(btRigidBody*)));

    inspector = 0;
    openGLWidget = 0;
}

CreatureViewerWindow::~CreatureViewerWindow()
{
    delete ui;
}

void CreatureViewerWindow::setInspector(QWidget * inspector)
{
    if(inspector != 0)
        ui->dwInspector->setWidget(inspector);
    else
        ui->dwCreature->setWidget(new QLabel("No element selected.")); // TODO NOT new !!!
}

void CreatureViewerWindow::setOpenGLWidget(QWidget * openGLWidget)
{
    setCentralWidget(openGLWidget);
}

void CreatureViewerWindow::setEntity(Entity *entity, btRigidBody *selectedBody)
{
//    if(entity != NULL)
//        ui->dwCreature->setWidget(Entity::getInspectorWidget(entity,selectedBody));
//    else
//        ui->dwCreature->setWidget(new QLabel("No creature selected.")); // TODO NOT new !!!
}

void CreatureViewerWindow::rigidBodySelected(btRigidBody *rigidBody)
{
    //other exclusions ?
    //if (!(rigidBody->isStaticObject() || rigidBody->isKinematicObject()))
    {
        if(rigidBody->getUserPointer() != NULL)
        {
            RigidBodyOrigin* origin = static_cast<RigidBodyOrigin*>(rigidBody->getUserPointer());
            if(origin != 0)
            {
                if(origin->getObject() != NULL)
                {
                    switch(origin->getType())
                    {
                        case RigidBodyOrigin::BONE:{

                            Bone *bone = dynamic_cast<Bone*>(origin->getObject());
                            //bone->setSelected(true); // TODO stock selection into rigidbody origin
                            setInspector(bone->getInspectorWidget());
                            setEntity(bone->getEntity(),bone->getRigidBody());
                            }
                            break;

                        case RigidBodyOrigin::FIXATION:{

                            Fixation *fix = dynamic_cast<Fixation*>(origin->getObject());
                            //fix->setSelected(true); // TODO stock selection into rigidbody origin
                            setInspector(fix->getInspectorWidget());
                            setEntity(fix->getEntity(),fix->getRigidBody());
                            }
                            break;

                        case RigidBodyOrigin::BASIC_SHAPE:{

                            //BasicShape *shape = dynamic_cast<BasicShape*>(reinterpret_cast<QObject*>(origin->getObject()));
                            //game->getOpenGLEngine()->getScene()->removeDrawableObject(shape);
                            //game->getBulletEngine()->getDynamicsWorld()->removeRigidBody(shape->getRigidBody());
                            setInspector(new QLabel("BASIC_SHAPE"));

                            }
                            break;

                        case RigidBodyOrigin::PLAYER_CHARACTER:{

                            qDebug() << "PLAYER_CHARACTER find !!!";
                            }
                            break;

                        default:
                            setInspector(0);
                    }
                }
                else
                    qDebug() << "CreatureViewer::rigidBodySelected : object NULL";
            }
            else
                qDebug() << "CreatureViewer::rigidBodySelected : RigidBodyOrigin NULL";
        }

        //pickedBody = body;
        //pickedrigidBody->setActivationState(DISABLE_DEACTIVATION);
//                btVector3 pickPos = rayCallback.m_hitPointWorld;
//                qDebug() << "pickPos=" << pickPos.getX() << pickPos.getY() << pickPos.getZ();


//                btVector3 localPivot = rigidBody->getCenterOfMassTransform().inverse() * pickPos;

//                if (use6Dof)
//                {
//                    btTransform tr;
//                    tr.setIdentity();
//                    tr.setOrigin(localPivot);
//                    btGeneric6DofConstraint* dof6 = new btGeneric6DofConstraint(*body, tr,false);
//                    dof6->setLinearLowerLimit(btVector3(0,0,0));
//                    dof6->setLinearUpperLimit(btVector3(0,0,0));
//                    dof6->setAngularLowerLimit(btVector3(0,0,0));
//                    dof6->setAngularUpperLimit(btVector3(0,0,0));

//                    game->getBulletEngine()->getDynamicsWorld()->addConstraint(dof6);
//                    m_pickConstraint = dof6;

//                    dof6->setParam(BT_CONSTRAINT_STOP_CFM,0.8,0);
//                    dof6->setParam(BT_CONSTRAINT_STOP_CFM,0.8,1);
//                    dof6->setParam(BT_CONSTRAINT_STOP_CFM,0.8,2);
//                    dof6->setParam(BT_CONSTRAINT_STOP_CFM,0.8,3);
//                    dof6->setParam(BT_CONSTRAINT_STOP_CFM,0.8,4);
//                    dof6->setParam(BT_CONSTRAINT_STOP_CFM,0.8,5);

//                    dof6->setParam(BT_CONSTRAINT_STOP_ERP,0.1,0);
//                    dof6->setParam(BT_CONSTRAINT_STOP_ERP,0.1,1);
//                    dof6->setParam(BT_CONSTRAINT_STOP_ERP,0.1,2);
//                    dof6->setParam(BT_CONSTRAINT_STOP_ERP,0.1,3);
//                    dof6->setParam(BT_CONSTRAINT_STOP_ERP,0.1,4);
//                    dof6->setParam(BT_CONSTRAINT_STOP_ERP,0.1,5);
//                } else
//                {
//                    btPoint2PointConstraint* p2p = new btPoint2PointConstraint(*body,localPivot);
//                    game->getBulletEngine()->getDynamicsWorld()->addConstraint(p2p);
//                    m_pickConstraint = p2p;
//                    p2p->m_setting.m_impulseClamp = mousePickClamping;
//                    //very weak constraint for picking
//                    p2p->m_setting.m_tau = 0.001f;
//                    /*
//                                            p2p->setParam(BT_CONSTRAINT_CFM,0.8,0);
//                                            p2p->setParam(BT_CONSTRAINT_CFM,0.8,1);
//                                            p2p->setParam(BT_CONSTRAINT_CFM,0.8,2);
//                                            p2p->setParam(BT_CONSTRAINT_ERP,0.1,0);
//                                            p2p->setParam(BT_CONSTRAINT_ERP,0.1,1);
//                                            p2p->setParam(BT_CONSTRAINT_ERP,0.1,2);
//                                            */
//                }
//                use6Dof = !use6Dof;

//                //save mouse position for dragging
//                gOldPickingPos = rayTo;
//                gHitPos = pickPos;

//                gOldPickingDist  = (pickPos-rayFrom).length();
    }
}
