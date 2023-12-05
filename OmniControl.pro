#-------------------------------------------------
#
# Project created by QtCreator 2021-03-29T18:41:08
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OmniControl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    joystick.cpp \
    connectionpulse.cpp \
    pulseform.cpp \
    customslider.cpp

HEADERS  += mainwindow.h \
    joystick.h \
    connectionpulse.h \
    pulseform.h \
    customslider.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    res/res.qrc \
    res/stylesheet.qrc
