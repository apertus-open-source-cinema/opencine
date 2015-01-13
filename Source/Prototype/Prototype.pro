TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    gl3w.c

include(deployment.pri)
qtcAddDeployment()

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS_RELEASE += -O2

LIBS += -lOpenCL -lOpenImageIO -lGL -ldl -lSDL2 #-L"../OpenCine/build/lib/libraw.so" #-lraw -lraw_r
LIBS += -L$$PWD/../OpenCine/build/lib/ -lraw
#LIBS +=  -L/usr/lib/x86_64-linux-gnu -lSDL2

INCLUDEPATH += $$PWD/../OpenCine/3rdParty/LibRaw/libraw
DEPENDPATH += $$PWD/../OpenCine/3rdParty/LibRaw/libraw

INCLUDEPATH += /home/andi/Downloads/oglplus-0.57.0/include/
INCLUDEPATH += /home/andi/Downloads/oglplus-0.57.0/build/include/
INCLUDEPATH += /home/andi/Downloads/oglplus-0.57.0/implement/

DISTFILES += \
    Test1.qml \
    Test1Form.ui.qml

HEADERS += \
    gl3w.h
