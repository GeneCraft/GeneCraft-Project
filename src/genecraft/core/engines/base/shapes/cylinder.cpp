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

#include "cylinder.h"
#include "base/linkengine.h"
#include "btfactory.h"
#include "btworld.h"

namespace GeneCraftCore {
    /**
     * @brief Construct a cylinder in a given world
     *
     * @param world the world where the cylinder will be
     * @param radius the radius of the cylinder
     * @param height the height of the cylinder
     * @param transform the initial position of the cylinder (bullet physics)
     * @param density the density of the cylinder
     */
    Cylinder::Cylinder(btWorld *world, btScalar radius, btScalar height, const btTransform &transform, const btScalar density)
        : Node(world) {
        this->radius = radius;
        this->height = height;
    }

    /**
     * @brief destruct and remove the cylinder from the world
     *
     */
    Cylinder::~Cylinder() {
        LinkEngine* lkEngine =
            (LinkEngine*)world->getFactory()->getEngineByName("Link");
        foreach(Cylinder* composite, composites) {
            if(delegate && delegate != composite) {
                lkEngine->removeLink(delegate, composite);
            }

            delete composite;
        }
    }

    /**
     * @brief setup the cylinder in the world
     *
     */
    void Cylinder::setup() {
        LinkEngine* lkEngine =
            (LinkEngine*)world->getFactory()->getEngineByName("Link");
        foreach(Cylinder* composite, composites) {
            if(delegate && delegate != composite) {
                lkEngine->addLink(delegate, composite);
            }
            composite->setup();
        }
    }

    /**
     * @brief change the size (both radius and height) of the cylinder
     *
     * @param radius the new radius of the cylinder
     * @param height the new height of the cylinder
     */
    void Cylinder::setSize(btScalar radius, btScalar height) {
        this->radius = radius;
        this->height = height;

        foreach(Cylinder* composite, composites) {
            composite->setSize(radius, height);
        }
    }


    /**
     * @brief return the radius of the cylinder
     *
     * @return the radius of the cylinder
     */
    btScalar Cylinder::getRadius() {
        return this->radius;
    }

    /**
     * @brief return the height of the cylinder
     *
     * @return height the height of the cylinder
     */
    btScalar Cylinder::getHeight() {
        return this->height;
    }

}
