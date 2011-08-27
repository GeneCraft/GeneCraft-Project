#ifndef JSONFILE_H
#define JSONFILE_H

#include "ressource.h"
#include <QVariant>
#include <QFile>

namespace GeneCraftCore {
class JsonFile : public Ressource
{

public:
    explicit JsonFile(QString filename, QObject *parent = 0);
    virtual QVariant load();
    virtual int save(QVariant data);
    virtual int remove();
    virtual QString getLocation();

public:
    QFile f;
    QString filename;

};

}
#endif // JSONFILE_H
