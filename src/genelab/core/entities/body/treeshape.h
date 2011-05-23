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
        explicit TreeShape(QObject *parent = 0);
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
          * Init Ogre and Bullet references
          */
        void initOgreBullet(OgreEngine* ogreManager, BulletEngine *bulletManager);

        /**
          * Setup the shape : add all entities in Ogre and Bullet
          */
        void setup();

        /**
          * Contract all articulations in the middle of min and max
          */
        void contractInNormalPosition();

        /**
          * Print the shape in default output
          */
        void print();

    signals:

    public slots:

    private:

        Fixation* root;

        // Ogre & Bullet
        OgreEngine* ogreManager;
        BulletEngine *bulletManager;

        /** for recurcive browsing */
        void setupFixation(Fixation *fix);
    };
}
#endif // TREESHAPE_H
