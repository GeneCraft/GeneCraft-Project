#include "fixation.h"

Fixation::Fixation(QObject *parent) :
    QObject(parent)
{
}


Bone* Fixation::addBone(float alpha, float beta, float length) {
    return this->addBone(alpha, beta, beta, 0, 0, length);
}

Bone* Fixation::addBone(float alpha, float beta, float r_min, float r_max, float length) {
    return this->addBone(alpha, beta, beta, r_min, r_max, length);
}

Bone* Fixation::addBone(float alpha, float beta_min, float beta_max, float length) {
    return this->addBone(alpha, beta_min, beta_max, 0, 0, length);
}

Bone* Fixation::addBone(float alpha, float beta_min, float beta_max, float r_min, float r_max, float length) {
    Bone* b = new Bone(alpha, beta_min, beta_max, r_min, r_max, length);
    this->bones.append(b);
    return b;
}

QList<Bone*> Fixation::getBones() {
    return bones;
}
