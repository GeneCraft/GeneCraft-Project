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
INCLUDEPATH += ../lib/qxt/src/core/


SOURCES += main.cpp\
        ogrebulletwindows.cpp \
    ../graphic/ogrewidget.cpp \
    ../graphic/ogremanager.cpp \
    ../entity/entity.cpp \
    ../world/world.cpp \
    ../graphic/ogrescene.cpp \
    ../physics/bulletmanager.cpp \
    ../world/ogrebulletworld.cpp \
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
    generic6dofconstraintcontroller.cpp

HEADERS  += ogrebulletwindows.h \
    ../graphic/ogrewidget.h \
    ../graphic/ogremanager.h \
    ../classes.h \
    ../entity/entity.h \
    ../world/world.h \
    ../graphic/ogrescene.h \
    ../physics/bulletmanager.h \
    ../world/ogrebulletworld.h \
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
    generic6dofconstraintcontroller.h

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
