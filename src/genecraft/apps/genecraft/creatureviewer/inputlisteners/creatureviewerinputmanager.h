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

#ifndef CREATUREVIEWERINPUTMANAGER_H
#define CREATUREVIEWERINPUTMANAGER_H

#include "genecraftcoreclasses.h"
#include "events/inspectorsinputmanager.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

using namespace GeneCraftCore;

/**
 * (c) GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * Manage inputs into the creature viewer.
 * Emit rigidBodySelected when user click on a rigidBody into the scene.
 * Allow you to throw cube by right clicking.
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo & Cyprien Huissoud
 */
class CreatureViewerInputManager : public InspectorsInputManager
{
    Q_OBJECT

public:

    CreatureViewerInputManager(BulletOgreEngine *btoEngine,Ogre::Camera *camera);

    // Events (called during beforeStep)
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void enterViewPortEvent(QEvent *e);
    void leaveViewPortEvent(QEvent *e);

    void setWorld(btWorld* world);

signals:

    void rigidBodySelected(btRigidBody *rigidBody);

public slots:

private:

    void pickBody();
    void throwCube();
    Ogre::Camera *camera;
    BulletOgreEngine* btoEngine;
    int mNumEntitiesInstanced;
    QPoint mousePos;
    btWorld* world;

};


#endif // CREATUREVIEWERINPUTMANAGER_H
