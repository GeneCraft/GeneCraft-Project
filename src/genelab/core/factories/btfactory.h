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


    QMap<QString, Engine*>        getEngines();
    QMap<QString, QWidget*>       getWidgets();
    btShapesFactory *             getShapesFactory();

signals:

public slots:

protected:
    QMap<QString, Engine*>         engines;
    QMap<QString, QWidget*>        widgets;
    btShapesFactory *              shapesFactory;

};

}

#endif // BTFACTORY_H
