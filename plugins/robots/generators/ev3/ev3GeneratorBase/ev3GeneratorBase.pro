# Copyright 2007-2015 QReal Research Group
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

TARGET = robots-ev3-generator-base

include(../../../../../global.pri)

QT += widgets

TEMPLATE = lib
CONFIG += plugin

includes(plugins/robots/generators/ev3/ev3GeneratorBase \
		plugins/robots/generators/generatorBase \
		plugins/robots/common/kitBase \
		plugins/robots/common/ev3Kit \
		plugins/robots/utils \
		qrtext \
)

links(qrkernel qslog qrutils qrrepo robots-generator-base robots-ev3-kit robots-kit-base)

DEFINES += ROBOTS_EV3_GENERATOR_BASE_LIBRARY

TRANSLATIONS = $$PWD/../../../../../qrtranslations/ru/plugins/robots/ev3GeneratorBase_ru.ts

#QT += widgets

#CONFIG += c++11

#include(../../../../../global.pri)

#TEMPLATE = lib
#CONFIG += plugin

#DESTDIR = $$PWD/../../../../../bin/
#TARGET = robots-ev3-generator-base

#MOC_DIR = .moc
#RCC_DIR = .moc
#OBJECTS_DIR = .obj

#LIBS += -L$$PWD/../../../../../bin -lqrkernel -lqslog -lqrutils -lqrrepo \
#		-lrobots-generator-base -lrobots-interpreter-base \

#DEFINES += ROBOTS_EV3_GENERATOR_BASE_LIBRARY

#INCLUDEPATH += \
#	$$PWD/include \
#	$$PWD/../../generatorBase/include/ \
#	$$PWD/../../../interpreters/interpreterBase/include \
#	$$PWD/../../../../../ \
#	$$PWD/../../../../../qrgui \
#	$$PWD/../../../../../qrtext/include \

## workaround for http://bugreports.qt.nokia.com/browse/QTBUG-8110
## when fixed it would become possible to use QMAKE_LFLAGS_RPATH
#!macx {
#	QMAKE_LFLAGS += -Wl,-O1,-rpath,$$PWD/../../../../../bin/
#	QMAKE_LFLAGS += -Wl,-rpath,$$PWD/../../../../../bin/plugins/
#}

#TRANSLATIONS = $$PWD/../../../../../qrtranslations/ru/plugins/robots/ev3GeneratorBase_ru.ts

HEADERS += \
	include/ev3GeneratorBase/ev3GeneratorPluginBase.h \
	include/ev3GeneratorBase/ev3GeneratorBaseDeclSpec.h \
	include/ev3GeneratorBase/ev3MasterGeneratorBase.h \
	src/ev3GeneratorCustomizer.h \
	src/simpleGenerators/drawLineGenerator.h \
	src/simpleGenerators/drawPixelGenerator.h \
	src/simpleGenerators/drawRectGenerator.h \
	src/simpleGenerators/drawCircleGenerator.h \
	src/simpleGenerators/enginesGenerator.h \
	src/simpleGenerators/enginesStopGenerator.h \
	src/simpleGenerators/waitForButtonGenerator.h \
	src/converters/goToBlockNumberConverter.h \
	src/simpleGenerators/waitForTouchSensorGenerator.h \
	src/converters/outputPortNameConverter.h \
	src/simpleGenerators/ifElementGenerator.h \
    include/ev3GeneratorBase/ev3GeneratorFactory.h \
    src/robotModel/ev3GeneratorRobotModel.h

SOURCES += \
	src/ev3GeneratorPluginBase.cpp \
	src/ev3MasterGeneratorBase.cpp \
	src/ev3GeneratorCustomizer.cpp \
	src/simpleGenerators/drawLineGenerator.cpp \
	src/simpleGenerators/drawPixelGenerator.cpp \
	src/simpleGenerators/drawRectGenerator.cpp \
	src/simpleGenerators/drawCircleGenerator.cpp \
	src/simpleGenerators/enginesGenerator.cpp \
	src/simpleGenerators/enginesStopGenerator.cpp \
	src/simpleGenerators/waitForButtonGenerator.cpp \
	src/converters/goToBlockNumberConverter.cpp \
	src/simpleGenerators/waitForTouchSensorGenerator.cpp \
	src/converters/outputPortNameConverter.cpp \
	src/simpleGenerators/ifElementGenerator.cpp \
    src/ev3GeneratorFactory.cpp \
    src/robotModel/ev3GeneratorRobotModel.cpp

OTHER_FILES +=