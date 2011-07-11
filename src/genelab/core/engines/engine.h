#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>

namespace GeneLabCore {

/**
 * (c) COPYRIGHT GeneCraft 2011, Aurelien Da Campo & Cyprien Huissoud
 *
 * An engine has mainly 3 methods that are called by the simulator.
 *
 * @version 1.0 | May 2011
 * @author Aurelien Da Campo
 * @author Cyprien Huissoud
 */
class Engine : public QObject
{

public:
    explicit Engine(QObject *parent = 0): QObject(parent) {}

    virtual bool isRenderable() {
        return false;
    }

    virtual void beforeStep()   {}
    virtual void step()         {}
    virtual void afterStep()    {}
};

}

#endif // ENGINE_H
