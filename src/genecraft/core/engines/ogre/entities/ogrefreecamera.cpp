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

#include "ogrefreecamera.h"

namespace GeneCraftCore {

const QPoint     OgreFreeCamera::invalidMousePoint(-1,-1);
const Ogre::Real OgreFreeCamera::turboModifier(10);

OgreFreeCamera::OgreFreeCamera (Ogre::Camera *ogreCamera) : followedBody(NULL)
{
    this->ogreCamera = ogreCamera;

    // Movement parameters
    initialMovementSpeed    = 1.4;
    movementSpeed           = initialMovementSpeed;
    maxMovementSpeed        = 60.0; // meter / s
    movementAcceleration    = 1.2;
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
        if(followedBody)
            unfollowBody();

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
    case Qt::Key_W :
    case Qt::Key_Up :
        forwardKeyPressed = true;
        break;
    case Qt::Key_S :
    case Qt::Key_Down :
        backwardKeyPressed = true;
        break;
    case Qt::Key_D :
    case Qt::Key_Right :
        rightStrafeKeyPressed = true;
        break;
    case Qt::Key_A :
    case Qt::Key_Left :
        leftStrafeKeyPressed = true;
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
    case Qt::Key_W :
    case Qt::Key_Up :
        forwardKeyPressed = false;
        break;
    case Qt::Key_S :
    case Qt::Key_Down :
        backwardKeyPressed = false;
        break;
    case Qt::Key_D :
    case Qt::Key_Right :
        rightStrafeKeyPressed = false;
        break;
    case Qt::Key_A :
    case Qt::Key_Left :
        leftStrafeKeyPressed = false;
        break;
    case Qt::Key_Space : upKeyPressed = false;
        break;
    case Qt::Key_Control : downKeyPressed = false;
        break;
    }
}

Ogre::Vector3 toOgreVector3(btVector3 vector) {
    Ogre::Vector3 v;
    v.x = vector.x();
    v.y = vector.y();
    v.z = vector.z();
    return v;
}

btVector3 toOgreVector3(Ogre::Vector3 vector);

void OgreFreeCamera::step()
{
    if(t.elapsed() == 0.0)
       t.start();

    Ogre::Real elapsedTime = t.elapsed()/1000.0;
    t.restart();

    if(followedBody) {

        Ogre::Vector3 oTarget = toOgreVector3(followedBody->getWorldTransform().getOrigin());
        ogreCamera->setDirection(oTarget - ogreCamera->getPosition());

    }

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
        move(vMovementDirection * movementSpeed * elapsedTime);

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
            move(lastMovementDirection * movementSpeed * elapsedTime);
    }
}

void OgreFreeCamera::move(const Ogre::Vector3& vec) {

    if(followedBody) {

        int nbSubSteps = vec.length() * 5;
        for(int i=0; i < nbSubSteps; i++) {
            ogreCamera->move(vec / nbSubSteps);

            Ogre::Vector3 oTarget = toOgreVector3(followedBody->getWorldTransform().getOrigin());
            ogreCamera->setDirection(oTarget - ogreCamera->getPosition());
        }
    }
    else
        ogreCamera->move(vec);
}

void OgreFreeCamera::enterViewPortEvent (QEvent *){}
void OgreFreeCamera::leaveViewPortEvent (QEvent *){}

void OgreFreeCamera::followBody(btRigidBody * body){

    distanceToTarget = ogreCamera->getPosition().distance(toOgreVector3(body->getWorldTransform().getOrigin()));
    followedBody = body;

    //maxMovementSpeed = 30.0;
}

void OgreFreeCamera::unfollowBody() {

    followedBody = NULL;
    //maxMovementSpeed = 60.0;
}

}
