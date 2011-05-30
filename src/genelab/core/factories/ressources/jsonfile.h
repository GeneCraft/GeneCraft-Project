#ifndef JSONFILE_H
#define JSONFILE_H

#include "ressource.h"
#include <QVariant>
#include <QFile>

namespace GeneLabCore {
class JsonFile : public Ressource
{
    Q_OBJECT
public:
    explicit JsonFile(QString filename, QObject *parent = 0);

    virtual QVariant load();
    virtual void save(QVariant data);

signals:

public slots:

protected:
    QFile f;

};

}
#endif // JSONFILE_H
