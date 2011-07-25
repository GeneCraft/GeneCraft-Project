#include "inspectorsinputmanager.h"

#include "entity.h"
#include "body/bone.h"
#include "body/fixation.h"

namespace GeneLabCore{

InspectorsInputManager::InspectorsInputManager()
{
}

// selection
void InspectorsInputManager::entitySelected(Entity *entity){
    emit sEntitySelected(entity);
}
void InspectorsInputManager::boneSelected(Bone *bone){
    emit sBoneSelected(bone);
}
void InspectorsInputManager::fixationSelected(Fixation *fix){
    emit sFixationSelected(fix);
}
void InspectorsInputManager::sensorsSelected(QList<Sensor*> s){
    emit sSensorsSelected(s);
}

// deletion
void InspectorsInputManager::entityDeleted(Entity *entity){
    emit sEntityDeleted(entity);
}
void InspectorsInputManager::boneDeleted(Bone *bone){
    emit sBoneDeleted(bone);
}
void InspectorsInputManager::fixationDeleted(Fixation *fix){
    emit sFixationDeleted(fix);
}

// update
void InspectorsInputManager::boneAdded(Bone *bone){
    emit sBoneAdded(bone);
}
void InspectorsInputManager::boneUpdated(Bone *bone){
    emit sBoneUpdated(bone);
}
void InspectorsInputManager::fixationUpdated(Fixation *fix){
    emit sFixationUpdated(fix);
}
void InspectorsInputManager::entityUpdated(Entity *entity){
    emit sEntityUpdated(entity);
}

// experiment
void InspectorsInputManager::loadExperiment(Experiment *experiment){
    emit sLoadExperiment(experiment);
}
void InspectorsInputManager::loadWorld(QVariantMap worldData) {
    emit sLoadWorld(worldData);
}
void InspectorsInputManager::loadEntity(QVariantMap genomeData, Ressource *ressource) {
    emit sLoadEntity(genomeData, ressource);
}
void InspectorsInputManager::loadResult(Result *result) {
    emit sLoadResult(result);
}
}
