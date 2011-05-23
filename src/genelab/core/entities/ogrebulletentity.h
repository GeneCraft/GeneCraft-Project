#ifndef OGREBULLETENTITY_H
#define OGREBULLETENTITY_H

#include "genelabcoreclasses.h"
#include "entity.h"

namespace GeneLabCore {

    class OgreBulletEntity : public GeneLabCore::Entity
    {
        Q_OBJECT
    public:
        explicit OgreBulletEntity(QString name, QString f, int gen, QObject *parent = 0);

    signals:

    public slots:
        void init(OgreEngine* ogreManager, BulletEngine* bulletManager, BrainEngine* brainEngine);
        void setup();
        void setShape(TreeShape* shape);
        TreeShape* getShape();

    private:
        TreeShape* shape;
        OgreEngine *ogreManager;
        BulletEngine *bulletManager;
        BrainEngine* brainEngine;
        NeuralNetwork* brain;

        void setupFixation(Fixation *fix);
    };

}
#endif // OGREBULLETENTITY_H
