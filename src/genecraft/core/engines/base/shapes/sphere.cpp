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

#include "sphere.h"

#include "btworld.h"
#include "btfactory.h"
#include "base/linkengine.h"

#include <QDebug>

namespace GeneCraftCore {


    /**
     * @brief construct a sphere in a given world
     *
     * @param btWorld the world where the sphere will be
     * @param radius the radius of the sphere
     * @param transform the initial transformation of the sphere
     * @param density the density of the sphere
     */
    Sphere::Sphere(btWorld *world, btScalar radius, const btTransform &transform, const btScalar density)
        : Node(world) {
        this->density = density;
        this->radius = radius;
    }

    /**
     * @brief destruct and remove the sphere from the world
     *
     */
    Sphere::~Sphere() {
        LinkEngine* lkEngine =
            (LinkEngine*)world->getFactory()->getEngineByName("Link");
        foreach(Sphere* composite, composites) {
            if(delegate && delegate != composite) {
                lkEngine->removeLink(delegate, composite);
            }

            delete composite;
        }
    }

    /**
     * @brief setup the sphere in the world
     *
     */
    void Sphere::setup() {
        LinkEngine* lkEngine =
            (LinkEngine*)world->getFactory()->getEngineByName("Link");
        foreach(Sphere* composite, composites) {
            if(delegate && delegate != composite) {
                lkEngine->addLink(delegate, composite);
            }
            composite->setup();
        }
    }

    /**
     * @brief change the size of the sphere
     *
     * @param radius the new radius of the sphere
     */
    void Sphere::setRadius(btScalar radius) {
        this->radius = radius;
        foreach(Sphere* composite, composites) {
            composite->setRadius(radius);
        }
    }

    /**
     * @brief return the size of the sphere
     *
     * @return radius the radius of the sphere
     */
    btScalar Sphere::getRadius() {
        return this->radius;
    }


    void Sphere::setFriction(btScalar friction) {
        this->friction = friction;
    }

    btScalar Sphere::getFriction() {
        return this->friction;
    }
}
