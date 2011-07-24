#ifndef DBRECORD_H
#define DBRECORD_H

#include "ressource.h"
#include <QNetworkReply>

namespace GeneLabCore {

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
        explicit DbRecord(DataBase db, QString id, QVariant postData = QVariant(), QObject *parent = 0);

        virtual QVariant load();
        virtual int save(QVariant data);
        virtual int remove();

        void deleteDoc(QString rev);

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
        QVariant postData;
    protected:
        QNetworkReply* r;

    };

}
#endif // DBRECORD_H
