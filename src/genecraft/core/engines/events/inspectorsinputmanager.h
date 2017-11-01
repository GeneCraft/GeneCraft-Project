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

#ifndef INSPECTORSINPUTMANAGER_H
#define INSPECTORSINPUTMANAGER_H

#include "genecraftcoreclasses.h"
#include "inputlistener.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

namespace GeneCraftCore {

class   InspectorsInputManager : public InputListener
{
    Q_OBJECT

public:

    InspectorsInputManager();

signals:

    void rigidBodySelected(btRigidBody *rigidBody);

    // selection
    void sEntitySelected(Entity * entity);
    void sBoneSelected(Bone * bone);
    void sFixationSelected(Fixation *fix);
    void sSensorsSelected(QList<Sensor*> s);

    // deletion
    void sEntityDeleted(Entity * entity);
    void sBoneDeleted(Bone * bone);
    void sFixationDeleted(Fixation *fix);

    // update
    void sBoneAdded(Bone * bone);
    void sBoneUpdated(Bone * bone);
    void sFixationUpdated(Fixation *fix);
    void sEntityUpdated(Entity * entity);
    void sExperimentUpdated(Experiment *experiment);

    // loading
    void sLoadExperiment(Experiment *experiment);
    void sLoadWorld(QJsonObject worldData);
    void sLoadEntity(QJsonObject genomeData, Ressource *ressource);
    void sLoadResult(Result*);


public slots:

    // selection
    void entitySelected(Entity * entity);
    void boneSelected(Bone * bone);
    void fixationSelected(Fixation *fix);
    void sensorsSelected(QList<Sensor*> s);

    // deletion
    void entityDeleted(Entity * entity);
    void boneDeleted(Bone * bone);
    void fixationDeleted(Fixation *fix);

    // update
    void boneAdded(Bone * bone);
    void boneUpdated(Bone * bone);
    void fixationUpdated(Fixation *fix);
    void entityUpdated(Entity * entity);
    void experimentUpdated(Experiment * experiment);

    // loading
    void loadExperiment(Experiment *experiment);
    void loadWorld(QJsonObject worldData);
    void loadEntity(QJsonObject genomeData, Ressource *ressource);
    void loadResult(Result *result);

};

}

#endif // INSPECTORSINPUTMANAGER_H
