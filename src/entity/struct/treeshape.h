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
    ~TreeShape();

    Fixation* getRoot();
    void setRoot(Fixation*);

    void print();

signals:

public slots:

private:
    Fixation* root;

};

#endif // TREESHAPE_H
