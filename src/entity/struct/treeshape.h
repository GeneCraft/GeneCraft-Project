#ifndef TREESHAPE_H
#define TREESHAPE_H

#include "shape.h"
#include "fixation.h"
#include "bone.h"

class TreeShape : public Shape
{
    Q_OBJECT
public:
    explicit TreeShape(QObject *parent = 0);

signals:

public slots:

private:
    Fixation start;

};

#endif // TREESHAPE_H
