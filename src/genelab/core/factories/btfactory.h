#ifndef BTFACTORY_H
#define BTFACTORY_H

#include <QObject>
#include <QMap>
#include "genelabcoreclasses.h"

namespace GeneLabCore {

class btFactory : public QObject
{
    Q_OBJECT
public:
    explicit btFactory(QObject *parent = 0);

    // To get an engine by its name
    Engine *getEngineByName(QString name);

    // To get all engines
    QMap<QString, Engine*> getEngines();

    // To get all widgets
    QMap<QString, QWidget*> getWidgets();

signals:

public slots:

protected:
    QMap<QString, Engine*>         engines;
    QMap<QString, QWidget*>        widgets;
};

}

#endif // BTFACTORY_H
