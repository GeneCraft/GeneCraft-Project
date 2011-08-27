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

    QVariant TreeShape::serialize()
    {
        QVariantMap treeShape, shape;

        treeShape.insert("shapeType", QVariant("TreeShape"));
        shape.insert("rootFix", root->serialize());
        treeShape.insert("shape",shape);

        return treeShape;
    }
}
