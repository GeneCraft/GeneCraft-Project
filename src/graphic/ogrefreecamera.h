#ifndef OGREFREECAMERA_H
#define OGREFREECAMERA_H

#include <QObject>
#include <QPoint>
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <Ogre.h>
#include <QDebug>

class OgreFreeCamera : public QObject
{
    Q_OBJECT
public:

    // Constructor

    // FIXME
    // J'ai d'abord fait un héritage de Ogre::Camera mais je n'arrive pas a créer
    // ma camera car normalement les caméras sont créées à l'aide du Ogre::SceneManager
    // de la facon suivante :
    //
    // Ogre::Camera *cam = sceneManager->createCamera("camName");
    //
    // Donc pour le moment c'est juste une encapsulation... :(
    OgreFreeCamera (Ogre::Camera *ogreCamera);

    // Events
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void enterViewPortEvent(QEvent *e);
    void leaveViewPortEvent(QEvent *e);

    // Compute the new position and angular
    void step(); // TODO better if the time is in paramater because speed is a distance by time...

private:

    Ogre::Camera *ogreCamera;

    // Movements
    Ogre::Real movementSpeed;
    Ogre::Real maxMovementSpeed;
    Ogre::Real movementAcceleration;
    Ogre::Real initialMovementSpeed;
    Ogre::Real movementDeceleration;
    int lastMovement;


    // Angular
    Ogre::Real lookSensibility;

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
};

#endif // OGREFREECAMERA_H
