#ifndef ENGINEFACTORY_H
#define ENGINEFACTORY_H

#include <QObject>

class EngineFactory : public QObject
{
    Q_OBJECT
public:
    explicit EngineFactory(QObject *parent = 0);

signals:

public slots:

};

#endif // ENGINEFACTORY_H
