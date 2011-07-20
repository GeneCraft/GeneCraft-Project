#include "ressource.h"
#include "dbrecord.h"
#include "jsonfile.h"
#include <QVariantMap>
#include <QDebug>
#include <QtScript>
#include <qxtjson.h>

namespace GeneLabCore {
    int cptRessource = 0;
    Ressource::Ressource(QObject *parent) :
        QObject(parent)
    {
        cptRessource++;
        qDebug() << "res" << cptRessource;
    }
    Ressource::~Ressource() {

        cptRessource--;
        qDebug() << "res" <<cptRessource;
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

        return NULL;
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


    QVariant Ressource::serialize(JsonFile *r) {
        QVariantMap ressourceMap;
        QVariantMap data;

        data.insert("type", "file");

        data.insert("filename", r->filename);

        ressourceMap.insert("type", "include");
        ressourceMap.insert("data", data);

        return ressourceMap;
    }


    QVariant Ressource::serialize(DbRecord *r) {
        QVariantMap ressourceMap;
        QVariantMap data;

        data.insert("type", "db");

        data.insert("url", r->db.url);
        data.insert("dbName", r->db.dbName);
        data.insert("port", r->db.port);

        data.insert("id", r->id);

        ressourceMap.insert("type", "include");
        ressourceMap.insert("data", data);

        return ressourceMap;
    }

    QString Ressource::beautifullJson(QVariant data) {
        static QScriptEngine* e = NULL;

        if(!e) {
            e = new QScriptEngine();
            QFile fjs(":/js/js-beautifull");
            fjs.open(QIODevice::ReadOnly |QIODevice::Text);
            QString js = fjs.readAll();
            e->evaluate(js);
        }

        QScriptValue beautifullJson = e->evaluate("js_beautify");
        QScriptValue bb = beautifullJson.call(QScriptValue(),
                                              QScriptValueList() << QxtJSON::stringify(data));
        //out << beautifullJson.toString();
        return bb.toString();
    }
}
