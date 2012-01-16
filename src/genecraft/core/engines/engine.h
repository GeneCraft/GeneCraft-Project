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

#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>

namespace GeneCraftCore {

/**
 * @brief An engine contains all mechanisme that interfer with simulation
 they have in charge the management of physical world, graphics, animations and
 also gameplay element. Everytime that you have to create something that need to
 be run on each simulation step, create an engine!

 During an engine step, it has access to everything he want about simulation, this
 reduce the concurrent issues since only one engine is stepped at a time and also
 increase the determinisme of the project.
 *
 */
class Engine : public QObject
{

public:
    /**
     * @brief basic constructor
     *
     * @param parent
     */
    explicit Engine(QObject *parent = 0): QObject(parent) {}

    /**
     * @brief not really used, but should make a distinction between render engine
     and physical/logic engines
     *
     * @return bool is the engine renderable
     */
    virtual bool isRenderable() {
        return false;
    }

    /**
     * @brief called before all simulations steps
     *
     */
    virtual void beforeStep()   {}
    /**
     * @brief is called during each simulations steps
     *
     */
    virtual void step()         {}
    /**
     * @brief is called after each simulations steps
     *
     */
    virtual void afterStep()    {}
};

}

#endif // ENGINE_H
