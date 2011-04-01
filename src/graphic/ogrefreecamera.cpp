#include "ogrefreecamera.h"

const QPoint     OgreFreeCamera::invalidMousePoint(-1,-1);
const Ogre::Real OgreFreeCamera::turboModifier(10);

OgreFreeCamera::OgreFreeCamera (Ogre::Camera *ogreCamera)
{
    this->ogreCamera = ogreCamera;

    // Movement parameters
    initialMovementSpeed    = 1.0;
    movementSpeed           = initialMovementSpeed;
    maxMovementSpeed        = 10.0;
    movementAcceleration    = 1.1;
    movementDeceleration    = 1.01;

    // Look parameters
    lookSensibility = 0.5;

    // Action default status
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

        if(e->modifiers().testFlag(Qt::ControlModifier))
        {
            deltaX *= turboModifier;
            deltaY *= turboModifier;
        }

        //            Ogre::Vector3 camTranslation(deltaX, deltaY, 0);
        //            const Ogre::Vector3 &actualCamPos = mCamera->getPosition();
        //            setCameraPosition(actualCamPos + camTranslation);

        ogreCamera->pitch(Ogre::Radian(deltaY * -0.01 * lookSensibility));
        ogreCamera->yaw(Ogre::Radian(deltaX * -0.01 * lookSensibility));

        oldPos = pos;
        e->accept();
    }
    else
    {
        e->ignore();
    }
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
    }
    // no movement key pressed
    else
    {
        movementSpeed /= movementDeceleration;

        qDebug() << "decelerarion : " << movementSpeed;

        if(movementSpeed < initialMovementSpeed)
            movementSpeed = initialMovementSpeed;


        // continue to move
        switch(lastMovement)
        {
            // ...
        }
    }

    // move
    if(forwardKeyPressed)
        ogreCamera->move(ogreCamera->getDirection().normalisedCopy() * movementSpeed);
    if(backwardKeyPressed)
        ogreCamera->move(-ogreCamera->getDirection().normalisedCopy() * movementSpeed);
    if(rightStrafeKeyPressed)
        ogreCamera->move(ogreCamera->getRight().normalisedCopy() * movementSpeed);
    if(leftStrafeKeyPressed)
        ogreCamera->move(-ogreCamera->getRight().normalisedCopy() * movementSpeed);
    if(upKeyPressed)
        ogreCamera->move(ogreCamera->getUp().normalisedCopy() * movementSpeed);
    if(downKeyPressed)
        ogreCamera->move(-ogreCamera->getUp().normalisedCopy() * movementSpeed);
}

void OgreFreeCamera::enterViewPortEvent (QEvent *e)
{

}

void OgreFreeCamera::leaveViewPortEvent (QEvent *e)
{

}

