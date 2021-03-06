/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ressource.h"
#include "dbrecord.h"
#include "jsonfile.h"
#include <QVariantMap>
#include <QDebug>
#include <QtScript>
#include <qxtjson.h>

namespace GeneCraftCore {
    int cptRessource = 0;
    Ressource::Ressource(QObject *parent) :
        QObject(parent)
    {
        cptRessource++;
    }
    Ressource::~Ressource() {

        cptRessource--;
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

    QString Ressource::beautifullJson(QString data) {

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
                                              QScriptValueList()
                                              << data
                                              << e->evaluate("({'indent_size': 1,'indent_char': ' '})"));
        //out << beautifullJson.toString();
        return bb.toString();
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
                                              QScriptValueList()
                                              << QxtJSON::stringify(data)
                                              << e->evaluate("({'indent_size': 1,'indent_char': ' '})"));
        //out << beautifullJson.toString();
        return bb.toString();
    }
}
