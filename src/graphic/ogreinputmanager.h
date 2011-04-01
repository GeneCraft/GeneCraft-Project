#ifndef OGREINPUTMANAGER_H
#define OGREINPUTMANAGER_H

#include <QObject>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

//#include <SdkTrays.h>
#include <SdkCameraMan.h>

class OgreInputManager : public QObject
{
    Q_OBJECT
public:
    explicit OgreInputManager(QObject *parent = 0);

signals:

public slots:

protected:

    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

};

#endif // OGREINPUTMANAGER_H
