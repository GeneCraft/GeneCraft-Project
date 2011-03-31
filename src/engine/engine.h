#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>

namespace GeneLabCore {

    class Engine : public QObject
    {
        Q_OBJECT
    public:
        explicit Engine(QObject *parent = 0): QObject(parent) {}

        virtual bool isRenderable() {
            return false;
        }

        virtual QWidget* getRenderWidget(QWidget* parent) {
            return NULL;
        }

    signals:

    public slots:
        virtual void beforeStep() = 0;
        virtual void step()       = 0;
        virtual void afterStep()  = 0;
    };

}

#endif // ENGINE_H
