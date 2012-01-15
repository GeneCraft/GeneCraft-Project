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


#library related
INCLUDEPATH  += \
    lib/bullet/src


#suppress warning for thoses systems
QMAKE_CXXFLAGS  += -isystemlib/bullet/src

LIBS += -L../src/lib/bullet/lib

LIBS += -lBulletDynamics
LIBS += -lBulletCollision
LIBS += -lLinearMath

SOURCES += \
    genecraft/core/engines/bullet/bulletengine.cpp \
    genecraft/core/engines/bullet/rigidbodyorigin.cpp \
    genecraft/core/engines/bullet/shapes/btshape.cpp \
    genecraft/core/engines/bullet/shapes/btbox.cpp \
    genecraft/core/engines/bullet/shapes/btsphere.cpp \
    genecraft/core/engines/bullet/shapes/btcylinder.cpp \
    genecraft/core/engines/bullet/shapes/btbone.cpp \
    genecraft/core/world/bullet/btworld.cpp \
    genecraft/core/world/bullet/btscene.cpp \
    genecraft/core/world/bullet/btbiome.cpp \
    genecraft/core/factories/bullet/btfactory.cpp \
    genecraft/core/factories/bullet/btworldfactory.cpp \
    genecraft/core/factories/bullet/btshapesfactory.cpp

HEADERS += \
    genecraft/core/engines/bullet/bulletengine.h \
    genecraft/core/engines/bullet/rigidbodyorigin.h \
    genecraft/core/engines/bullet/shapes/btshape.h \
    genecraft/core/engines/bullet/shapes/btbox.h \
    genecraft/core/engines/bullet/shapes/btsphere.h \
    genecraft/core/engines/bullet/shapes/btcylinder.h \
    genecraft/core/engines/bullet/shapes/btbone.h \
    genecraft/core/world/bullet/btworld.h \
    genecraft/core/world/bullet/btscene.h \
    genecraft/core/world/bullet/btbiome.h \
    genecraft/core/factories/bullet/btshapesfactory.h \
    genecraft/core/factories/bullet/btfactory.h \
    genecraft/core/factories/bullet/btworldfactory.h

