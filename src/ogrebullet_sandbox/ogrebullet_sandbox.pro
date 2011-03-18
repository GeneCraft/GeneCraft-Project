#-------------------------------------------------
#
# Project created by QtCreator 2011-03-17T09:54:00
#
#-------------------------------------------------

QT       += core gui opengl testlib

TARGET = ogrebullet_sandbox
TEMPLATE = app

#genelab
INCLUDEPATH += ../entity/
INCLUDEPATH += ../graphic/
INCLUDEPATH += ..
#library related
INCLUDEPATH += ../lib/ogre/include/OGRE
INCLUDEPATH += ../lib/ogre/include/OIS
INCLUDEPATH += ../lib/ogre/include
INCLUDEPATH += ../lib/ogre/boost_1_44
INCLUDEPATH += ../lib/ogrebullet-build/include/Collisions
INCLUDEPATH += ../lib/ogrebullet-build/include/Dynamics
INCLUDEPATH += ../lib/ogrebullet-build/include
INCLUDEPATH += ../lib/bullet/src
INCLUDEPATH += ../lib/bullet/Extra/ConvexDecomposition


SOURCES += main.cpp\
        ogrebulletwindows.cpp \
    ../graphic/ogrewidget.cpp \
    ../graphic/ogremanager.cpp \
    ../graphic/scenemanager.cpp \
    ../graphic/ninjascene.cpp \
    ../physics/ogrebulletmanager.cpp

HEADERS  += ogrebulletwindows.h \
    ../graphic/ogrewidget.h \
    ../graphic/ogremanager.h \
    ../graphic/scenemanager.h \
    ../graphic/ninjascene.h \
    ../physics/ogrebulletmanager.h

FORMS    += ogrebulletwindows.ui


CONFIG(Debug) {
    LIBS += -L../lib/ogre/bin/debug
    LIBS += -lOgreMain_d -lOIS_d
}
CONFIG(Release) {
    LIBS += -L../lib/ogre/bin/release
    LIBS += -lOgreMain -lOIS
}

LIBS += -L../lib/ogrebullet-build/lib
LIBS += -L../lib/bullet/lib

LIBS += -lOgreBulletCol
LIBS += -lOgreBulletDyn
LIBS += -lBulletDynamics
LIBS += -lBulletCollision
LIBS += -lLinearMath
LIBS += -lConvexDecomposition
LIBS += -lBulletWorldImporter
LIBS += -lBulletFileLoader
LIBS += -lBulletMultiThreaded
LIBS += -lBulletSoftBody
#LIBS += -lGIMPACTUtils
#LIBS += -lgle
#LIBS += -lglsmap
#LIBS += -lglut32
#LIBS += -lGLUI
#LIBS += -lMiniCL
#LIBS += -lmui
#LIBS += -lOpenGLSupport
