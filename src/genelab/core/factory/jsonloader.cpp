#include "jsonloader.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "qxtjson.h"

namespace GeneLabCore {
    JsonLoader::JsonLoader(QObject *parent) :
        QObject(parent)
    {
    }

    void JsonLoader::saveTo(QString ressourceType, QString id, QVariant data) {
        if(ressourceType == "file") {
            QFile f(id);
            f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
            QTextStream out(&f);
            out << QxtJSON::stringify(data);
        }
        else if(ressourceType == "db") {

        }
        else {
            qDebug() << "LoaderInfo : can't handle this ressource type.";
        }
    }

    QVariant JsonLoader::loadFrom(QString ressourceType, QString id) {
        QString content;

        if(ressourceType == "file") {
            QFile f(id);
            if(f.exists()) {
                // On ouvre le fichier et on le lit !
                if(f.open(QIODevice::ReadOnly | QIODevice::Text))
                    content = f.readAll();
            }
            else {
                qDebug() << "LoaderInfo : " << id << " don't exist !";
            }

        }
        else if(ressourceType == "db") {

        }
        qDebug() << "loading " << content;
        return QxtJSON::parse(content);
    }
}
