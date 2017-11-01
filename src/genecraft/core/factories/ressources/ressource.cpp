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
#include <QJsonDocument>
#include <QJsonObject>

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


    Ressource* Ressource::unserialize(QJsonObject map) {

        if(map["type"].toString() == "include") {
            map = map["data"].toObject();
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


    QJsonObject Ressource::load(QJsonObject data) {
        Ressource* r = unserialize(data);
        // Include of another data ?
        if(r) {
            QJsonObject includedData = r->load();
            delete r;
            return load(includedData); // Nested inclusion ?
        } else // Already loaded, not included
            return data;
    }


    QJsonObject Ressource::serialize(JsonFile *r) {
        QJsonObject ressourceMap;
        QJsonObject data;

        data.insert("type", "file");

        data.insert("filename", r->filename);

        ressourceMap.insert("type", "include");
        ressourceMap.insert("data", data);

        return ressourceMap;
    }


    QJsonObject Ressource::serialize(DbRecord *r) {
        QJsonObject ressourceMap;
        QJsonObject data;

        data.insert("type", "db");

        data.insert("url", r->db.url);
        data.insert("dbName", r->db.dbName);
        data.insert("port", r->db.port);

        data.insert("id", r->id);

        ressourceMap.insert("type", "include");
        ressourceMap.insert("data", data);

        return ressourceMap;
    }
}
