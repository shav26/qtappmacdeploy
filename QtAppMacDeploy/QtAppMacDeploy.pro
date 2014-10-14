TEMPLATE = app

QT += qml quick widgets
CONFIG += qt c++11

SOURCES += main.cpp \
    qmdsettings.cpp \
    qmdmanager.cpp \
    qmdcommand.cpp \
    qmdcommandmanager.cpp

RESOURCES += qml.qrc

ICON = icon_512x512.icns

macx {
    QMAKE_INFO_PLIST = Info.plist
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    qmdsettings.h \
    qmdmanager.h \
    qmdcommand.h \
    qmdcommandmanager.h
