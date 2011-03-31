#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#include <QObject>
#include "classes.h"

namespace GeneLabCore {
    class GraphicsEngine : public QObject
    {
        Q_OBJECT
    public:
        explicit GraphicsEngine(QObject *parent = 0);
        // Engine initialisation
        virtual void init() = 0;
        // Scene getter
        virtual GraphicsScene* getGraphicsScene() = 0;

    signals:

    public slots:
        // Engine step by step
        virtual void graphicsStep() = 0;
    };
}

#endif // GRAPHICSENGINE_H
