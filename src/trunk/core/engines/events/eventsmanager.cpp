#include "eventsmanager.h"

using namespace Ogre;

namespace GeneCraftCore {

    EventsManager::EventsManager(QObject *parent) : GeneCraftCore::Engine(parent)
    {
    }

    void EventsManager::addListener(InputListener * il)
    {
        inputListeners.push_back(il);
    }

    void EventsManager::removeListener(InputListener *il)
    {
        inputListeners.removeOne(il);
    }

    void EventsManager::mousePressEvent(QMouseEvent * e)
    {
        eventsQueue.enqueue(e);
    }

    void EventsManager::mouseReleaseEvent(QMouseEvent * e)
    {
        eventsQueue.enqueue(e);
    }

    void EventsManager::mouseMoveEvent(QMouseEvent * e)
    {
        eventsQueue.enqueue(e);
    }

    void EventsManager::keyPressEvent(QKeyEvent *e)
    {
        eventsQueue.enqueue(e);
    }

    void EventsManager::keyReleaseEvent(QKeyEvent *e)
    {
        eventsQueue.enqueue(e);
    }

    void EventsManager::enterViewPortEvent (QEvent *e)
    {
        eventsQueue.enqueue(e);
    }

    void EventsManager::leaveViewPortEvent (QEvent *e)
    {
        eventsQueue.enqueue(e);
    }

    // Engine
    void EventsManager::beforeStep(){

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


    void EventsManager::step()
    {}

    void EventsManager::afterStep()
    {}
}
