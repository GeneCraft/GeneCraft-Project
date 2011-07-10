#include "mutationsmanager.h"

#include <QVariantMap>
#include "tools.h"
#include <QDebug>

#define MAX_MUTATION_TRIES 100

namespace GeneLabCore {

    MutationsManager::MutationsManager(QVariant mutationsParams)
    {
        // Bone Length mutation
        boneLength.probability  = 0.1;
        boneLength.minFact      = 0.5;
        boneLength.maxFact      = 1.5;
        boneLength.minValue     = 0.1;
        boneLength.maxValue     = 5.0;

        // Bone radius mutation
        boneRadius.probability  = 0.1;
        boneRadius.minFact      = 0.5;
        boneRadius.maxFact      = 1.5;
        boneRadius.minValue     = 0.1;
        boneRadius.maxValue     = 2.0;

        // Fixation radius mutation
        fixRadius.probability   = 0.1;
        fixRadius.minFact       = 0.5;
        fixRadius.maxFact       = 1.5;
        fixRadius.minValue      = 0.1;
        fixRadius.maxValue      = 2.0;

        // Plug grid size
        brainSize.probability   = 0.1;
        brainSize.minFact       = 0.5;
        brainSize.maxFact       = 1.5;
        brainSize.minValue      = 1;
        brainSize.maxValue      = 100;
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
        mutate(boneMap, "length", boneLength);

        // radius mutation ?
        mutate(boneMap, "radius", boneRadius);

        return boneMap;
    }


    QVariant MutationsManager::mutateFixation(const QVariant &fixVariant){

        QVariantMap fixMap = fixVariant.toMap();

        // radius mutation ?
        mutate(fixMap, "radius", fixRadius);

        return fixMap;
    }



    void MutationsManager::mutate(QVariantMap &map, QString key, Mutation mutation){

        // mutation ?
        if(Tools::random(0.f,1.f) <= mutation.probability) {

            //for(int i=0; i < MAX_MUTATION_TRIES; ++i){

                float factor = Tools::random(mutation.minFact, mutation.maxFact);
                float newValue = factor * map.value(key).toDouble();

                // correct value
                //if(newValue >= minValue && newValue <= maxValue){
                //} // La capé serait mieux

                if(newValue < mutation.minValue)
                    newValue = mutation.minValue;

                if(newValue > mutation.maxValue)
                    newValue = mutation.maxValue;


                map.insert(key,QVariant((double)newValue));
                //break;

                //qDebug() << Q_FUNC_INFO << "Incorrect mutation !" << factor << key << " : " << newValue;
            //}
        }



    }

    // Mutate the brain
    QVariant MutationsManager::mutateBrain(QVariant brain) {
        QVariantMap brainRetour = brain.toMap();
        this->mutate(brainRetour, "plugGridSize", brainSize);
    }

    // Mutate a brainInput
    QVariant MutationsManager::mutateBrainIn(QVariant brainIn) {

    }

    // Mutate a brainOutput
    QVariant MutationsManager::mutateBrainOut(QVariant brainOut) {
    }
}
