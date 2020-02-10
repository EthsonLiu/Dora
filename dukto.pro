include(src/qtsingleapplication/qtsingleapplication.pri)

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

TARGET = Dukto

mac:ICON = image/dukto.icns
win32:RC_ICONS = image/dukto.ico
unix:RC_ICONS = image/dukto.ico

SOURCES += \
    src/main.cpp \
    src/main_window.cpp

HEADERS += \
    src/main_window.h

RESOURCES += \
    image/image.qrc

