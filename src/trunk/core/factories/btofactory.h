#ifndef BTOFACTORY_H
#define BTOFACTORY_H

#include "genecraftcoreclasses.h"
#include "btfactory.h"

namespace GeneCraftCore {

class btoFactory : public btFactory
{
    Q_OBJECT
public:
    explicit btoFactory(QWidget* sceneWidget, unsigned long winId, QObject *parent = 0);

signals:

public slots:

};
}

#endif // BTOFACTORY_H
