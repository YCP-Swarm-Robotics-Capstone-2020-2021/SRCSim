#-------------------------------------------------
#
# Project created by QtCreator 2020-09-25T08:37:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ControlGUI
TEMPLATE = app
DESTDIR = ./bin

MOC_DIR = .moc
OBJECTS_DIR = .obj

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

INCLUDEPATH += \
     ../../../moos-ivp/include \
     ../../../moos-ivp/MOOS/MOOSCore/Core/libMOOS/App/include \
     ../../../moos-ivp/MOOS/MOOSCore/Core/libMOOS/Comms/include \
     ../../../moos-ivp/MOOS/MOOSCore/Core/libMOOS/include \
     ../../../moos-ivp/MOOS/MOOSCore/Core/libMOOS/Thirdparty/getpot/include \
     ../../../moos-ivp/MOOS/MOOSCore/Core/libMOOS/Thirdparty/PocoBits/include \
     ../../../moos-ivp/MOOS/MOOSCore/Core/libMOOS/Thirdparty/AppCasting/include \
     ../../../moos-ivp/MOOS/MOOSCore/Core/libMOOS/Utils/include \
     ../VehicleStateMachine/src/

SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
        src/robotoverviewitem.cpp \
        src/uimoosinterface.cpp \
        src/uimoosinterface_info.cpp

HEADERS += \
        src/mainwindow.h \
        src/robotoverviewitem.h \
        src/styles.h \
        src/uimoosinterface.h \
        src/uimoosinterface_info.h

OTHER_FILES += \
        config/*

LIBS += \
 -L../../../moos-ivp/build/MOOS/MOOSCore/lib/ \
 -lMOOS \
 \
 -L../../../moos-ivp/lib/ \
 -lapputil \
 -lmbutil

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target