#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <QObject>

class EntityFactory : public QObject
{
    Q_OBJECT
public:
    explicit EntityFactory(QObject *parent = 0);

signals:

public slots:

};

#endif // ENTITYFACTORY_H
