#ifndef GENOMEBUILDER_H
#define GENOMEBUILDER_H

#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include <QList>

#include "entity.h"

#include "genomemodifier.h"

namespace GeneCraftCore {

class GenomeBuilder : public QObject
{
    Q_OBJECT
public:
    explicit GenomeBuilder(QObject *parent = 0);

    // To create an entity with its genome
    static Entity*    buildEntity(QVariant genotype,
                                btShapesFactory *shapesFactory,
                                const btVector3 &initialPosition);

    // Create the root fixation
    //static Fixation* createRootFromGenotype(btShapesFactory *shapesFactory, QVariant genotype, btTransform initTransform);

    // Build a fixation from the genome
    //static void buildFixFromGenotype(btShapesFactory *shapesFactory, Fixation *fix, Fixation* root, QVariant fixGenotype);

    static Fixation*  buildBone(btShapesFactory* shapesFactory, Fixation *parent,  QList<GenomeModifier*> modifier, QVariant genome, Bone* ref);
    static Fixation*  buildFix(btShapesFactory* shapesFactory, Fixation  *fix,  QList<GenomeModifier*> modifier, QVariant genome, Bone* ref);
    static Fixation*  buildElement(btShapesFactory* shapesFactory, Fixation *parent,  QList<GenomeModifier*> modifier, QVariant genome, Bone* ref);
    static Fixation*  buildRoot(btShapesFactory* shapesFactory, QVariant genotype, btTransform initPos);
signals:

public slots:

};

}

#endif // GENOMEBUILDER_H

