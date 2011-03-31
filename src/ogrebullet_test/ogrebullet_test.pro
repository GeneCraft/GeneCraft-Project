#-------------------------------------------------
#
# Project created by QtCreator 2011-03-10T16:39:17
#
#-------------------------------------------------

QT       += core gui testlib opengl

TARGET = ogrebullet_test

INCLUDEPATH += ../lib/ogre/include/OGRE
INCLUDEPATH += ../lib/ogre/include/OIS
INCLUDEPATH += ../lib/ogre/include
INCLUDEPATH += ../lib/ogre/boost_1_44
INCLUDEPATH += ../lib/ogrebullet-build/include/Collisions
INCLUDEPATH += ../lib/ogrebullet-build/include/Dynamics
INCLUDEPATH += ../lib/ogrebullet-build/include
INCLUDEPATH += ../lib/bullet/src
INCLUDEPATH += ../lib/bullet/Extra/ConvexDecomposition

SOURCES += \
    OgreBulletListener.cpp \
    OgreBulletInputListener.cpp \
    OgreBulletGuiListener.cpp \
    OgreBulletApplication.cpp \
    BetaGUI.cpp \
    Primitives_Demo.cpp \
    TriMesh_Demo.cpp \
    Vehicle_Demo.cpp \
    main.cpp \
    Ragdoll_Demo.cpp \
    Terrain_Demo.cpp \
    Constraints_Demo.cpp

HEADERS  += \
    OgreBulletListener.h \
    OgreBulletInputListener.h \
    OgreBulletGuiListener.h \
    OgreBulletApplication.h \
    exampleframelistener.h \
    ExampleApplication.h \
    BetaGUI.h \
    Constraints_Demo.h \
    Primitives_Demo.h \
    TriMesh_Demo.h \
    Vehicle_Demo.h \
    Ragdoll_Demo.h \
    Terrain_Demo.h \
    Snake.h

FORMS    +=

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

LIBS += -lOgreBulletCol -lOgreBulletDyn
LIBS += -lBulletDynamics
LIBS += -lBulletCollision
LIBS += -lLinearMath
LIBS += -lConvexDecomposition
LIBS += -lBulletWorldImporter -lBulletFileLoader
LIBS += -lBulletMultiThreaded
LIBS += -lBulletSoftBody
LIBS += -lGIMPACTUtils
#LIBS += -lgle
#LIBS += -lglsmap
#LIBS += -lglut32
LIBS += -lGLUI
LIBS += -lMiniCL
#LIBS += -lmui
LIBS += -lOpenGLSupport
