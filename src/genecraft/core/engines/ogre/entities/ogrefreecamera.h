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

#ifndef OGREFREECAMERA_H
#define OGREFREECAMERA_H

#include <QObject>
#include <QPoint>
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <Ogre.h>
#include "genecraftcoreclasses.h"
#include "events/inputlistener.h"
#include <QTime>

#include "BulletDynamics/Dynamics/btRigidBody.h"

namespace GeneCraftCore {

class OgreFreeCamera : public InputListener
{
    Q_OBJECT
public:

    // Constructor
    OgreFreeCamera (Ogre::Camera *ogreCamera);

public slots:

    // Events
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void enterViewPortEvent(QEvent *e);
    void leaveViewPortEvent(QEvent *e);

    // Compute the new position and angular
    void step();
    void move(const Ogre::Vector3& vec);

    void followBody(btRigidBody * body);
    void unfollowBody();

private:

    Ogre::Camera *ogreCamera;

    // Movements
    Ogre::Real movementSpeed;
    Ogre::Real maxMovementSpeed;
    Ogre::Real movementAcceleration;
    Ogre::Real initialMovementSpeed;
    Ogre::Real movementDeceleration;
    Ogre::Vector3 lastMovementDirection;

    // Angular
    Ogre::Real lookSensibility;
    QTime t;

    // Action status
    bool forwardKeyPressed;
    bool backwardKeyPressed;
    bool rightStrafeKeyPressed;
    bool leftStrafeKeyPressed;
    bool upKeyPressed;
    bool downKeyPressed;

    QPoint oldPos;
    static const Ogre::Real turboModifier;
    static const QPoint invalidMousePoint;

    btRigidBody * followedBody;
    Ogre::Real distanceToTarget;
};
}
#endif // OGREFREECAMERA_H
