#include "eventmanager.h"

using namespace Ogre;

namespace GeneLabCore {

    EventManager::EventManager(QObject *parent) : GeneLabCore::Engine(parent)
    {
    }

    void EventManager::addListener(InputListener * il)
    {
        inputListeners.push_back(il);
    }

    void EventManager::removeListener(InputListener *il)
    {
        inputListeners.removeOne(il);
    }

    void EventManager::mousePressEvent(QMouseEvent * e)
    {
        eventsQueue.enqueue(e);
    }

    void EventManager::mouseReleaseEvent(QMouseEvent * e)
    {
        eventsQueue.enqueue(e);
    }

    void EventManager::mouseMoveEvent(QMouseEvent * e)
    {
        eventsQueue.enqueue(e);
    }

    void EventManager::keyPressEvent(QKeyEvent *e)
    {
        eventsQueue.enqueue(e);
    }

    void EventManager::keyReleaseEvent(QKeyEvent *e)
    {
        eventsQueue.enqueue(e);
    }

    void EventManager::enterViewPortEvent (QEvent *e)
    {
        eventsQueue.enqueue(e);
    }

    void EventManager::leaveViewPortEvent (QEvent *e)
    {
        eventsQueue.enqueue(e);
    }

    // Engine
    void EventManager::beforeStep(){

        while(!eventsQueue.empty())
        {
            QEvent *e = eventsQueue.dequeue();
            QMouseEvent *me;
            QKeyEvent *ke;

            switch(e->type())
            {
            case QEvent::MouseButtonPress :
                me = (QMouseEvent*) e;
                for(int i=0;i<inputListeners.length();i++)
                    inputListeners.at(i)->mousePressEvent(me);
                break;

            case QEvent::MouseButtonRelease :
                me = (QMouseEvent*) e;
                for(int i=0;i<inputListeners.length();i++)
                    inputListeners.at(i)->mouseReleaseEvent(me);
                break;

            case QEvent::MouseMove :
                me = (QMouseEvent*) e;
                for(int i=0;i<inputListeners.length();i++)
                    inputListeners.at(i)->mouseMoveEvent(me);
                break;

            case QEvent::KeyRelease :
                ke = (QKeyEvent*) e;
                for(int i=0;i<inputListeners.length();i++)
                    inputListeners.at(i)->keyReleaseEvent(ke);
                break;

            case QEvent::KeyPress :
                ke = (QKeyEvent*) e;
                for(int i=0;i<inputListeners.length();i++)
                    inputListeners.at(i)->keyPressEvent(ke);
                break;

            case QEvent::Enter :
                me = (QMouseEvent*) e;
                for(int i=0;i<inputListeners.length();i++)
                    inputListeners.at(i)->enterViewPortEvent(me);
                break;

            case QEvent::Leave :
                me = (QMouseEvent*) e;
                for(int i=0;i<inputListeners.length();i++)
                    inputListeners.at(i)->leaveViewPortEvent(me);
                break;

             default:
                ;
            }
        }
    }


    void EventManager::step()
    {}

    void EventManager::afterStep()
    {}
}
