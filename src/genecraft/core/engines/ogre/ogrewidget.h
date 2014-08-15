/*
Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud

This file is part of Genecraft-Project.

Genecraft-Project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Genecraft-Project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OGREWIDGET_H
#define OGREWIDGET_H

#include <QGLWidget>
#include <QX11Info>
#include <QMutex>
#include <QMouseEvent>
#include "genecraftcoreclasses.h"
#include "ogre/entities/ogrefreecamera.h"
#include <Ogre.h>
#include "entity.h"

namespace GeneCraftCore {
    class OgreWidget : public QWidget
    {
        Q_OBJECT

    public:
        OgreWidget(Ogre::Root* ogreRoot,
                   Ogre::SceneManager* scnManager,
                   Ogre::Camera* camera,
                   QWidget *parent);

        ~OgreWidget();

        void step();

        OgreFreeCamera *getOgreFreeCamera() { return ogreFreeCamera; }

    public:
        bool resized;
    public slots:

        void resize();
        void init();
        void resizeEvent(QResizeEvent* evt);
        QPaintEngine *paintEngine() const
        {
            return 0;
        }

        void paintEvent(QPaintEvent*) {}

    signals:
        // Events
        void mousePressed(QMouseEvent * e);
        void mouseReleased(QMouseEvent * e);
        void mouseMoved(QMouseEvent * e);
        void keyPressed(QKeyEvent *e);
        void keyReleased(QKeyEvent *e);
        void entered(QEvent * event);
        void leaved(QEvent * event);
        void stepped();

    protected:

        // Ogre
        Ogre::Root *mOgreRoot;
        Ogre::RenderWindow *mOgreWindow;
        Ogre::Camera *mCamera;
        Ogre::Viewport *mViewport;
        Ogre::SceneManager *mSceneMgr;

        bool mIsInit;
        static int ogrewidgetCpt;

        // Events
        void mousePressEvent(QMouseEvent * e);
        void mouseReleaseEvent(QMouseEvent * e);
        void mouseMoveEvent(QMouseEvent * e);
        void keyPressEvent(QKeyEvent *e);
        void keyReleaseEvent(QKeyEvent *e);
        void enterEvent(QEvent * event);
        void leaveEvent(QEvent * event);

    private:

        OgreFreeCamera *ogreFreeCamera;
    };
}
#endif // OGREWIDGET_H
