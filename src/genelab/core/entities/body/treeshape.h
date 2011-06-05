#ifndef TREESHAPE_H
#define TREESHAPE_H
#include "genelabcoreclasses.h"
#include <QObject>
#include "LinearMath/btTransform.h"

// TODO: INHERIT : Shape, -> CREATE CLASS SHAPE with method setup AND print
namespace GeneLabCore {
    class TreeShape : QObject
    {
        Q_OBJECT
    public:
        explicit TreeShape(btShapesFactory* shapesFactory, QObject *parent = 0);
        void createRootFromGenotype(QVariant genotype, btTransform initTransform);
        ~TreeShape();

        /**
          * Get the root fixation
          */
        Fixation* getRoot();

        /**
          * Set the root fixation
          */
        void setRoot(Fixation*);

        /**
          * Setup the shape : add all entities in Ogre and Bullet
          */
        void setup();

        QVariant serialize();
        void buildFixFromGenotype(Fixation *fix, QVariant fixGenotype);

    signals:

    public slots:

    private:

        Fixation* root;

        // Ogre & Bullet
        btShapesFactory* shapesFactory;
    };
}
#endif // TREESHAPE_H
