#include "dbrecord.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>

#include "qxtjson.h"

#include <QDebug>
#include <QVariantMap>

namespace GeneLabCore {
    DbRecord::DbRecord(DataBase db, QString id, QObject *parent) :
        Ressource(parent), db(db), id(id), rev("")
    {
    }

    QVariant DbRecord::load() {
        QString url = QString("%1:%2/%3/%4").arg(db.url, QString::number(db.port), db.dbName, this->id);
        this->request(url, RGET);
        qDebug() << r->error();
        if(r->error() == 0) {
            QVariantMap v = QxtJSON::parse(r->readAll()).toMap();
            this->id = v.find("_id").value().toString();
            this->rev = v.find("_rev").value().toString();
            return v;
        } else {
            qDebug() << r->readAll();
            QVariantMap v;
            v.insert("error", r->errorString());
            return v;
        }

        r->deleteLater();
    }

    void DbRecord::save(QVariant data) {
        QString url = QString("%1:%2/%3/%4").arg(db.url, QString::number(db.port), db.dbName, this->id);
        QVariantMap mData = data.toMap();
        mData.insert("_id", this->id);
        if(this->rev != "")
            mData.insert("_rev", this->rev);


        qDebug() << url;
        this->request(url, RPUT, QxtJSON::stringify(mData));
        qDebug() << r->error();
        if(r->error() == 0) {
            QVariantMap v = QxtJSON::parse(r->readAll()).toMap();
            this->id = v.find("id").value().toString();
            this->rev = v.find("rev").value().toString();
            this->error = false;

        } else {
            this->error = true;
            this->errorString = r->errorString();
            qDebug() << r->readAll();
        }

        r->deleteLater();
    }

    void DbRecord::request(QString url, RequestType verb, QString data) {

        QNetworkAccessManager * pnam = new QNetworkAccessManager(this);

        connect(pnam, SIGNAL(finished(QNetworkReply *)), this,
              SLOT(networkReply(QNetworkReply*)));

        QNetworkRequest req = QNetworkRequest(QUrl(url));

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


}
