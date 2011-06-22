#-------------------------------------------------
#
# Project created by QtCreator 2011-05-16T17:50:27
#
#-------------------------------------------------

QT       += core gui opengl testlib network
TARGET = genelab_global
TEMPLATE = app

# genelab core
INCLUDEPATH += \
    ../genelab/core \
    ../genelab/core/engines \
    ../genelab/core/entities \
    ../genelab/core/entities/ui \
    ../genelab/core/factories \
    ../genelab/core/ui \
    ../genelab/core/utils

# genelab apps
INCLUDEPATH += \
    ../genelab/apps/genelab \
    ../genelab/apps/genelab/creatureviewer \
    ../genelab/apps/genelab/creatureviewer/inputlisteners \


#library related
INCLUDEPATH  += \
    ../lib/ogre/boost_1_44 \
    ../lib/bullet/src \
    ../lib/bullet/Extra/ConvexDecomposition \
    ../lib/qxt/src/core \
    ../lib/qwt/src

 win32 {
    INCLUDEPATH += ../lib/ogre/include/OGRE \
                   ../lib/ogre/include/OIS \
                   ../lib/ogre/include


    QMAKE_CXXFLAGS  += -isystem../lib/ogre/include/OGRE
    QMAKE_CXXFLAGS  += -isystem../lib/ogre/include/OIS
 }
 unix {
    INCLUDEPATH += ../lib/ogre/Dependencies/include \
    /Users/cyprienhuissoud/Downloads/ogre_src_v1-7-3/OgreMain/include \
    /Users/cyprienhuissoud/Downloads/ogre_src_v1-7-3/build/lib/RelWithDebInfo/Ogre.framework/Headers

    QMAKE_CXXFLAGS  += -isystem../lib/ogre/Dependencies/include
    QMAKE_CXXFLAGS  += -isystem/Users/cyprienhuissoud/Downloads/ogre_src_v1-7-3/build/lib/RelWithDebInfo/Ogre.framework/Headers
    QMAKE_CXXFLAGS  += -isystem/Users/cyprienhuissoud/Downloads/ogre_src_v1-7-3/OgreMain/include
 }

QMAKE_CXXFLAGS  += -isystem../lib/ogre/include
QMAKE_CXXFLAGS  += -isystem../lib/ogre/boost_1_44
QMAKE_CXXFLAGS  += -isystem../lib/bullet/src
QMAKE_CXXFLAGS  += -isystem../lib/bullet/Extra/ConvexDecomposition
QMAKE_CXXFLAGS  += -isystem../lib/qxt/src/core
QMAKE_CXXFLAGS  += -isystem../lib/qwt/src

win32 {
    LIBS += -L../lib/bullet/lib
    LIBS += -L../lib/qxt/lib
    LIBS += -L../lib/ogre/bin/Release
    LIBS += -lQxtCore
    LIBS += -lOgreMain -lOIS
}

unix {
    LIBS += -L/Users/cyprienhuissoud/Downloads/Dependencies/bin/Release
    LIBS += -F/Users/cyprienhuissoud/Downloads/ogre_src_v1-7-3/build/lib/RelWithDebInfo
    LIBS += -framework Ogre
    LIBS += -framework QxtCore
    LIBS += -lzzip
    LIBS += -lfreetype
    LIBS += -lfreeimage
    LIBS += -lOIS
}

LIBS += -lBulletDynamics
LIBS += -lBulletCollision
LIBS += -lLinearMath
#LIBS += -lConvexDecomposition
#LIBS += -lBulletWorldImporter -lBulletFileLoader
LIBS += -lBulletMultiThreaded
LIBS += -lBulletSoftBody
#LIBS += -lGIMPACTUtils
#LIBS += -lgle
#LIBS += -lglsmap
#LIBS += -lglut32
#LIBS += -lGLUI
LIBS += -lMiniCL
#LIBS += -lmui
#LIBS += -lOpenGLSupport

