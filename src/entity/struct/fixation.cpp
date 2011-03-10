#include "fixation.h"
#include <QStringBuilder>

Fixation::Fixation(QObject *parent) :
    QObject(parent)
{
}

Fixation::~Fixation() {
    while(!bones.isEmpty()) {
        Bone* b = bones.takeFirst();
        delete b;
    }
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

QString Fixation::toString() {
    QString b;
    b += "O";
    if(bones.length() > 1) {
        b += "{";
        for(int i = 0; i < bones.length(); i++) {
            b += bones[i]->toString();
            if(i+1 < bones.length())
                b+= ",";
        }
        b += "}";
    }
    else if(bones.length() == 1)
        b += bones.first()->toString();
    b += "";
    return b;
}
