#include "treeshape.h"

#include <QVariant>
#include <QVariantMap>

#include "fixation.h"
#include "treeshape.h"
#include "bone.h"
#include "ogreengine.h"
#include "bulletengine.h"
#include "btshapesfactory.h"

#include "OGRE/Ogre.h"

namespace GeneLabCore {
    TreeShape::TreeShape(btShapesFactory* shapesFactory, QObject *parent) :
        QObject(parent)
    {
        this->shapesFactory = shapesFactory;
        this->root = NULL;
    }

    TreeShape::TreeShape(btShapesFactory* shapeFactories, QVariant genotype, btTransform initTransform, QObject *parent) :
        QObject(parent)
    {
        this->shapesFactory = shapesFactory;

        QVariantMap treeShapeMap = genotype.toMap();

        // Root fix
        QVariantMap rootFixMap = treeShapeMap.value("rootFix").toMap();

        root = new Fixation(shapeFactories, rootFixMap.value("radius").toDouble(), initTransform);

        buildFixFromGenotype(root,treeShapeMap.value("rootFix"));
    }

    void TreeShape::buildFixFromGenotype(Fixation *fix, QVariant fixGenotype)
    {
        QVariantList bonesVariantList = fixGenotype.toMap().value("bones").toList();

        foreach(QVariant bone, bonesVariantList)
        {
            QVariantMap boneMap = bone.toMap();

            // Radius & lenght
            btScalar boneRadius = boneMap.value("radius").toDouble();
            btScalar boneLength = boneMap.value("length").toDouble();

            btScalar endFixRadius = boneMap.value("endFix").toMap().value("radius").toDouble();

            // Yaw & Roll (local)
            QVariantMap localRotationMap = boneMap.value("localRotation").toMap();
            btScalar yAxisRot = localRotationMap.value("y").toDouble();
            btScalar zAxisRot = localRotationMap.value("z").toDouble();

            // Limits
            btVector3 lowerLimits, upperLimits;
            QVariantMap lowerLimitsMap = boneMap.value("lowerLimits").toMap();
            QVariantMap upperLimitsMap = boneMap.value("upperLimits").toMap();

            lowerLimits.setValue(lowerLimitsMap.value("x").toDouble(),
                                 lowerLimitsMap.value("y").toDouble(),
                                 lowerLimitsMap.value("z").toDouble());
            upperLimits.setValue(upperLimitsMap.value("x").toDouble(),
                                 upperLimitsMap.value("y").toDouble(),
                                 upperLimitsMap.value("z").toDouble());

            Bone *bone = fix->addBone(yAxisRot,zAxisRot,boneRadius,boneLength,endFixRadius,lowerLimits,upperLimits);

            // Add bone recurcively
            buildFixFromGenotype(bone->getEndFixation(),boneMap.value("endFix"));
        }
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
        QVariantMap treeShape, shape;

        treeShape.insert("shapeType", QVariant("TreeShape"));
        shape.insert("rootFix", root->serialize());
        treeShape.insert("shape",shape);

        return treeShape;
    }
}
