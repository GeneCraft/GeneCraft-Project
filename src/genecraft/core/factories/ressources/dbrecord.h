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

#ifndef DBRECORD_H
#define DBRECORD_H

#include "ressource.h"
#include <QNetworkReply>
#include <QJsonObject>

namespace GeneCraftCore {

    struct DataBase {
        QString url;
        int port;
        QString dbName;
    };

    enum RequestType {RGET, RPOST, RPUT, RDELETE};

    class DbRecord : public Ressource
    {
        Q_OBJECT
    public:
        explicit DbRecord(DataBase db, QString id, QJsonObject postData = QJsonObject(), QObject *parent = 0);

        virtual QJsonObject load();
        virtual int save(QJsonObject data);
        virtual int remove();
        virtual QString getLocation();

        int deleteDoc(QString rev);

        bool error;
        QString errorString;
    signals:

    public slots:

    protected slots:
        void networkReply(QNetworkReply*);
        void request(QString url, RequestType verb, QString data = "");

    public:
        DataBase db;
        QString id;
        QString rev;
        QJsonObject postData;
    protected:
        QNetworkReply* r;

    };

}
#endif // DBRECORD_H
