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
