#ifndef FIXATION_H
#define FIXATION_H

#include <QObject>
#include <QList>
#include "bone.h"

class Bone;

class Fixation : public QObject
{
    Q_OBJECT
public:
    explicit Fixation(QObject *parent = 0);
    ~Fixation();

    Bone* addBone(float alpha,
                 float beta,
                 float length);

    Bone* addBone(float alpha,
                 float beta_min, float beta_max,
                 float length);

    Bone* addBone(float alpha,
                 float beta,
                 float r_min, float r_max,
                 float length);

    Bone* addBone(float alpha,
                 float beta_min, float beta_max,
                 float r_min, float r_max,
                 float length);

    QList<Bone*> getBones();

    QString toString();

signals:

public slots:

private:
    QList<Bone*> bones;

};

#endif // FIXATION_H
