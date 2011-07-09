#include "ressource.h"
#include "dbrecord.h"
#include "jsonfile.h"
#include <QVariantMap>

namespace GeneLabCore {
    Ressource::Ressource(QObject *parent) :
        QObject(parent)
    {
    }


    Ressource* Ressource::unserialize(QVariant v) {
        QVariantMap map = v.toMap();

        if(map["type"].toString() == "include") {
            map = map["data"].toMap();
        } else {
            return NULL;
        }

        QString type = map["type"].toString();

        if(type == "file") {
            JsonFile* f = new JsonFile(map["filename"].toString());
            return f;
        }

        if(type == "db") {
            DataBase db;
            db.dbName = map["dbName"].toString();
            db.port = map["port"].toInt();
            db.url = map["url"].toString();

            DbRecord* r = new DbRecord(db, map["id"].toString());
            return r;
        }
    }


    QVariant Ressource::load(QVariant data) {
        Ressource* r = unserialize(data);
        // Include of another data ?
        if(r) {
            QVariant includedData = r->load();
            delete r;
            return load(includedData); // Nested inclusion ?
        } else // Already loaded, not included
            return data;
    }


    QVariant Ressource::serialize(Ressource *r) {

    }
}