SOURCES += \
    ../genelab/core/engines/simulationmanager.cpp \
    ../genelab/core/engines/ogre/ogreengine.cpp \
    ../genelab/core/engines/ogre/entities/ogrefreecamera.cpp \
    ../genelab/core/engines/events/inputlistener.cpp \
    ../genelab/core/engines/engine.cpp \
    ../genelab/core/engines/bullet/bulletengine.cpp \
    ../genelab/core/engines/ogre/ogrewidget.cpp \
    ../genelab/core/entities/body/treeshape.cpp \
    ../genelab/core/entities/brain/synapse.cpp \
    ../genelab/core/entities/families/snakefamily.cpp \
    ../genelab/core/entities/brain/sinusin.cpp \
    ../genelab/core/entities/body/fixation.cpp \
    ../genelab/core/entities/entityfamily.cpp \
    ../genelab/core/entities/entity.cpp \
    ../genelab/core/entities/body/bone.cpp \
    ../genelab/core/factories/worldfactory.cpp \
    ../genelab/core/factories/ressources/ressource.cpp \
    ../genelab/core/factories/mainfactory.cpp \
    ../genelab/core/ui/widgets/ogrebulletwindows.cpp \
    ../genelab/core/ui/widgets/entities/generic6dofconstraintcontroller.cpp \
    ../genelab/apps/sandbox/entitysandbox/entitysandbox.cpp \
    ../genelab/apps/genelab/creatureviewer/inputlisteners/creatureviewerinputmanager.cpp \
    ../genelab/core/engines/world/world.cpp \
    ../genelab/core/engines/world/ogrebulletworld.cpp \
    main.cpp \
    ../genelab/core/engines/bullet/rigidbodyorigin.cpp \
    ../genelab/core/ui/widgets/entities/fixationproperties.cpp \
    ../genelab/core/ui/widgets/entities/bonepropertiescontroller.cpp \
    ../genelab/core/utils/tools.cpp \
    ../genelab/core/engines/bullet/shapes/btshape.cpp \
    ../genelab/core/engines/bullet/shapes/btbox.cpp \
    ../genelab/core/engines/bullet/shapes/btsphere.cpp \
    ../genelab/core/engines/bulletogre/shapes/btobox.cpp \
    ../genelab/core/engines/bulletogre/shapes/btosphere.cpp \
    ../genelab/core/engines/bulletogre/bulletogreengine.cpp \
    ../genelab/core/engines/bullet/shapes/btcylinder.cpp \
    ../genelab/core/engines/bulletogre/shapes/btocylinder.cpp \
    ../genelab/core/factories/btshapesfactory.cpp \
    ../genelab/core/factories/btoshapesfactory.cpp \
    ../genelab/core/entities/families/spider/spider.cpp \
    ../genelab/core/ui/widgets/entities/entitypropertiescontroller.cpp \
    ../genelab/apps/genelab/creatureviewer/ui/creatureviewerwindow.cpp \
    ../genelab/core/engines/bullet/shapes/btbone.cpp \
    ../genelab/core/engines/bulletogre/shapes/btobone.cpp \
    ../genelab/core/entities/brain/brainpluggrid.cpp \
    ../genelab/core/entities/brain/brainnode.cpp \
    ../genelab/core/entities/brain/brain.cpp \
    ../genelab/core/entities/brain/brainfunctional.cpp \
    ../genelab/core/entities/brain/brainin.cpp \
    ../genelab/core/entities/brain/brainout.cpp \
    ../genelab/core/ui/widgets/entities/pluggridvisualizer.cpp \
    ../genelab/apps/genelab/creatureviewer/ui/creatureviewerabout.cpp \
    ../genelab/core/entities/sensors/sensor.cpp \
    ../genelab/core/entities/sensors/positionsensor.cpp \
    ../genelab/core/engines/entities/entitiesengine.cpp \
    ../genelab/core/entities/sensors/gyroscopicsensor.cpp \
    ../genelab/core/entities/sensors/accelerometersensor.cpp \
    ../genelab/core/entities/modifiers/modifier.cpp \
    ../genelab/core/entities/modifiers/rotationalmotorsmodifier.cpp \
    ../genelab/core/factories/ressources/jsonfile.cpp \
    ../genelab/core/factories/ressources/dbrecord.cpp \
    ../genelab/core/entities/families/ant/ant.cpp \
    ../genelab/core/entities/families/genericfamily.cpp \
    ../genelab/core/ui/widgets/entities/pluggriddesignvisualizer.cpp \
    ../genelab/core/world/btworld.cpp \
    ../genelab/core/world/btscene.cpp \
    ../genelab/core/world/btbiome.cpp \
    ../genelab/core/world/btoworld.cpp \
    ../genelab/core/world/btoscene.cpp \
    ../genelab/core/world/btobiome.cpp \
    ../genelab/core/engines/events/eventsmanager.cpp

