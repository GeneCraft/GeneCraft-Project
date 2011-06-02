#include "treeshape.h"

#include <QVariant>
#include <QVariantMap>

#include "fixation.h"
#include <QDebug>
#include <QStringBuilder>
#include "treeshape.h"
#include "bone.h"
#include <QList>
#include <QStack>
#include "ogreengine.h"
#include "bulletengine.h"
#include "btshapesfactory.h"

#include "OGRE/Ogre.h"

namespace GeneLabCore {
    TreeShape::TreeShape(btShapesFactory* factory, QObject *parent) :
        QObject(parent)
    {
        this->shapeFactories = factory;
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

    void TreeShape::setup()
    {
        //getRoot()->initOgreBullet(ogreManager,bulletManager);
        getRoot()->setup();
    }

    QVariant TreeShape::serialize()
    {
        QVariantMap shape;

        shape.insert("ShapeType", QVariant("TreeShape"));
        shape.insert("RootFix", root->serialize());

        return shape;
    }
}
