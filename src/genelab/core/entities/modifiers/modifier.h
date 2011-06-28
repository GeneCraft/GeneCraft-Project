#ifndef MODIFIER_H
#define MODIFIER_H

#include <QObject>
#include <QString>
#include "genelabcoreclasses.h"

namespace GeneLabCore {

enum EffectorType { rotationalMotor };

class Effector : public QObject
{
    Q_OBJECT
public:
    explicit Effector(QObject *parent = 0);
    Effector(QVariant data);
    virtual QVariant serialize();

    const QString &getTypeName() { return typeName; }
    const QList<BrainOut*> getOutputs() { return outs; }

signals:

public slots:

    /**
     * Used to update world.
     */
    virtual void step() = 0;

protected:
    QString typeName;
    QList<BrainOut*> outs;

};
}
#endif // MODIFIER_H