HEADERS += \
    ../genelab/core/engines/simulationmanager.h \
    ../genelab/core/engines/ogre/ogreengine.h \
    ../genelab/core/engines/ogre/entities/ogrefreecamera.h \
    ../genelab/core/engines/engine.h \
    ../genelab/core/engines/bullet/bulletengine.h \
    ../genelab/core/engines/ogre/ogrewidget.h \
    ../genelab/core/engines/events/inputlistener.h \
    ../genelab/core/entities/body/treeshape.h \
    ../genelab/core/entities/brain/synapse.h \
    ../genelab/core/entities/families/snakefamily.h \
    ../genelab/core/entities/brain/sinusin.h \
    ../genelab/core/entities/body/fixation.h \
    ../genelab/core/entities/entityfamily.h \
    ../genelab/core/entities/entity.h \
    ../genelab/core/entities/body/bone.h \
    ../genelab/core/factories/worldfactory.h \
    ../genelab/core/factories/ressources/ressource.h \
    ../genelab/core/factories/mainfactory.h \
    ../genelab/core/ui/widgets/ogrebulletwindows.h \
    ../genelab/core/ui/widgets/entities/generic6dofconstraintcontroller.h \
    ../genelab/apps/sandbox/entitysandbox/entitysandbox.h \
    ../genelab/apps/genelab/creatureviewer/inputlisteners/creatureviewerinputmanager.h \
    ../genelab/core/engines/world/world.h \
    ../genelab/core/engines/world/ogrebulletworld.h \
    ../genelab/core/genelabcoreclasses.h \
    ../genelab/core/engines/bullet/rigidbodyorigin.h \
    ../genelab/core/ui/widgets/entities/fixationproperties.h \
    ../genelab/core/ui/widgets/entities/bonepropertiescontroller.h \
    ../genelab/core/utils/tools.h \
    ../genelab/core/engines/bullet/shapes/btshape.h \
    ../genelab/core/engines/bullet/shapes/btbox.h \
    ../genelab/core/engines/bullet/shapes/btsphere.h \
    ../genelab/core/engines/bulletogre/shapes/btobox.h \
    ../genelab/core/engines/bulletogre/shapes/btosphere.h \
    ../genelab/core/engines/bulletogre/bulletogreengine.h \
    ../genelab/core/engines/bullet/shapes/btcylinder.h \
    ../genelab/core/engines/bulletogre/shapes/btocylinder.h \
    ../genelab/core/factories/btshapesfactory.h \
    ../genelab/core/factories/btoshapesfactory.h \
    ../genelab/core/entities/families/spider/spider.h \
    ../genelab/core/ui/widgets/entities/entitypropertiescontroller.h \
    ../genelab/apps/genelab/creatureviewer/ui/creatureviewerwindow.h \
    ../genelab/core/engines/bullet/shapes/btbone.h \
    ../genelab/core/engines/bulletogre/shapes/btobone.h \
    ../genelab/core/entities/brain/brainpluggrid.h \
    ../genelab/core/entities/brain/brainnode.h \
    ../genelab/core/entities/brain/brain.h \
    ../genelab/core/entities/brain/brainfunctional.h \
    ../genelab/core/entities/brain/brainin.h \
    ../genelab/core/entities/brain/brainout.h \
    ../genelab/core/ui/widgets/entities/pluggridvisualizer.h \
    ../genelab/apps/genelab/creatureviewer/ui/creatureviewerabout.h \
    ../genelab/core/entities/sensors/sensor.h \
    ../genelab/core/entities/sensors/positionsensor.h \
    ../genelab/core/engines/entities/entitiesengine.h \
    ../genelab/core/entities/sensors/gyroscopicsensor.h \
    ../genelab/core/entities/sensors/accelerometersensor.h \
    ../genelab/core/entities/modifiers/modifier.h \
    ../genelab/core/entities/modifiers/rotationalmotorsmodifier.h \
    ../genelab/core/factories/ressources/jsonfile.h \
    ../genelab/core/factories/ressources/dbrecord.h \
    ../genelab/core/entities/families/ant/ant.h \
    ../genelab/core/entities/families/genericfamily.h \
    ../genelab/core/ui/widgets/entities/pluggriddesignvisualizer.h \
    ../genelab/core/ui/widgets/entities/bodyitems.h \
    ../genelab/core/world/btworld.h \
    ../genelab/core/world/btscene.h \
    ../genelab/core/world/btbiome.h \
    ../genelab/core/world/btoworld.h \
    ../genelab/core/world/btoscene.h \
    ../genelab/core/world/btobiome.h \
    ../genelab/core/engines/events/eventsmanager.h

FORMS += \
    ../genelab/core/ui/widgets/ogrebulletwindows.ui \
    ../genelab/core/ui/widgets/entities/generic6dofconstraintcontroller.ui \
    ../genelab/apps/sandbox/entitysandbox/entitysandbox.ui \
    ../genelab/apps/sandbox/brainsandbox/brainapp.ui \
    ../genelab/core/ui/widgets/entities/fixationproperties.ui \
    ../genelab/core/ui/widgets/entities/bonepropertiescontroller.ui \
    ../genelab/core/ui/widgets/entities/entitypropertiescontroller.ui \
    ../genelab/apps/genelab/creatureviewer/ui/creatureviewerwindow.ui \
    ../genelab/apps/genelab/creatureviewer/ui/creatureviewerabout.ui

RESOURCES += \
    ../genelab/core/ressources/ressources.qrc
