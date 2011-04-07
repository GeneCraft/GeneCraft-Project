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
INCLUDEPATH += ../physics/
INCLUDEPATH += ..

#library related
QMAKE_CXXFLAGS  += -isystem../lib/ogre/include/OGRE
QMAKE_CXXFLAGS  += -isystem../lib/ogre/include/OIS
QMAKE_CXXFLAGS  += -isystem../lib/ogre/include
QMAKE_CXXFLAGS  += -isystem../lib/ogre/boost_1_44
QMAKE_CXXFLAGS  += -isystem../lib/ogrebullet-build/include/Collisions
QMAKE_CXXFLAGS  += -isystem../lib/ogrebullet-build/include/Dynamics
QMAKE_CXXFLAGS  += -isystem../lib/ogrebullet-build/include
QMAKE_CXXFLAGS  += -isystem../lib/bullet/src
QMAKE_CXXFLAGS  += -isystem../lib/bullet/Extra/ConvexDecomposition
QMAKE_CXXFLAGS  += -isystem../lib/qxt/src/core/


SOURCES += main.cpp\
        ogrebulletwindows.cpp \
    ../graphic/ogrewidget.cpp \
    ../graphic/ogremanager.cpp \
    ../entity/entity.cpp \
    ../world/world.cpp \
    ../graphic/ogrescene.cpp \
    ../physics/bulletmanager.cpp \
    ../physics/bulletscene.cpp \
    ../engine/engine.cpp \
    ../factory/jsonloader.cpp \
    ../factory/mainfactory.cpp \
    ../factory/enginefactory.cpp \
    ../factory/entityfactory.cpp \
    ../factory/worldfactory.cpp \
    ../entity/ogrebulletentity.cpp \
    ../entity/entityfamily.cpp \
    ../entity/ogrebulletentityfamily.cpp \
    ../entity/struct/treeshape.cpp \
    ../entity/struct/fixation.cpp \
    ../entity/struct/bone.cpp \
    ../entity/sample/snakefamily.cpp \
    ../graphic/ogreinputmanager.cpp \
    ../graphic/ogrefreecamera.cpp \
    generic6dofconstraintcontroller.cpp \
    ../graphic/defaulteventmanager.cpp \
    ../world/ogrebulletscene.cpp \
    ogrebulletsandboxscene.cpp \
    sandboxtools.cpp \
    ../simulation/simulationmanager.cpp \
    ../simulation/ogrebulletsimulationmanager.cpp

HEADERS  += ogrebulletwindows.h \
    ../graphic/ogrewidget.h \
    ../graphic/ogremanager.h \
    ../classes.h \
    ../entity/entity.h \
    ../world/world.h \
    ../graphic/ogrescene.h \
    ../physics/bulletmanager.h \
    ../physics/bulletscene.h \
    ../engine/engine.h \
    ../factory/jsonloader.h \
    ../factory/mainfactory.h \
    ../factory/enginefactory.h \
    ../factory/entityfactory.h \
    ../factory/worldfactory.h \
    ../entity/ogrebulletentity.h \
    ../entity/entityfamily.h \
    ../entity/ogrebulletentityfamily.h \
    ../entity/struct/types.h \
    ../entity/struct/treeshape.h \
    ../entity/struct/fixation.h \
    ../entity/struct/bone.h \
    ../entity/sample/snakefamily.h \
    ../graphic/ogreinputmanager.h \
    ../graphic/ogrefreecamera.h \
    generic6dofconstraintcontroller.h \
    ../graphic/defaulteventmanager.h \
    ../world/ogrebulletscene.h \
    ogrebulletsandboxscene.h \
    sandboxtools.h \
    ../simulation/simulationmanager.h \
    ../simulation/ogrebulletsimulationmanager.h

FORMS    += ogrebulletwindows.ui \
    generic6dofconstraintcontroller.ui


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
LIBS += -L../lib/qxt/lib

LIBS += -lQxtCore
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
