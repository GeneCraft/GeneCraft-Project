#ifndef TREESHAPE_H
#define TREESHAPE_H
#include "genelabcoreclasses.h"
#include <QObject>

// TODO: INHERIT : Shape, -> CREATE CLASS SHAPE with method setup AND print
namespace GeneLabCore {
    class TreeShape : QObject
    {
        Q_OBJECT
    public:
        explicit TreeShape(btShapesFactory* shapeFactories, QObject *parent = 0);
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


    signals:

    public slots:

    private:

        Fixation* root;

        // Ogre & Bullet
        btShapesFactory* shapeFactories;
    };
}
#endif // TREESHAPE_H
