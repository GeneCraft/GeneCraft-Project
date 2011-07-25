#ifndef INSPECTORSINPUTMANAGER_H
#define INSPECTORSINPUTMANAGER_H

#include "genelabcoreclasses.h"
#include "inputlistener.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

namespace GeneLabCore {

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
    void sLoadWorld(QVariantMap worldData);
    void sLoadEntity(QVariantMap genomeData, Ressource *ressource);
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
    void loadWorld(QVariantMap worldData);
    void loadEntity(QVariantMap genomeData, Ressource *ressource);
    void loadResult(Result *result);

};

}

#endif // INSPECTORSINPUTMANAGER_H
