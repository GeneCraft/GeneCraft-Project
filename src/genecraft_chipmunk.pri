#Copyright 2011, 2012 Aurélien Da Campo, Cyprien Huissoud
#
#This file is part of Genecraft-Project.
#
#Genecraft-Project is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#Genecraft-Project is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with Genecraft-Project.  If not, see <http://www.gnu.org/licenses/>.

# genecraft core
INCLUDEPATH += \
    genecraft/core \
    genecraft/core/engines \
    genecraft/core/entities \
    genecraft/core/experiment \
    genecraft/core/factories/bullet \
    genecraft/core/world/bullet \
    genecraft/core/utils


DEFINES += "M_PI_2=M_PI/2"

INCLUDEPATH += ../../lib/chipmunk/include/chipmunk

LIBS += -L../../lib/chipmunk/ -lchipmunk


#QMAKE_CFLAGS += -std=c99

#suppress warning for thoses systems
QMAKE_CXXFLAGS  += -isystemlib/bullet/src


SOURCES += \
    genecraft/core/engines/chipmunk/rigidbodyorigin.cpp \
    genecraft/core/engines/chipmunk/shapes/btshape.cpp \
    genecraft/core/engines/chipmunk/shapes/btbox.cpp \
    genecraft/core/engines/chipmunk/shapes/btsphere.cpp \
    genecraft/core/engines/chipmunk/shapes/btcylinder.cpp \
    genecraft/core/engines/chipmunk/shapes/btbone.cpp \
    genecraft/core/world/chipmunk/btworld.cpp \
    genecraft/core/world/chipmunk/btscene.cpp \
    genecraft/core/world/chipmunk/btbiome.cpp \
    genecraft/core/factories/chipmunk/btfactory.cpp \
    genecraft/core/factories/chipmunk/btworldfactory.cpp \
    genecraft/core/factories/chipmunk/btshapesfactory.cpp \
    genecraft/core/engines/chipmunk/chipmunkengine.cpp

HEADERS += \
    genecraft/core/engines/chipmunk/rigidbodyorigin.h \
    genecraft/core/world/chipmunk/btworld.h \
    genecraft/core/world/chipmunk/btscene.h \
    genecraft/core/world/chipmunk/btbiome.h \
    genecraft/core/factories/chipmunk/btshapesfactory.h \
    genecraft/core/factories/chipmunk/btfactory.h \
    genecraft/core/factories/chipmunk/btworldfactory.h \
    genecraft/core/engines/chipmunk/chipmunkengine.h \
    genecraft/core/engines/chipmunk/shapes/cmbone.h \
    genecraft/core/engines/chipmunk/shapes/cmbox.h \
    genecraft/core/engines/chipmunk/shapes/cmcylinder.h \
    genecraft/core/engines/chipmunk/shapes/cmshape.h \
    genecraft/core/engines/chipmunk/shapes/cmsphere.h















