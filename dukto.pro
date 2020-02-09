include(src/qtsingleapplication/qtsingleapplication.pri)

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
    src/main.cpp \
    src/main_window.cpp

HEADERS += \
    src/main_window.h

