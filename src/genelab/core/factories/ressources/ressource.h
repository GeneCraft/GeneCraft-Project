#ifndef RESSOURCE_H
#define RESSOURCE_H

#include <QObject>
#include <QVariant>

namespace GeneLabCore {
    class Ressource : public QObject
    {
        Q_OBJECT
    public:
        explicit Ressource(QObject *parent = 0);

        virtual QVariant load() = 0;
        virtual void save(QVariant data) = 0;

    signals:

    public slots:

    };

}
#endif // RESSOURCE_H
