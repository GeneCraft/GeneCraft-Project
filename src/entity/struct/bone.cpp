#include "bone.h"

Bone::Bone(QObject *parent) :
    QObject(parent)
{
    end = new Fixation();
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
