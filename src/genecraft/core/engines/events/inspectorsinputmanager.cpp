/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "inspectorsinputmanager.h"

#include "entity.h"
#include "body/bone.h"
#include "body/fixation.h"

namespace GeneCraftCore{

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
void InspectorsInputManager::experimentUpdated(Experiment *experiment){
    emit sExperimentUpdated(experiment);
}

// experiment
void InspectorsInputManager::loadExperiment(Experiment *experiment){
    emit sLoadExperiment(experiment);
}
void InspectorsInputManager::loadWorld(QJsonObject worldData) {
    emit sLoadWorld(worldData);
}
void InspectorsInputManager::loadEntity(QJsonObject genomeData, Ressource *ressource) {
    emit sLoadEntity(genomeData, ressource);
}
void InspectorsInputManager::loadResult(Result *result) {
    emit sLoadResult(result);
}
}
