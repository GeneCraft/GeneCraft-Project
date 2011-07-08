#include "mutationsmanager.h"

#include <QVariantMap>
#include "tools.h"
#include <QDebug>

#define MAX_MUTATION_TRIES 100

namespace GeneLabCore {

MutationsManager::MutationsManager(QVariant mutationsParams)
{
    // Bone Length mutation
    probOfBoneLengthMutation    = 1.0; // 100%
    minFactOfBoneLengthMutation = 0.2; // - 80%
    maxFactOfBoneLengthMutation = 1.8; // + 80%
    minBoneLength               = 0.1;
    maxBoneLength               = 5.0;

    // Bone radius mutation
    probOfBoneRadiusMutation    = 1.0; // 100%
    minFactOfBoneRadiusMutation = 0.2; // - 80%
    maxFactOfBoneRadiusMutation = 1.8; // + 80%
    minBoneRadius               = 0.1;
    maxBoneRadius               = 2.0;

    // Fixation radius mutation
    probOfFixRadiusMutation    = 1.0; // 100%
    minFactOfFixRadiusMutation = 0.5; // - 80%
    maxFactOfFixRadiusMutation = 1.5; // + 80%
    minFixRadius               = 0.1;
    maxFixRadius               = 5.0;
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
        newBonesList.append(recurciveMutateTreeShape(boneVariant));

    rootFixMap.insert("bones",newBonesList);
    treeShapeMap.insert("rootFix",rootFixMap);
    return treeShapeMap;
}

QVariant MutationsManager::recurciveMutateTreeShape(QVariant &boneVariant) {

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
        newBonesList.append(recurciveMutateTreeShape(boneVariant));

    endFixMap.insert("bones",newBonesList);
    boneVariantMap.insert("endFix",endFixMap);

    return boneVariantMap;
}

QVariant MutationsManager::mutateBone(const QVariant &boneVariant){

    QVariantMap boneMap = boneVariant.toMap();

    // length mutation ?
    mutate(boneMap,"length",probOfBoneLengthMutation,minFactOfBoneLengthMutation,maxFactOfBoneLengthMutation,minBoneLength,maxBoneLength);

    // radius mutation ?
    mutate(boneMap,"radius",probOfBoneRadiusMutation,minFactOfBoneRadiusMutation,maxFactOfBoneRadiusMutation,minBoneRadius,maxBoneRadius);

    return boneMap;
}


QVariant MutationsManager::mutateFixation(const QVariant &fixVariant){

    QVariantMap fixMap = fixVariant.toMap();

    // radius mutation ?
    mutate(fixMap,"radius",probOfFixRadiusMutation,minFactOfFixRadiusMutation,maxFactOfFixRadiusMutation,minFixRadius,maxFixRadius);

    return fixMap;
}



void MutationsManager::mutate(QVariantMap &map, QString key, float probOfMutation, float minFactor, float maxFactor, float minValue, float maxValue){

    // mutation ?
    if(Tools::random(0.f,1.f) <= probOfMutation) {

        float newValue;

        for(int i=0; i < MAX_MUTATION_TRIES; ++i){

            float factor = Tools::random(minFactor,maxFactor);
            newValue = factor * map.value(key).toDouble();

            qDebug() << Q_FUNC_INFO << factor << key << " : " << newValue;

            // correct value
            if(newValue >= minValue && newValue <= maxValue){
                map.insert(key,newValue);
                break;
            }

            //qDebug() << Q_FUNC_INFO << "Incorrect mutation !";
        }
    }
}

}