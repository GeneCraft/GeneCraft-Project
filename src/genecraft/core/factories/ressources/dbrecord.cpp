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

#include "dbrecord.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>

#include "qxtjson.h"

#include <QDebug>
#include <QVariantMap>

namespace GeneCraftCore {
    DbRecord::DbRecord(DataBase db, QString id, QVariant postData, QObject *parent) :
        Ressource(parent), db(db), id(id), rev(""), postData(postData)
    {
    }

    QVariant DbRecord::load() {
        error = true;
        if(postData == QVariant()) {
            QString url = QString("%1:%2/%3/%4").arg(db.url, QString::number(db.port), db.dbName, this->id);
            r = NULL;
            this->request(url, RGET);
            if(!r)
                return QVariant();

            r->deleteLater();
            if(r->error() == 0) {
                error = false;
                QVariantMap v = QxtJSON::parse(r->readAll()).toMap();
                if(v.contains("_id")) {
                    this->id = v.find("_id").value().toString();
                    this->rev = v.find("_rev").value().toString();
                }
                return v;
            } else {
                qDebug() << r->readAll();
                QVariantMap v;
                v.insert("error", r->errorString());
                return v;
            }
            return QVariant();
        } else {
            QString url = QString("%1:%2/%3/%4").arg(db.url, QString::number(db.port), db.dbName, this->id);
            r = NULL;
            this->request(url, RPOST, QxtJSON::stringify(postData));
            if(!r) {
                error = true;
                return QVariant();
            }

            qDebug() << r->error();
            r->deleteLater();
            if(r->error() == 0) {
                error = false;
                QVariantMap v = QxtJSON::parse(r->readAll()).toMap();
                if(v.contains("_id")) {
                    this->id = v.find("_id").value().toString();
                    this->rev = v.find("_rev").value().toString();
                }
                return v;
            } else {
                qDebug() << r->readAll();
                QVariantMap v;
                v.insert("error", r->errorString());
                return v;
            }
            return QVariant();
        }
    }

    int DbRecord::save(QVariant data) {
        QString url = QString("%1:%2/%3").arg(db.url, QString::number(db.port), db.dbName);

        if(this->id != "")
            url += "/" + this->id;

        QVariantMap mData = data.toMap();

        if(this->id != "")
            mData.insert("_id", this->id);
        if(this->rev != "")
            mData.insert("_rev", this->rev);

        RequestType type = RPUT;

        if(this->id == "" || this->id == "_bulk_docs")
            type = RPOST;

        r = NULL;
        this->request(url, type, QxtJSON::stringify(mData));
        if(!r)
            return -1;

        if(r->error() == 0) {
            QVariantMap v = QxtJSON::parse(r->readAll()).toMap();
            if(v.contains("id")) {
                this->id = v.find("id").value().toString();
                this->rev = v.find("rev").value().toString();
            }
            this->error = false;

        } else {
            this->error = true;
            this->errorString = r->errorString();
            qDebug() << r->readAll();
        }

        r->deleteLater();

        return this->error;
    }

    int DbRecord::remove() {
        return this->deleteDoc(this->rev);
    }

    int DbRecord::deleteDoc(QString rev) {
        QString url = QString("%1:%2/%3/%4?rev=%5").arg(db.url, QString::number(db.port), db.dbName,
                                                         this->id, rev);

        RequestType type = RDELETE;

        r = NULL;
        this->request(url, type);
        if(!r)
            return -1;

        qDebug() << r->error();
        if(r->error() == 0) {
            QVariantMap v = QxtJSON::parse(r->readAll()).toMap();
            this->error = false;

        } else {
            this->error = true;
            this->errorString = r->errorString();
            qDebug() << r->readAll();
        }

        r->deleteLater();

        return this->error;
    }

    void DbRecord::request(QString url, RequestType verb, QString data) {

        QNetworkAccessManager * pnam = new QNetworkAccessManager(this);

        connect(pnam, SIGNAL(finished(QNetworkReply *)), this,
              SLOT(networkReply(QNetworkReply*)));

        QNetworkRequest req = QNetworkRequest(QUrl(url));
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        switch(verb) {
        case RGET:
            pnam->get(req);
            break;
        case RPOST:
            pnam->post(req, data.toUtf8());
            break;
        case RPUT:
            pnam->put(req, data.toUtf8());
            break;
        case RDELETE:
            pnam->deleteResource(req);
            break;
        }

        // execute an event loop to process the request (nearly-synchronous)
        QEventLoop eventLoop;
        // also dispose the event loop after the reply has arrived
        connect(pnam, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
        eventLoop.exec();

        pnam->deleteLater();
    }

    void DbRecord::networkReply(QNetworkReply* r) {
        this->r = r;
    }

    QString DbRecord::getLocation() {
        return "online";
    }

}
