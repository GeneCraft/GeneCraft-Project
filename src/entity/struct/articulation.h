#ifndef ARTICULATION_H
#define ARTICULATION_H

#include <QObject>
#include "classes.h"

// OgreBullet
#include "OgreBulletDynamicsConstraint.h"
#include "Dynamics/Constraints/OgreBulletDynamics6DofConstraint.h"


// DELETE THIS CLASS

namespace GeneLabOgreBullet {
    class Articulation : public QObject
    {
        Q_OBJECT
    public:
        Articulation(QObject *parent = 0);

        Articulation(GeneLabOgreBullet::Fixation *fix, QObject *parent = 0);

    signals:

    public slots:

    private:

        OgreBulletDynamics::SixDofConstraint *parent, *child;
    };
}
#endif // ARTICULATION_H
