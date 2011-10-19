# genecraft core
INCLUDEPATH += \
    genecraft/core \
    genecraft/core/engines \
    genecraft/core/factories \
    genecraft/core/ui \
    genecraft/core/world \
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
    genecraft/core/world/btoworld.cpp \
    genecraft/core/world/btoscene.cpp \
    genecraft/core/world/btobiome.cpp \
    genecraft/core/factories/btofactory.cpp \
    genecraft/core/factories/btoworldfactory.cpp \
    genecraft/core/factories/btoshapesfactory.cpp \
    genecraft/core/ui/widgets/entities/brainpropertiescontroller.cpp \
    genecraft/core/ui/widgets/entities/statisticspropertiescontroller.cpp \
    genecraft/core/ui/widgets/entities/fixationpropertiescontroller.cpp \
    genecraft/core/ui/widgets/experiments/experimentspropertiescontroller.cpp \
    genecraft/core/ui/widgets/experiments/floatmutationcontroller.cpp \
    genecraft/core/ui/widgets/experiments/integermutationcontroller.cpp \
    genecraft/core/ui/widgets/experiments/simpleprobabilitycontroller.cpp \
    genecraft/core/ui/widgets/experiments/structuralmutationcontroller.cpp \
    genecraft/core/ui/widgets/experiments/mutationelementcontroller.cpp \
    genecraft/core/ui/widgets/experiments/workerctrl.cpp \
    genecraft/core/ui/widgets/experiments/ressourcesbrowser.cpp \
    genecraft/core/ui/widgets/experiments/experimentctrl.cpp \
    genecraft/core/ui/widgets/ogrebulletwindows.cpp \
    genecraft/core/ui/widgets/entities/generic6dofconstraintcontroller.cpp \
    genecraft/core/ui/widgets/entities/bonepropertiescontroller.cpp \
    genecraft/core/ui/widgets/entities/pluggridvisualizer.cpp \
    genecraft/core/ui/widgets/entities/entitypropertiescontroller.cpp \
    genecraft/core/ui/widgets/entities/pluggriddesignvisualizer.cpp \
    genecraft/core/ui/widgets/experiments/conversionctrl.cpp \
    genecraft/core/ui/widgets/plot/fitnessplot.cpp \
    genecraft/core/ui/widgets/experiments/floordialog.cpp \
    genecraft/core/utils/uitools.cpp

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
    genecraft/core/factories/btoshapesfactory.h \
    genecraft/core/factories/btofactory.h \
    genecraft/core/factories/btoworldfactory.h \
    genecraft/core/world/btoworld.h \
    genecraft/core/world/btoscene.h \
    genecraft/core/world/btobiome.h \
    genecraft/core/ui/widgets/experiments/structuralmutationcontroller.h \
    genecraft/core/ui/widgets/experiments/mutationelementcontroller.h \
    genecraft/core/ui/widgets/experiments/workerctrl.h \
    genecraft/core/ui/widgets/experiments/ressourcesbrowser.h \
    genecraft/core/ui/widgets/experiments/ressourcesItems.h \
    genecraft/core/ui/widgets/experiments/experimentctrl.h \
    genecraft/core/ui/widgets/experiments/experimentspropertiescontroller.h \
    genecraft/core/ui/widgets/experiments/floatmutationcontroller.h \
    genecraft/core/ui/widgets/experiments/integermutationcontroller.h \
    genecraft/core/ui/widgets/experiments/simpleprobabilitycontroller.h \
    genecraft/core/ui/widgets/entities/brainpropertiescontroller.h \
    genecraft/core/ui/widgets/entities/statisticspropertiescontroller.h \
    genecraft/core/ui/widgets/entities/fixationpropertiescontroller.h \
    genecraft/core/ui/widgets/entities/pluggriddesignvisualizer.h \
    genecraft/core/ui/widgets/entities/bodyitems.h \
    genecraft/core/ui/widgets/entities/entitypropertiescontroller.h \
    genecraft/core/ui/widgets/entities/pluggridvisualizer.h \
    genecraft/core/ui/widgets/entities/bonepropertiescontroller.h \
    genecraft/core/ui/widgets/entities/generic6dofconstraintcontroller.h \
    genecraft/core/ui/widgets/ogrebulletwindows.h \
    genecraft/core/ui/widgets/experiments/conversionctrl.h \
    genecraft/core/ui/widgets/plot/fitnessplot.h \
    genecraft/core/ui/widgets/experiments/floordialog.h \
    genecraft/core/utils/uitools.h

FORMS += \
    genecraft/core/ui/widgets/ogrebulletwindows.ui \
    genecraft/core/ui/widgets/entities/generic6dofconstraintcontroller.ui \
    genecraft/core/ui/widgets/entities/bonepropertiescontroller.ui \
    genecraft/core/ui/widgets/entities/entitypropertiescontroller.ui \
    genecraft/core/ui/widgets/entities/brainpropertiescontroller.ui \
    genecraft/core/ui/widgets/entities/statisticspropertiescontroller.ui \
    genecraft/core/ui/widgets/entities/fixationpropertiescontroller.ui \
    genecraft/core/ui/widgets/experiments/experimentspropertiescontroller.ui \
    genecraft/core/ui/widgets/experiments/floatmutationcontroller.ui \
    genecraft/core/ui/widgets/experiments/integermutationcontroller.ui \
    genecraft/core/ui/widgets/experiments/simpleprobabilitycontroller.ui \
    genecraft/core/ui/widgets/experiments/structuralmutationcontroller.ui \
    genecraft/core/ui/widgets/experiments/mutationelementcontroller.ui \
    genecraft/core/ui/widgets/experiments/workerctrl.ui \
    genecraft/core/ui/widgets/experiments/ressourcesbrowser.ui \
    genecraft/core/ui/widgets/experiments/experimentctrl.ui \
    genecraft/core/ui/widgets/experiments/conversionctrl.ui \
    genecraft/core/ui/widgets/experiments/floordialog.ui

RESOURCES += \
    genecraft/core/ressources/ressources.qrc
