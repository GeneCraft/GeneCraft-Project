#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <QObject>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QEvent>
#include <QQueue>
#include "genecraftcoreclasses.h"
#include "engine.h"
#include "inputlistener.h"

namespace GeneCraftCore {

    /**
      * EventManager is an Engine.
      *
      * The aim of EventManager is to stock events raised by a Qt widgets and forward them to all registered InputListener
      * when the method beforeStep is called by the Engines Manager (SimulationManager).
      *
      * Thus, the management of events is sequential and avoiding the problems of concurrent access to engine objects.
      *
      * @author Da Campo Aurelien
      * @author Cyprien Huissoud
      * @version 1.0 | April 2011
      * @see Engine
      * @see InputListener
      */
    class EventsManager : public Engine
    {
        Q_OBJECT

    public:

        // Constructor
        EventsManager(QObject *parent = 0);

        /**
          * Used to register an InputListener
          */
        void addListener(InputListener *);

        /**
          * Used to unregister an InputListener
          */
        void removeListener(InputListener *);

    private:

        // Events will be managed during steps calls and not directly when they are detected
        QQueue<QEvent*> eventsQueue;

        /**
          * List of registered InputListener
          */
        QList<InputListener*> inputListeners;

    signals:

    public slots:

        // Events (only used to save event into eventsQueue)
        void mousePressEvent(QMouseEvent * e);
        void mouseReleaseEvent(QMouseEvent * e);
        void mouseMoveEvent(QMouseEvent * e);
        void keyPressEvent(QKeyEvent *e);
        void keyReleaseEvent(QKeyEvent *e);
        void enterViewPortEvent(QEvent *e);
        void leaveViewPortEvent(QEvent *e);

        // Engine
        void beforeStep();
        void step();
        void afterStep();
    };
}
#endif // EVENTMANAGER_H
