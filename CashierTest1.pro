#-------------------------------------------------
#
# Project created by QtCreator 2022-06-21T21:53:17
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += serialport

QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CashierTest1
        target.files = CashierTest1
        target.path=/
INSTALLS +=target
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    progressbartest.cpp \
    iomanager.cpp \
    infomanager.cpp \
    uart.cpp \
    functionmanagement.cpp \
    uart2.cpp \
    uartthread.cpp

HEADERS  += widget.h \
    dbconnect.h \
    progressbartest.h \
    iomanager.h \
    infomanager.h \
    uart.h \
    functionmanagement.h \
    uart2.h \
    uartthread.h

FORMS    += widget.ui \
    progressbartest.ui \
    iomanager.ui \
    infomanager.ui

DISTFILES +=

RESOURCES += \
    src.qrc
