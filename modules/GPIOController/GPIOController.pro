#--------------------------------------------------------
# The .pro file for:                       pMotorController
# Author(s):                               Josiah Sam
#--------------------------------------------------------
QT -= gui
QT += core
QT -= widgets

CONFIG += c++11 console
CONFIG -= app_bundle

DESTDIR = ./bin

MOC_DIR = .moc
OBJECTS_DIR = .obj

TARGET = GPIOController
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
 ../VehicleStateMachine/src/ \
 ../MotionController/src/

SOURCES += src/main.cpp \
 src/LEDController.cpp \
 src/LIRController.cpp \
 src/Motor.cpp \
 src/MotorController.cpp \
 src/GPIOController.cpp \
 src/GPIOController_Info.cpp \
 src/VL53L1X_api.c \
 src/vl53l1_platform.c

HEADERS += \
 src/LEDController.h \
 src/LIRController.h \
 src/Motor.h \
 src/MotorController.h \
 src/GPIOController.h \
 src/GPIOController_Info.h \
 src/VL53L1X_api.h \
 src/vl53l1_platform.h \
 src/vl53l1_types.h \
 src/vl53l1_error_codes.h


OTHER_FILES += \
 *.sh \
 config/*.moos

LIBS += \
 -L../../../moos-ivp/build/MOOS/MOOSCore/lib/ \
 -lMOOS \
 \
 -L../../../moos-ivp/lib/ \
 -lapputil \
 -lmbutil \
 -lpigpiod_if2 \
 -lrt

unix {
 QMAKE_LFLAGS_RELEASE += -W
 QMAKE_CXXFLAGS += -Werror

 target.path=/usr/bin
 configs.path = /etc/SRC/configs
 config.files += config/*
}

!isEmpty(target.path): INSTALLS += target
!isEmpty(configs.path): INSTALLS += configs

