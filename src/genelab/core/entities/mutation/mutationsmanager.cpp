#include "mutationsmanager.h"

#include <QVariantMap>
#include "tools.h"
#include <QDebug>
#include "floatmutation.h"
#include "integermutation.h"
#include "brainnodemutation.h"

#define MAX_MUTATION_TRIES 100

namespace GeneLabCore {

    MutationsManager::MutationsManager(QVariant mutationsParams)
    {
        // Bone Length
        boneLength = new FloatMutation();
        boneLength->probability  = 0.1;
        boneLength->minFact      = 0.5;
        boneLength->maxFact      = 1.5;
        boneLength->minValue     = 0.1;
        boneLength->maxValue     = 5.0;

        // Bone radius mutation
        boneRadius = new FloatMutation();
        boneRadius->probability  = 0.1;
        boneRadius->minFact      = 0.5;
        boneRadius->maxFact      = 1.5;
        boneRadius->minValue     = 0.1;
        boneRadius->maxValue     = 2.0;

        // Fixation radius mutation
        fixRadius = new FloatMutation();
        fixRadius->probability   = 0.1;
        fixRadius->minFact       = 0.5;
        fixRadius->maxFact       = 1.5;
        fixRadius->minValue      = 0.1;
        fixRadius->maxValue      = 2.0;

        // Plug grid size
        brainSize = new IntegerMutation();
        brainSize->probability   = 0.1;
        brainSize->minFact       = 0.5;
        brainSize->maxFact       = 1.5;
        brainSize->minValue      = 1;
        brainSize->maxValue      = 100;
    }


    QVariant MutationsManager::mutateTreeShape(const QVariant &treeShapeVariant)
    {
        // Convert to map  (IT'S NOW A COPY !)
        QVariantMap treeShapeMap = treeShapeVariant.toMap();

        // mutate the root fix
        QVariant rootFixVariant = treeShapeMap.value("rootFix");
        rootFixVariant = mutateFixation(rootFixVariant);

        // mutate all bones
        QVariantMap rootFixMap = rootFixVariant.toMap(); // COPY !
        QVariantList newBonesList;
        foreach(QVariant boneVariant, rootFixMap.value("bones").toList())
            newBonesList.append(recursiveMutateTreeShape(boneVariant));

        rootFixMap.insert("bones",newBonesList);
        treeShapeMap.insert("rootFix",rootFixMap);
        return treeShapeMap;
    }

    QVariant MutationsManager::recursiveMutateTreeShape(QVariant &boneVariant) {

        // mutate bone
        boneVariant = mutateBone(boneVariant);
        QVariantMap boneVariantMap = boneVariant.toMap(); // COPY !

        // mutate the end fix
        QVariant endFixVariant = boneVariantMap.value("endFix"); // COPY !
        endFixVariant = mutateFixation(endFixVariant);

        // mutate all bones
        QVariantMap endFixMap = endFixVariant.toMap(); // COPY !
        QVariantList newBonesList;
        foreach(QVariant boneVariant, endFixMap.value("bones").toList())
            newBonesList.append(recursiveMutateTreeShape(boneVariant));

        endFixMap.insert("bones",newBonesList);
        boneVariantMap.insert("endFix",endFixMap);

        return boneVariantMap;
    }

    QVariant MutationsManager::mutateBone(const QVariant &boneVariant){

        QVariantMap boneMap = boneVariant.toMap();

        // length mutation ?
        boneLength->mutate(boneMap, "length");

        // radius mutation ?
        boneRadius->mutate(boneMap, "radius");

        return boneMap;
    }


    QVariant MutationsManager::mutateFixation(const QVariant &fixVariant){

        QVariantMap fixMap = fixVariant.toMap();

        // radius mutation ?
        fixRadius->mutate(fixMap, "radius");

        return fixMap;
    }

    // Mutate the brain
    QVariant MutationsManager::mutateBrain(QVariant brain) {
        QVariantMap brainMap = brain.toMap();
        brainSize->mutate(brainMap, "plugGridSize");
        return brainMap;
    }

    // Mutate a brainInput
    QVariant MutationsManager::mutateBrainIn(QVariant brainIn) {
        return brainIn;
    }

    // Mutate a brainOutput
    QVariant MutationsManager::mutateBrainOut(QVariant brainOut) {
        return brainOut;
    }
}
