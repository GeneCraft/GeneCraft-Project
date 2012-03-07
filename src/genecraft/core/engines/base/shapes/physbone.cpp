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

#include "physbone.h"
#include "btworld.h"
#include "btfactory.h"
#include "base/linkengine.h"

#include <QDebug>

namespace GeneCraftCore {

const btScalar PhysBone::DENSITY = 1010.0; // Average body density
    /**
     * @brief Construct a PhysBone in a given world, and set informations about the
     way it's attached to the parent fixation
     *
     * @param world a world where the PhysBone will be located
     * @param length the length of the PhysBone
     * @param radius the radius of the PhysBone
     * @param radiusArticulation the radius of the sphere at the end of the PhysBone
     * @param transform the way the PhysBone is attached to the parent
     */
    PhysBone::PhysBone(btWorld *world, btScalar length, btScalar radius, btScalar radiusArticulation, const btTransform &transform)
        : Node(world){
        this->length = length;
        this->radius = radius;
        this->radiusArticulation = radiusArticulation;
    }
        /**
     * @brief simple bone destructor
     *
     */
    PhysBone::~PhysBone() {
        LinkEngine* lkEngine =
            (LinkEngine*)world->getFactory()->getEngineByName("Link");

        foreach(PhysBone* composite, composites) {
            qDebug() << "delete physbone composite";
            if(delegate && delegate != composite) {
                qDebug() << "remove link";
                lkEngine->removeLink(delegate, composite);
            }

            delete composite;
        }
    }

    /**
     * @brief setup the bone into the world, attach the bone to the parent and
     if necessary create the motor effector for it's joint.
     *
     */
    void PhysBone::setup() {
        LinkEngine* lkEngine =
            (LinkEngine*)world->getFactory()->getEngineByName("Link");
        foreach(PhysBone* composite, composites) {
            if(delegate && delegate != composite) {
                lkEngine->addLink(delegate, composite);
            }
            composite->setup();
        }
    }

    /**
     * @brief return the length of the bone
     *
     * @return btScalar the length of the bone
     */
    btScalar PhysBone::getLength() {
        return this->length;
    }

    /**
     * @brief return the radius of the bone
     *
     * @return btScalar the radius of the bone
     */
    btScalar PhysBone::getRadius() {
        return this->radius;
    }

    /**
     * @brief return the radius of the sphere at the end of the bone
     *
     * @return btScalar the radius of the fixation
     */
    btScalar PhysBone::getArticulationRadius() {
        return this->radiusArticulation;
    }

    /**
     * @brief change the bone size (both length and radius)
     *
     * @param radius the new radius of the bone
     * @param length the new length of the bone
     */
    void PhysBone::setSize(btScalar radius, btScalar length) {
        this->radius = radius;
        this->length = length;
        foreach(PhysBone* composite, composites) {
            composite->setSize(radius, length);
        }
    }

    /**
     * @brief change the ending sphere radius
     *
     * @param radius the new radius of the fixation
     */
    void PhysBone::setEndFixationRadius(btScalar radiusArticulation) {
        this->radiusArticulation = radiusArticulation;
        foreach(PhysBone* composite, composites) {
            composite->setEndFixationRadius(radius);
        }
    }


    btScalar PhysBone::getMass() const {
        if(this->delegate) {
            return this->delegate->getMass();
        }
        qDebug() << "no delegate defined, can't compute mass";
        return -1;
    }


}
