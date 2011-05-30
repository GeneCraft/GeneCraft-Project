#ifndef MODIFIER_H
#define MODIFIER_H

#include <QObject>
#include <QString>
#include "genelabcoreclasses.h"

namespace GeneLabCore {

class Modifier : public QObject
{
    Q_OBJECT
public:
    explicit Modifier(QObject *parent = 0);

    inline const QString &getTypeName() { return typeName; }

signals:

public slots:

    /**
     * Used to update world.
     */
    virtual void step() = 0;

protected:
    QString typeName;

};
}
#endif // MODIFIER_H
