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

#include "box.h"
#include "btworld.h"
#include "btfactory.h"
#include "base/linkengine.h"

#include <QDebug>

namespace GeneCraftCore {

        /**
         * @brief Create a simple physical box in the world
         *
         * @param world the world where the box will be
         * @param size the size of the edge of the box
         * @param transform the initial position (see bulletphysics transform)
         * @param density the density of the box
         */
        Box::Box(btWorld *world, btVector3 size, const btTransform &transform, const btScalar density)
            : Node(world) {
            this->size = size;
            this->density = density;
        }

        /**
         * @brief destruct the box and remove it from the world
         *
         */
        Box::~Box() {
            LinkEngine* lkEngine =
                (LinkEngine*)world->getFactory()->getEngineByName("Link");
            foreach(Box* composite, composites) {
                if(delegate && delegate != composite) {
                    lkEngine->removeLink(delegate, composite);
                }

                delete composite;
            }
        }

        /**
         * @brief setup the box and add it in the world
         *
         */
        void Box::setup() {
            LinkEngine* lkEngine =
                (LinkEngine*)world->getFactory()->getEngineByName("Link");
            foreach(Box* composite, composites) {
                if(delegate && delegate != composite) {
                    lkEngine->addLink(delegate, composite);
                }

                composite->setup();
            }
        }

        /**
          * @brief to resize a box
          */
        void Box::resize(btVector3 size) {
            this->size = size;
            foreach(Box* composite, composites) {
                composite->resize(size);
            }
        }

        /**
          * @brief return the actual size
          */
        btVector3 Box::getSize() {
            return this->size;
        }

}
