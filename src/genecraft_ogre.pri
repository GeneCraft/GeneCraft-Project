# genecraft core
INCLUDEPATH += \
    genecraft/core \
    genecraft/core/engines \
    genecraft/core/factories/bulletogre \
    genecraft/core/ui \
    genecraft/core/world/bulletogre \
    genecraft/core/utils

INCLUDEPATH += lib/ogre/include/OGRE \
               lib/ogre/include \
               lib/ogre/boost_1_44 # for win32
               #../lib/ogre/boost_1_46_1/ # for macos

#suppress warning from libs
QMAKE_CXXFLAGS  += -isystem../src/lib/ogre/boost_1_44/  # boost_1_44 for win32
QMAKE_CXXFLAGS  += -isystem../src/lib/ogre/include
QMAKE_CXXFLAGS  += -isystem../src/lib/ogre/include/OGRE

win32 {

    LIBS += -L../src/lib/ogre/bin/Release
    LIBS += -lOgreMain
}

macx {
    LIBS += -L../src/lib/ogre/lib
    LIBS += -F../src/lib/ogre/lib/release/
    LIBS += -framework Ogre
}

SOURCES += \
    genecraft/core/engines/simulationmanager.cpp \
    genecraft/core/engines/events/inspectorsinputmanager.cpp \
    genecraft/core/engines/events/inputlistener.cpp \
    genecraft/core/engines/events/eventsmanager.cpp \
    genecraft/core/engines/bulletogre/shapes/btobox.cpp \
    genecraft/core/engines/bulletogre/shapes/btosphere.cpp \
    genecraft/core/engines/bulletogre/bulletogreengine.cpp \
    genecraft/core/engines/bulletogre/shapes/btocylinder.cpp \
    genecraft/core/engines/bulletogre/shapes/btobone.cpp \
    genecraft/core/engines/ogre/ogrewidget.cpp \
    genecraft/core/engines/ogre/ogreengine.cpp \
    genecraft/core/engines/ogre/entities/ogrefreecamera.cpp \
    genecraft/core/world/bulletogre/btoworld.cpp \
    genecraft/core/world/bulletogre/btoscene.cpp \
    genecraft/core/world/bulletogre/btobiome.cpp \
    genecraft/core/factories/bulletogre/btofactory.cpp \
    genecraft/core/factories/bulletogre/btoworldfactory.cpp \
    genecraft/core/factories/bulletogre/btoshapesfactory.cpp \
    genecraft/core/ui/widgets/ogrebulletwindows.cpp

HEADERS += \
    genecraft/core/engines/simulationmanager.h \
    genecraft/core/engines/events/eventsmanager.h \
    genecraft/core/engines/events/inspectorsinputmanager.h \
    genecraft/core/engines/events/inputlistener.h \
    genecraft/core/engines/bulletogre/shapes/btobox.h \
    genecraft/core/engines/bulletogre/shapes/btosphere.h \
    genecraft/core/engines/bulletogre/bulletogreengine.h \
    genecraft/core/engines/bulletogre/shapes/btocylinder.h \
    genecraft/core/engines/bulletogre/shapes/btobone.h \
    genecraft/core/engines/ogre/ogreengine.h \
    genecraft/core/engines/ogre/entities/ogrefreecamera.h \
    genecraft/core/engines/ogre/ogrewidget.h \
    genecraft/core/factories/bulletogre/btoshapesfactory.h \
    genecraft/core/factories/bulletogre/btofactory.h \
    genecraft/core/factories/bulletogre/btoworldfactory.h \
    genecraft/core/world/bulletogre/btoworld.h \
    genecraft/core/world/bulletogre/btoscene.h \
    genecraft/core/world/bulletogre/btobiome.h \
    genecraft/core/ui/widgets/ogrebulletwindows.h

FORMS += \
    genecraft/core/ui/widgets/ogrebulletwindows.ui
