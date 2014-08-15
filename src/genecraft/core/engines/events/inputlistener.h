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

#ifndef INPUTLISTENER_H
#define INPUTLISTENER_H

#include <QObject>
#include <QMouseEvent>
#include <QKeyEvent>

namespace GeneCraftCore {

    /**
      * InputListener is an interface. It force you to define several events methods.
      *
      * These methods will be call during the before step of the engine. For doing that, you need to
      * register the InputListener subclass to an EventManager.
      *
      * After that, when event method is called, you're acces to all objects into the engin without
      * concurrential problems.
      *
      * @author Da Campo Aurelien
      * @author Cyprien Huissoud
      * @version 1.0 | April 2011
      * @see EventManager
      */
    class InputListener : public QObject
    {
        Q_OBJECT
    public:
        explicit InputListener(QObject *parent = 0);

    signals:

    public slots:

        // Events (call during beforeStep by the EventManager where this is registered)
        virtual void mousePressEvent(QMouseEvent *) {}
        virtual void mouseReleaseEvent(QMouseEvent *) {}
        virtual void mouseMoveEvent(QMouseEvent *) {}
        virtual void keyPressEvent(QKeyEvent *) {}
        virtual void keyReleaseEvent(QKeyEvent *) {}
        virtual void enterViewPortEvent(QEvent *) {}
        virtual void leaveViewPortEvent(QEvent *) {}

    };
}
#endif // INPUTLISTENER_H
