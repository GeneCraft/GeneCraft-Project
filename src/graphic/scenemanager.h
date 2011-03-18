#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <QObject>

namespace Ogre {
    class SceneManager;
    class Root;
}

class SceneManager : public QObject
{
    Q_OBJECT
public:
    explicit SceneManager(QObject *parent = 0);

    virtual void createScene(Ogre::SceneManager* sceneManager) = 0;
signals:

public slots:

};

#endif // SCENEMANAGER_H
