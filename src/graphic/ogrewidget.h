#ifndef OGREWIDGET_H
#define OGREWIDGET_H

#include <QGLWidget>
#include <OGRE/Ogre.h>
#include <QX11Info>

class OgreWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit OgreWidget(QWidget *parent = 0);

signals:

public slots:

};

#endif // OGREWIDGET_H
