#--------------------------------------------------------
# The .pro file for:                       iCameraInterface
# Author(s):                               Josiah Sam
#--------------------------------------------------------
QT -= gui
QT += core network
QT -= widgets

CONFIG += c++11 console
CONFIG -= app_bundle

DESTDIR = ./bin

MOC_DIR = .moc
OBJECTS_DIR = .obj

TARGET = CameraInterface
QMAKE_CXXFLAGS += -Wall -Werror

TEMPLATE = app

INCLUDEPATH += \
 ../../../moos-ivp/include \
 ../../../moos-ivp/MOOS/MOOSCore/Core/libMOOS/App/include \
 ../../../moos-ivp/MOOS/MOOSCore/Core/libMOOS/Comms/include \
 ../../../moos-ivp/MOOS/MOOSCore/Core/libMOOS/include \
 ../../../moos-ivp/MOOS/MOOSCore/Core/libMOOS/Thirdparty/getpot/include \
 ../../../moos-ivp/MOOS/MOOSCore/Core/libMOOS/Thirdparty/PocoBits/include \
 ../../../moos-ivp/MOOS/MOOSCore/Core/libMOOS/Thirdparty/AppCasting/include \
 ../../../moos-ivp/MOOS/MOOSCore/Core/libMOOS/Utils/include \

SOURCES += src/main.cpp \
 src/CameraInterface.cpp \
 src/CameraInterface_Info.cpp

HEADERS += \
 src/CameraInterface.h \
 src/CameraInterface_Info.h

OTHER_FILES += \
 *.sh \
 config/*.moos

LIBS += \
 -L../../../moos-ivp/build/MOOS/MOOSCore/lib/ \
 -lMOOS \
 \
 -L../../../moos-ivp/lib/ \
 -lapputil \
 -lmbutil

unix {
 QMAKE_LFLAGS_RELEASE += -W
 QMAKE_CXXFLAGS += -Werror

 target.path=/usr/bin
 configs.path = /etc/SRC/configs
 config.files += config/*
}

!isEmpty(target.path): INSTALLS += target
!isEmpty(configs.path): INSTALLS += configs

