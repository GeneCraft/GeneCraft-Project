#-------------------------------------------------
#
# Project created by QtCreator 2011-05-16T17:50:27
#
#-------------------------------------------------

QT       += core gui opengl testlib

TARGET = genelab_global
TEMPLATE = app

# genelab core
INCLUDEPATH += \
    ../genelab/core \
    ../genelab/core/engines \
    ../genelab/core/engines/brains \
    ../genelab/core/engines/bullet \
    ../genelab/core/engines/bullet/shapes \
    ../genelab/core/engines/events \
    ../genelab/core/engines/ogre \
    ../genelab/core/engines/ogre/entities \
    ../genelab/core/engines/bulletogre \
    ../genelab/core/engines/bulletogre/shapes \
    ../genelab/core/engines/entities \
    ../genelab/core/engines/world \
    ../genelab/core/entities \
    ../genelab/core/entities/body \
    ../genelab/core/entities/brain \
    ../genelab/core/entities/sensors \
    ../genelab/core/entities/families \
    ../genelab/core/entities/factories \
    ../genelab/core/entities/ui \
    ../genelab/core/entities/ui/widgets \
    ../genelab/core/entities/ui/utils \
    ../genelab/core/factories \
    ../genelab/core/ui \
    ../genelab/core/ui/widgets \
    ../genelab/core/ui/widgets/entities \
    ../genelab/core/utils

# genelab apps
INCLUDEPATH += \
    ../genelab/apps/genelab \
    ../genelab/apps/genelab/creatureviewer \
    ../genelab/apps/genelab/creatureviewer/inputlisteners \

#library related
INCLUDEPATH  += \
    ../lib/ogre/include/OGRE \
    ../lib/ogre/include/OIS \
    ../lib/ogre/include \
    ../lib/ogre/boost_1_44 \
    ../lib/ogrebullet-build/include/Collisions \
    ../lib/ogrebullet-build/include/Dynamics \
    ../lib/ogrebullet-build/include \
    ../lib/bullet/src \
    ../lib/bullet/Extra/ConvexDecomposition \
    ../lib/qxt/src/core

#CONFIG(Debug) {
    QMAKE_CXXFLAGS  += -isystem../lib/ogre/include/OGRE
    QMAKE_CXXFLAGS  += -isystem../lib/ogre/include/OIS
    QMAKE_CXXFLAGS  += -isystem../lib/ogre/include
    QMAKE_CXXFLAGS  += -isystem../lib/ogre/boost_1_44
    QMAKE_CXXFLAGS  += -isystem../lib/ogrebullet-build/include/Collisions
    QMAKE_CXXFLAGS  += -isystem../lib/ogrebullet-build/include/Dynamics
    QMAKE_CXXFLAGS  += -isystem../lib/ogrebullet-build/include
    QMAKE_CXXFLAGS  += -isystem../lib/bullet/src
    QMAKE_CXXFLAGS  += -isystem../lib/bullet/Extra/ConvexDecomposition
    QMAKE_CXXFLAGS  += -isystem../lib/qxt/src/core
#}

#CONFIG(Debug) {
#    LIBS += -L../lib/ogre/bin/Debug
#    LIBS += -lOgreMain_d -lOIS_d
#}
#CONFIG(Release) {
    LIBS += -L../lib/ogre/bin/Release
    LIBS += -lOgreMain -lOIS
#}

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

SOURCES += \
    ../genelab/core/engines/simulationmanager.cpp \
    ../genelab/core/engines/ogre/ogreengine.cpp \
    ../genelab/core/engines/ogre/entities/ogrefreecamera.cpp \
    ../genelab/core/engines/events/inputlistener.cpp \
    ../genelab/core/engines/events/eventmanager.cpp \
    ../genelab/core/engines/engine.cpp \
    ../genelab/core/engines/bullet/bulletengine.cpp \
    ../genelab/core/engines/brains/brainengine.cpp \
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
    ../genelab/core/factories/ressource.cpp \
    ../genelab/core/factories/neuralnetworkfactory.cpp \
    ../genelab/core/factories/mainfactory.cpp \
    ../genelab/core/factories/jsonloader.cpp \
    ../genelab/core/factories/entityfactory.cpp \
    ../genelab/core/factories/enginefactory.cpp \
    ../genelab/core/ui/widgets/ogrebulletwindows.cpp \
    ../genelab/core/ui/widgets/entities/generic6dofconstraintcontroller.cpp \
    ../genelab/apps/sandbox/entitysandbox/entitysandbox.cpp \
    ../genelab/apps/genelab/creatureviewer/inputlisteners/creatureviewerinputmanager.cpp \
    ../genelab/apps/sandbox/brainsandbox/brainapp.cpp \
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
    ../genelab/core/entities/sensors/accelerometersensor.cpp

HEADERS += \
    ../genelab/core/engines/simulationmanager.h \
    ../genelab/core/engines/ogre/ogreengine.h \
    ../genelab/core/engines/ogre/entities/ogrefreecamera.h \
    ../genelab/core/engines/events/eventmanager.h \
    ../genelab/core/engines/engine.h \
    ../genelab/core/engines/bullet/bulletengine.h \
    ../genelab/core/engines/brains/brainengine.h \
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
    ../genelab/core/factories/ressource.h \
    ../genelab/core/factories/neuralnetworkfactory.h \
    ../genelab/core/factories/jsonloader.h \
    ../genelab/core/factories/entityfactory.h \
    ../genelab/core/factories/enginefactory.h \
    ../genelab/core/factories/mainfactory.h \
    ../genelab/core/ui/widgets/ogrebulletwindows.h \
    ../genelab/core/ui/widgets/entities/generic6dofconstraintcontroller.h \
    ../genelab/apps/sandbox/entitysandbox/entitysandbox.h \
    ../genelab/apps/sandbox/brainsandbox/brainapp.h \
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
    ../genelab/core/entities/sensors/accelerometersensor.h

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
