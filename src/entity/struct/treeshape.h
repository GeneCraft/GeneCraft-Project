#ifndef TREESHAPE_H
#define TREESHAPE_H
#include "classes.h"
#include <QObject>


// TODO: CREATE CLASS SHAPE with method setup AND print

namespace GeneLabOgreBullet {
    class TreeShape : QObject
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
}
#endif // TREESHAPE_H
