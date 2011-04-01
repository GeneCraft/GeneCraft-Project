#include "bone.h"
#include "entity/struct/fixation.h"

namespace GeneLabOgreBullet {
    Bone::Bone(QObject *parent) :
        QObject(parent)
    {
        end = new Fixation();
    }

    Bone::~Bone() {
        delete end;
    }

    Bone::Bone(float alpha, float beta_min, float beta_max, float r_min, float r_max, float length) {
        this->alpha = alpha;
        this->beta_min = beta_min;
        this->beta_max = beta_max;
        this->r_min = r_min;
        this->r_max = r_max;
        this->length = length;

        end = new Fixation();
    }

    float Bone::getLength() {
        return this->length;
    }

    float Bone::rotationCapacity() {
        return r_max - r_min;
    }

    float Bone::hingeCapacity() {
        return beta_max - beta_min;
    }

    float Bone::getAlpha() {
        return alpha;
    }

    float Bone::getBeta() {
        return beta_min;
    }

    Fixation* Bone::getFixation() {
        return end;
    }

    QString Bone::toString() {
        return "-" + QString::number(length) + "-" + this->end->toString();
    }
}
