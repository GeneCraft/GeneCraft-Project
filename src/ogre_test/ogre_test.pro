#-------------------------------------------------
#
# Project created by QtCreator 2011-03-10T16:39:17
#
#-------------------------------------------------

QT       += core gui testlib opengl

TARGET = ogre_test

INCLUDEPATH += ../lib/ogre/include/OGRE
INCLUDEPATH += ../lib/ogre/include/OIS
INCLUDEPATH += ../lib/ogre/boost_1_44
INCLUDEPATH += ../lib/ogrebullet-build/include
INCLUDEPATH += ../lib/bullet/src
INCLUDEPATH += ../lib/bullet/Extra

SOURCES +=\
    TutorialApplication.cpp \
    BaseApplication.cpp

HEADERS  += \
    TutorialApplication.h \
    BaseApplication.h

FORMS    +=

CONFIG(Debug) {
    LIBS += -L../lib/ogre/bin/debug
    LIBS += -lOgreMain_d -lOIS_d
}
CONFIG(Release) {
    LIBS += -L../lib/ogre/bin/release
    LIBS += -L../lib/ogrebullet-build/lib
    LIBS += -lOgreMain -lOIS -lOgreBulletDyn -lOgreBulletCol
}
