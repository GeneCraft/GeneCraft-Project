#include "genomemodifier.h"
#include <QDebug>

namespace GeneCraftCore {

    GenomeModifier::GenomeModifier(QObject *parent) :
        QObject(parent)
    {
        isPhysSym   = false;
        isPhysScale = false;
        isNeuralSym = false;
        isNeuralRot = false;

        physSym   = 0.;
        physScale = 1.;
        neuralSym = 0.;
        neuralAlpha = 0.;
        neuralDelta = 0.;

    }

    // Set the modifications parameters
    void GenomeModifier::setPhysicalSymmetry(btScalar alpha) {
        isPhysSym = true;
        physSym = alpha;
    }

    void GenomeModifier::setPhysicalScale   (btScalar scale) {
        isPhysScale = true;
        physScale = scale;
    }

    void GenomeModifier::setNeuralSymmetry  (btScalar alpha) {
        isNeuralSym = true;
        neuralSym = alpha;
    }

    void GenomeModifier::setNeuralRotation  (btScalar alpha, btScalar delta) {
        isNeuralRot = true;
        neuralAlpha = alpha;
        neuralDelta = delta;
    }

    // The modification will be applied to the bone element and all bone childs
    QVariant GenomeModifier::modify(QVariant element) {
        QVariantMap map = element.toMap();
        QString type = map["type"].toString();
        if(map.contains("endFix")) { // Bone
            // Modify physical parameters
            if(isPhysSym)
                applyBoneSymmetry(map);

            if(isPhysScale)
                applyBoneScale(map);

        } else if(map.contains("bones")) { // Fixation

            // Modify physical parameters
            if(isPhysSym)
                applyFixSymmetry(map);

            if(isPhysScale)
                applyFixScale(map);
        }

        return map;
    }


    void GenomeModifier::applyBoneSymmetry(QVariantMap& element) {

        // moving X by sym
        // inversing y
        QVariantMap rot = element["localRotation"].toMap();
        rot["z"] = rot["z"].toFloat() + physSym;
        rot["y"] = -rot["y"].toFloat();
        element["localRotation"] = rot;

        // inversiong some freedom degree to keep coherence
        QVariantMap lo = element["lowerLimits"].toMap();
        QVariantMap hi = element["upperLimits"].toMap();
        btScalar loX, loY;
        loX = lo["x"].toFloat();
        loY = lo["y"].toFloat();
        lo["x"] = -hi["x"].toFloat();
        hi["x"] = -loX;
        lo["y"] = -hi["y"].toFloat();
        hi["y"] = -loY;
        element["lowerLimits"] = lo;
        element["upperLimits"] = hi;

    }

    void GenomeModifier::applyBoneScale   (QVariantMap& element) {
        // Reduce length and radius
        element["length"] = element["length"].toFloat()*physScale;
        element["radius"] = element["radius"].toFloat()*physScale;

        QVariantMap endFix = element["endFix"].toMap();
        this->applyFixScale(endFix);

        element["endFix"] = endFix;

    }


    void GenomeModifier::applyFixSymmetry(QVariantMap& element) {
        // Nothing to do...
    }

    void GenomeModifier::applyFixScale(QVariantMap& element) {
        // Radius
        element["radius"] = element["radius"].toFloat()*physScale;
    }

}
