#ifndef NINJASCENE_H
#define NINJASCENE_H

#include "scenemanager.h"

class NinjaScene : public SceneManager
{
    Q_OBJECT
public:
    explicit NinjaScene(QObject *parent = 0);

    void createScene(Ogre::SceneManager* sceneManager);
signals:

public slots:

};

#endif // NINJASCENE_H
