#include "jsonfile.h"

#include <QTextStream>
#include <QDebug>

#include "qxtjson.h"

namespace GeneLabCore {
    JsonFile::JsonFile(QString filename, QObject *parent) :
        Ressource(parent), f(filename), filename(filename)
    {

    }


    int JsonFile::save(QVariant data) {
        f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
        QTextStream out(&f);
        out << QxtJSON::stringify(data);
        f.close();

        return f.error();
    }

    QVariant JsonFile::load() {
        QString content;
        if(f.exists()) {
            // On ouvre le fichier et on le lit !
            if(f.open(QIODevice::ReadOnly | QIODevice::Text))
                content = f.readAll();
        } else {
            qDebug() << "Could not open " << f.fileName();
        }

        f.close();
        return QxtJSON::parse(content);
    }
}
