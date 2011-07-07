#ifndef INPUTLISTENER_H
#define INPUTLISTENER_H

#include <QObject>
#include <QMouseEvent>
#include <QKeyEvent>

namespace GeneLabCore {

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
        virtual void mouseReleaseEvent(QMouseEvent *) = 0;
        virtual void mouseMoveEvent(QMouseEvent *) = 0;
        virtual void keyPressEvent(QKeyEvent *) = 0;
        virtual void keyReleaseEvent(QKeyEvent *) = 0;
        virtual void enterViewPortEvent(QEvent *) = 0;
        virtual void leaveViewPortEvent(QEvent *) = 0;

    };
}
#endif // INPUTLISTENER_H
