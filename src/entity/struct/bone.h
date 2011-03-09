#ifndef BONE_H
#define BONE_H

#include <QObject>
#include "fixation.h"

class Fixation;

class Bone : public QObject
{
    Q_OBJECT
public:
    explicit Bone(QObject *parent = 0);
    Bone(float alpha, float beta_min, float beta_max, float r_min, float r_max, float length);

    float rotationCapacity();
    float hingeCapacity();
    float getAlpha();
    float getBeta();
    Fixation* getFixation();

signals:

public slots:

private:
    float alpha, beta_min, beta_max;
    float r_min, r_max;
    float length;
    Fixation* end;
};

#endif // BONE_H
