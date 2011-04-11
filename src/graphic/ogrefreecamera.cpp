#include "ogrefreecamera.h"
#include <QDebug>


const QPoint     OgreFreeCamera::invalidMousePoint(-1,-1);
const Ogre::Real OgreFreeCamera::turboModifier(10);

OgreFreeCamera::OgreFreeCamera (Ogre::Camera *ogreCamera)
{
    this->ogreCamera = ogreCamera;

    // Movement parameters
    initialMovementSpeed    = 1.0;
    movementSpeed           = initialMovementSpeed;
    maxMovementSpeed        = 5.0;
    movementAcceleration    = 1.02;
    movementDeceleration    = 1.1;

    // Look parameters
    lookSensibility         = 1.8;

    // Default action status
    forwardKeyPressed       = false;
    backwardKeyPressed      = false;
    rightStrafeKeyPressed   = false;
    leftStrafeKeyPressed    = false;
    upKeyPressed            = false;
    downKeyPressed          = false;
}

void OgreFreeCamera::mousePressEvent(QMouseEvent * e)
{
    if(e->buttons().testFlag(Qt::LeftButton))
    {
        oldPos = e->pos();
        e->accept();
    }
    else
        e->ignore();
}

void OgreFreeCamera::mouseReleaseEvent(QMouseEvent * e)
{
    if(!e->buttons().testFlag(Qt::LeftButton))
    {
        oldPos = QPoint(invalidMousePoint);
        e->accept();
    }
    else
        e->ignore();
}

void OgreFreeCamera::mouseMoveEvent(QMouseEvent * e)
{
    if(e->buttons().testFlag(Qt::LeftButton) && oldPos != invalidMousePoint)
    {
        const QPoint &pos = e->pos();
        Ogre::Real deltaX = pos.x() - oldPos.x();
        Ogre::Real deltaY = pos.y() - oldPos.y();

//        if(e->modifiers().testFlag(Qt::ControlModifier))
//        {
//            deltaX *= turboModifier;
//            deltaY *= turboModifier;
//        }

        ogreCamera->pitch(Ogre::Radian(deltaY * -0.001 * lookSensibility));
        ogreCamera->yaw(Ogre::Radian(deltaX * -0.001 * lookSensibility));

        oldPos = pos;

        e->accept();
    }
    else
        e->ignore();
}

void OgreFreeCamera::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_W : forwardKeyPressed = true;
        break;
    case Qt::Key_S : backwardKeyPressed = true;
        break;
    case Qt::Key_D : rightStrafeKeyPressed = true;
        break;
    case Qt::Key_A : leftStrafeKeyPressed = true;
        break;
    case Qt::Key_Space : upKeyPressed = true;
        break;
    case Qt::Key_Control : downKeyPressed = true;
        break;
    }
}

void OgreFreeCamera::keyReleaseEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_W : forwardKeyPressed = false;
        break;
    case Qt::Key_S : backwardKeyPressed = false;
        break;
    case Qt::Key_D : rightStrafeKeyPressed = false;
        break;
    case Qt::Key_A : leftStrafeKeyPressed = false;
        break;
    case Qt::Key_Space : upKeyPressed = false;
        break;
    case Qt::Key_Control : downKeyPressed = false;
        break;
    }
}

void OgreFreeCamera::step()
{
    // float time = 1.0; TODO (event)

    // any movement key are pressed
    if(forwardKeyPressed || backwardKeyPressed
       || rightStrafeKeyPressed || leftStrafeKeyPressed
       || upKeyPressed || downKeyPressed)
    {
        movementSpeed *= movementAcceleration;

        if(movementSpeed > maxMovementSpeed)
            movementSpeed = maxMovementSpeed;

        // compute the direction of the movement
        Ogre::Vector3 vMovementDirection(0,0,0);

        // add all direction
        if(forwardKeyPressed)
            vMovementDirection += ogreCamera->getDirection();
        if(backwardKeyPressed)
            vMovementDirection += -ogreCamera->getDirection();
        if(rightStrafeKeyPressed)
            vMovementDirection += ogreCamera->getRight();
        if(leftStrafeKeyPressed)
            vMovementDirection += -ogreCamera->getRight();
        if(upKeyPressed)
            vMovementDirection += ogreCamera->getUp();
        if(downKeyPressed)
            vMovementDirection += -ogreCamera->getUp();

        // normalise for applying speed
        vMovementDirection.normalise();

        // apply speed and move the camera
        ogreCamera->move(vMovementDirection * movementSpeed);

        // save the direction for deceleration
        lastMovementDirection = vMovementDirection;
    }
    else // no movement key pressed
    {
        // deceleration
        movementSpeed /= movementDeceleration;

        if(movementSpeed < initialMovementSpeed)
            // the minimal speed is reached, don't move
            movementSpeed = initialMovementSpeed;
        else
            // continue to move in the last direction
            ogreCamera->move(lastMovementDirection * movementSpeed);
    }
}

void OgreFreeCamera::enterViewPortEvent (QEvent *e)
{

}

void OgreFreeCamera::leaveViewPortEvent (QEvent *e)
{

}

