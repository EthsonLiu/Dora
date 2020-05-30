include(src/qtsingleapplication/qtsingleapplication.pri)

QT += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

TARGET = Dukto

mac:ICON = image/dukto.icns
win32:RC_ICONS = image/dukto.ico
unix:RC_ICONS = image/dukto.ico

LIBS += -framework CoreServices

SOURCES += \
    src/about_widget.cpp \
    src/dukto_widget.cpp \
    src/main.cpp \
    src/preference_widget.cpp \
    src/project.cpp \
    src/system_tray_widget.cpp \
    src/updates_checking_widget.cpp \
    src/dukto_protocol.cpp \
    src/platform.cpp

HEADERS += \
    src/about_widget.h \
    src/config.h \
    src/dukto_widget.h \
    src/preference_widget.h \
    src/project.h \
    src/system_tray_widget.h \
    src/updates_checking_widget.h \
    src/dukto_protocol.h \
    src/platform.h

RESOURCES += \
    image/image.qrc

