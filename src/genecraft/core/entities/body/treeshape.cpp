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

#include "treeshape.h"

#include <QVariant>
#include <QVariantMap>

#include "fixation.h"
#include "treeshape.h"
#include "bone.h"
#include "bullet/bulletengine.h"
#include "btshapesfactory.h"

#include "sensors/sensor.h"
#include "sensors/accelerometersensor.h"
#include "sensors/gyroscopicsensor.h"
#include "sensors/positionsensor.h"
#include "sensors/contactsensor.h"
#include "sensors/boxsmellsensor.h"
#include "sensors/distancesensor.h"

#include "effectors/grippereffector.h"
#include "effectors/flyingeffector.h"

namespace GeneCraftCore {
    TreeShape::TreeShape(btShapesFactory* shapesFactory, QObject *parent) :
        QObject(parent)
    {
        this->shapesFactory = shapesFactory;
        this->root = NULL;
    }


    TreeShape::~TreeShape() {
        delete root;
    }

    void TreeShape::setRoot(Fixation *root) {
        this->root = root;
    }

    Fixation* TreeShape::getRoot() {
        return this->root;
    }

    void TreeShape::setup() {
        getRoot()->setup();
    }

    QJsonObject TreeShape::serialize()
    {
        QJsonObject treeShape, shape;

        treeShape.insert("shapeType", QString("TreeShape"));
        shape.insert("rootFix", root->serialize());
        treeShape.insert("shape",shape);

        return treeShape;
    }
}
